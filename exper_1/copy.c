#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#define BUF_MAX 8

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("argc error!\n");
		return 0;
	}	

	int infd, outfd;
	if((infd = open(argv[1], O_RDONLY)) == -1){
		printf("source file: %s\n", argv[1]);
		printf("open source file error!\n");
		return 0;
	}
	
	if((outfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1){
		printf("create target file error!\n");
		return 0;
	}

	char buf[BUF_MAX];
	int nread;
	while((nread = read(infd, buf, BUF_MAX)) > 0){
		write(outfd, buf, nread);
	}
	close(infd);
	close(outfd);
	return 0;
}
