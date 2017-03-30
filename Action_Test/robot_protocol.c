#include <stdio.h>
#include <string.h>
#include "robot_protocol.h"
#include "uart_api.h"
//////////////////////////////////////////////////// Protocol Test
unsigned char Send_Buffer[256];
unsigned char Receive_Ack(void);
/*
    send commnad function
*/
void Send_Command(unsigned char command)
{
	Send_Buffer[0] = command;
	printf("\nSend_Command()\n");
        user_uart_write(Send_Buffer, 1);

	//if (!Receive_Ack())
	//    printf("\nCommand Failed\n");
	//else
	//    printf("\nCommand OK\n");
}

int Receive_Command(unsigned char *buff)
{
    int res;

    res = user_uart_read(buff, 1);

    return res;
}

unsigned char Receive_Buffer[2];
#define ERROR	0
#define OK	1
/*
    recive processing function
*/
unsigned char Receive_Ack(void)
{
    int i;
    int rx_len;

    while(1) {
	rx_len = user_uart_read(Receive_Buffer, 2);
	if(rx_len > 0) {
	    printf("\nReceive Code:");
	    for(i=0; i<rx_len; i++) printf("%d", Receive_Buffer[i]);
	    for(i=0; i<rx_len; i++) {
		if(Receive_Buffer[i] == 48) {
		    printf("\nExit Code\n");
		    return OK;
		} else if(Receive_Buffer[i] == 30) {
		    printf("\nBasic Position");
		} else if(Receive_Buffer[i] == 31) {
		    printf("\nShun Position");
		} else if(Receive_Buffer[i] == 32) {
		    printf("\nUpright Position");
		} else if(Receive_Buffer[i] == 1) {
		    //printf("\nCarrige Return");
		    ;
		} else {
		    printf("\nUnknown Pose");
		    return ERROR;
		}
	    }
	} else
	    return ERROR;
    }
    return OK;
}

unsigned char Receive_Angle(unsigned char command)
{
	Send_Buffer[0] = command;
  user_uart_write(Send_Buffer, 1);
	int i;
  int rx_len;
	unsigned char temp;
	unsigned char Receive_Buf[3];
  while(1) {
		rx_len = user_uart_read(Receive_Buf, 3);
		//printf("%d %d %d \n",Receive_Buf[0],Receive_Buf[1],Receive_Buf[2]);
		if(rx_len > 0) {	
		  for(i=0; i<rx_len; i++) {
				temp = Receive_Buf[i];
				if(temp == 60)
				{
					printf("\nReceive Angle: %d",Receive_Buf[i-2]);
					return OK;
				}
		  }
		} else
	   printf("\nCommand Failed\n");
	}
  printf("\nCommand OK\n");
}

unsigned char Receive_All_Angle()
{
	Send_Buffer[0] = MOTOR0_ANGLE;
      user_uart_write(Send_Buffer, 1);

	int i,j=0,z=0;
  	int rx_len;
	unsigned char temp;
	unsigned char Receive_Buf[3];
   	while(1) {
		rx_len = user_uart_read(Receive_Buf, 3);
		if(rx_len > 0) {	
		    for(i=0; i<rx_len; i++) {
			temp = Receive_Buf[i];
			if(temp == 60)
			{
			
				printf("\nMotor %d angle %d",z,Receive_Buf[i-2]);
				j++;
				switch(j)
				{
					case 1: z=1; Send_Buffer[0] = MOTOR1_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 2: z=2; Send_Buffer[0] = MOTOR2_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 3: z=3; Send_Buffer[0] = MOTOR3_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 4: z=4; Send_Buffer[0] = MOTOR4_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 5: z=6; Send_Buffer[0] = MOTOR6_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 6: z=7; Send_Buffer[0] = MOTOR7_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 7: z=8; Send_Buffer[0] = MOTOR8_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 8: z=11; Send_Buffer[0] = MOTOR11_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 9: z=12; Send_Buffer[0] = MOTOR12_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 10: z=13; Send_Buffer[0] = MOTOR13_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 11: z=14; Send_Buffer[0] = MOTOR14_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 12: z=18; Send_Buffer[0] = MOTOR18_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 13: z=19; Send_Buffer[0] = MOTOR19_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 14: z=20; Send_Buffer[0] = MOTOR20_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 15: z=21; Send_Buffer[0] = MOTOR21_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 16: z=22; Send_Buffer[0] = MOTOR22_ANGLE; user_uart_write(Send_Buffer,1); break;
					case 17: return OK;
				}	
				
			}
		    }
		} else
	    printf("\nCommand Failed\n");
	}
    printf("\nCommand OK\n");
}
