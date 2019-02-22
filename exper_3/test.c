#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_SIZE 1024
 
int main(void)
{
	int fd;
	char buf[MAX_SIZE];	//缓冲区
	char get[MAX_SIZE];	//要写入的信息
	fd = open("/dev/myDevice", O_RDWR | O_NONBLOCK);
	if (fd != -1)
	{
		//写信息
		printf("input :");
		gets(get);
		write(fd, get, sizeof(get));
 
		//读刚才写的信息
		read(fd, buf, sizeof(buf)); 
		printf("device Message: %s\n", buf);
		
		close(fd);
		return 0;
	}
	else
	{
		printf("Device open failed\n");
		return -1;
	}
}
