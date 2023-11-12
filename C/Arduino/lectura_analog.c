#include "serial.h"
#include <string.h>

int main()
{
	char *portName = "/dev/cu.usbmodem1101";
	char command[MAX_DATA_LENGTH];
	char response[MAX_DATA_LENGTH];
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
	
	while (isConnected(&arduino) && command[0] != 'q') {
		strcpy(command, "\n");
		writeSerialPort(command, strlen(command), &arduino);
		Sleep(1);
		readSerialPort(response, MAX_DATA_LENGTH, &arduino);
		int delay = atoi(response) + 100;
		strcpy(command, "on\n");
		writeSerialPort(command, strlen(command), &arduino);
		Sleep(delay);
		strcpy(command, "off\n");
		writeSerialPort(command, strlen(command), &arduino);
		Sleep(delay);
	}
	closeSerial(&arduino);
	return 0;
}
