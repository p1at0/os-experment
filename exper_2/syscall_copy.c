#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
int main(int argc, char* argv[]){
/*
	int i;
	for(i =0; i < 10; i++){
		syscall(336, i);
	}
*/
	if(argc != 3){
		printf("para error!\n");
		return 0;
	}
	syscall(335, argv[1], argv[2]);
	return 0;
}
