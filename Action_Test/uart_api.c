#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <pthread.h>
#include "uart_api.h"

volatile int STOP=FALSE;

int wait_flag=TRUE;		/* while signal not recive -> TRUE */
static struct termios uart_oldtio, uart_newtio;
static int uart_dev = -1;
static char recvbuf[256];

pthread_t ridst, rids;
pthread_mutex_t rstatus_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
    serial device open function
*/
int user_uart_open(char *device)
{
    char opendevice[20];
    sprintf(opendevice, "/dev/%s", device);
    uart_dev = open(opendevice, O_RDWR | O_NOCTTY | O_NONBLOCK);
    recv_status = FIRST_STATE;	
    if (uart_dev <0) {perror(opendevice); return -1; }
    return 0;

}


/*
    serial device close function
*/
void user_uart_close (void)
{
    tcsetattr(uart_dev,TCSANOW,&uart_oldtio);
    close(uart_dev);
}

/*
    terminal property set function
*/
void user_uart_config(int baud)
{
  
    tcgetattr(uart_dev,&uart_oldtio); /* save current port settings */

    /* Non canonical : port setting to input data processing */
    switch(baud)
    {
	case 4800:    uart_newtio.c_cflag |= B4800; break;
	case 9600:    uart_newtio.c_cflag |= B9600; break;
	case 19200:    uart_newtio.c_cflag |= B19200; break;
	case 38400:    uart_newtio.c_cflag |= B38400; break;
	case 57600:    uart_newtio.c_cflag |= B57600; break;
	case 115200:    uart_newtio.c_cflag |= B115200; break;
	default:    uart_newtio.c_cflag |= B0; break;
    }
	uart_newtio.c_cflag |= CS8 | CLOCAL | CREAD;	
	uart_newtio.c_iflag = IGNPAR | ICRNL;
	uart_newtio.c_oflag = 0;
	uart_newtio.c_lflag = ~(ICANON | ECHO | ECHOE | ISIG);
	uart_newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
	uart_newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
	uart_newtio.c_cc[VERASE]   = 0;     /* del */
	uart_newtio.c_cc[VKILL]    = 0;     /* @ */
	uart_newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
	uart_newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
	uart_newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
	uart_newtio.c_cc[VSWTC]    = 0;     /* '\0' */
	uart_newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
	uart_newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
	uart_newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
	uart_newtio.c_cc[VEOL]     = 0;     /* '\0' */
	uart_newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
	uart_newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
	uart_newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
	uart_newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
	uart_newtio.c_cc[VEOL2]    = 0;     /* '\0' */
	tcflush(uart_dev, TCIFLUSH);
	tcsetattr(uart_dev,TCSANOW,&uart_newtio);
	
//	pthread_create(&ridst,0,receive_threadst,(void *)uart_dev);

}

int user_uart_write(unsigned char *ubuf, int size)
{
    return write(uart_dev, ubuf, size);
}
void *receive_threadst(void *arg)
{
	int recv_fd;
	int *arg_fd;
	fd_set readfs;
	struct timeval timeout;
	int len,i;
	arg_fd = (int *)arg;
	recv_fd = (int)arg_fd;
	FD_ZERO(&readfs);
	timeout.tv_sec = 0;
	timeout.tv_usec = 5000;
	usleep(1000);
	while(1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		len = read(recv_fd, recvbuf, sizeof(recvbuf));
		if(len>0) {
#ifdef _REIEVE_MSG_ 
			printf("\n\r recv data:");				
#endif
			for(i=0;i<len;i++){
				if(recvbuf[i]==0x3c){	
					recv_status = RECIEVED_STATE;
				}
#ifdef _REIEVE_MSG_ 
				printf("0x%x ",recvbuf[i]);
#endif
			}
		}
	}
}

int user_uart_read(unsigned char *ubuf, int size)
{
    int res=0;

    /* loop while waiting for input. normally we would do something
	useful here */
    while (STOP==FALSE) {
	
	if (wait_flag==FALSE) {
	    res = read(uart_dev, ubuf, size);
	   
	    wait_flag = TRUE;     
	    break;
	}
    }
    return res;
}

