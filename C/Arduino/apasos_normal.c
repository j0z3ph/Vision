#include "serial.h"
#include <string.h>

int main()
{
	char *portName = "/dev/cu.usbmodem1101";
	char command[MAX_DATA_LENGTH];
	char response[MAX_DATA_LENGTH];
	int delay = 10;
	command[0] = '\n';
	SerialPort arduino = initSerialPort(portName);
	printf("Conectando");
	while (!isConnected(&arduino)) {
		Sleep(100);
		printf(".");
		arduino = initSerialPort(portName);
	}
	if (isConnected(&arduino))
		printf("\nConectado al puerto %s\n", portName);
	strcpy(command, "0000\n");
	writeSerialPort(command, strlen(command), &arduino);
	Sleep(delay);
	while (isConnected(&arduino)) {
		// Movimiento Por Normal
		strcpy(command, "1100\n");
		writeSerialPort(command, strlen(command), &arduino);
		strcpy(command, "0110\n");
		writeSerialPort(command, strlen(command), &arduino);
		strcpy(command, "0011\n");
		writeSerialPort(command, strlen(command), &arduino);
		strcpy(command, "1001\n");
		writeSerialPort(command, strlen(command), &arduino);
		Sleep(delay);
	}
	closeSerial(&arduino);
	return 0;
}