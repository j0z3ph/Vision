/**
 * @file lectura_analog.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief 
 * @version 0.1
 * @date 2023-11-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "serial.h"
#include <string.h>
#include <stdio.h>
#define X_OFFSET 3105
#define Y_OFFSET 3095
#define MAX_JOY 4095
#define MIN_JOY 0
#define MAX_X 20
#define MIN_X -20
#define MAX_Y 20
#define MIN_Y -20

int main()
{
	char *portName = "/dev/cu.usbserial-0001";
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
	
	while (isConnected(&arduino)) {
		//strcpy(command, "\n");
		//writeSerialPort(command, strlen(command), &arduino);
		Sleep(1);
		int tot = readSerialPort(response, MAX_DATA_LENGTH, &arduino);

		//if(response[11] != '\n') continue;
		
		int x = atoi(response) - X_OFFSET;
		int y = atoi(response+5) - Y_OFFSET;
		
		if(x >= 0) {
			x = (int)((double)x * ((double)MAX_X / (double)(MAX_JOY - X_OFFSET))); 
		} else {
			x = (-1)*(int)((double)x * ((double)MIN_X / (double)(X_OFFSET)));
		}

		if(y >= 0) {
			y = (int)((double)y * ((double)MAX_Y / (double)(MAX_JOY - Y_OFFSET))); 
		} else {
			y = (-1)*(int)((double)y * ((double)MIN_Y / (double)(Y_OFFSET)));
		}

		printf("%i - %i\n", x, y);
		
		//printf("%s", response);
		//int c =0;
		//for (int i = 0; i < MAX_DATA_LENGTH; i++)
		//{
		//	if(response[i] == '\n') {
		//		c = i;
		//		break;
		//	}
		//}
		
		//printf("%i - %i\n", tot, c);
		//Sleep(1);
		//printf("%c\n", response[10]);
		if(response[9] == '-' && response[10] == '0') {
			strcpy(command, "on\n");
			writeSerialPort(command, strlen(command), &arduino);
		} else {
			strcpy(command, "off\n");
			writeSerialPort(command, strlen(command), &arduino);
		}
		//Sleep(1);
	}
	closeSerial(&arduino);
	return 0;
}
