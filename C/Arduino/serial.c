#include "serial.h"

SerialPort initSerialPort(const char *portName)
{
    SerialPort handler;
    handler.connected = false;
    handler.handler = CreateFileA((LPCSTR)portName,
                                 GENERIC_READ | GENERIC_WRITE,
                                 0,
                                 NULL,
                                 OPEN_EXISTING,
                                 FILE_ATTRIBUTE_NORMAL,
                                 NULL);
    if (handler.handler == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            printf("ERROR: Handle was not attached. Reason : %s not available\n", portName);
        }
        else
        {
            printf("ERROR!!!\n");
        }
    }
    else
    {
        DCB dcbSerialParameters = {0};

        if (!GetCommState(handler.handler, &dcbSerialParameters))
        {
            printf("Failed to get current serial parameters\n");
        }
        else
        {
            dcbSerialParameters.BaudRate = CBR_9600;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler.handler, &dcbSerialParameters))
            {
                printf("ALERT: could not set serial port parameters\n");
            }
            else
            {
                handler.connected = true;
                PurgeComm(handler.handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
    return handler;
}

int readSerialPort(const char *buffer, unsigned int buf_size, SerialPort *handler)
{
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(handler->handler, &handler->errors, &handler->status);

    if (handler->status.cbInQue > 0)
    {
        if (handler->status.cbInQue > buf_size)
        {
            toRead = buf_size;
        }
        else
        {
            toRead = handler->status.cbInQue;
        }
    }

    memset((void*) buffer, 0, buf_size);

    if (ReadFile(handler->handler, (void*) buffer, toRead, &bytesRead, NULL))
    {
        return bytesRead;
    }

    return 0;
}


bool writeSerialPort(const char *buffer, unsigned int buf_size, SerialPort *handler)
{
    DWORD bytesSend;

    if (!WriteFile(handler->handler, buffer, buf_size, &bytesSend, 0))
    {
        ClearCommError(handler->handler, &handler->errors, &handler->status);
        return false;
    }
    return true;
}

bool isConnected(SerialPort *handler)
{
    if (!ClearCommError(handler->handler, &handler->errors, &handler->status))
    {
        handler->connected = false;
    }

    return handler->connected;
}

void closeSerial(SerialPort *handler)
{
    CloseHandle(handler->handler);
}
