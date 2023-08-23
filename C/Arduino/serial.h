#ifndef __SERIAL_ARDUINO_H__
#define __SERIAL_ARDUINO_H__ 1

#ifdef _WIN32
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

typedef struct Handler
{
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;
} SerialPort;

SerialPort initSerialPort(const char *portName);
int readSerialPort(const char *buffer, unsigned int buf_size, SerialPort *handler);
bool writeSerialPort(const char *buffer, unsigned int buf_size, SerialPort *handler);
bool isConnected(SerialPort *handler);
void closeSerial(SerialPort *handler);

#else

#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h>  
#include <errno.h>  
#include <termios.h>
#include <time.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h> 
#include <unistd.h> 
#include <sys/ioctl.h>
#include <getopt.h>

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

typedef struct Handler
{
    int handler;
    bool connected;
} SerialPort;

SerialPort initSerialPort(const char *portName);
int readSerialPort(char *buffer, unsigned int buf_size, SerialPort *handler);
bool writeSerialPort(const char *buffer, unsigned int buf_size, SerialPort *handler);
bool isConnected(SerialPort *handler);
void closeSerial(SerialPort *handler);
void Sleep(int val);

#endif

#endif