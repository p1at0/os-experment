#include <string.h>
#include "stdlib.h"
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#define BUFMAX 10
union semun{
     int val;
     struct semid_ds *buf;
     unsigned short int *array;
     struct seminfo *__buf;
};

typedef struct Buffer{
	char data[10][10];
	int length[10];
	int in;
	int out;
	int over;
}Buffer;

key_t shmKey = 333;
key_t semKey = 444;

void P(int semid, int index){
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid, &sem, 1);
}

void V(int semid, int index){
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(semid, &sem, 1);
}

int writebuf(const char* source){
	//取得共享缓冲区
	int shmId = shmget(shmKey, sizeof(Buffer), IPC_CREAT | 0666);
	Buffer* buf = (Buffer*) shmat(shmId, NULL, SHM_R|SHM_W);
	//取得信号灯
	int semId = semget(semKey, 2, IPC_CREAT | 0666);

	//读文件
	FILE *fr;
	if((fr = fopen(source, "rb")) == NULL){
		printf("read source error!\n");
		return 0;
	}
	
	int readover = 0;
	int size;
	while(!readover){
		P(semId, 0);
		printf("write buf.\n");
		size = fread(buf->data[buf->in],sizeof(char), sizeof(buf->data[buf->in]), fr);
		buf->length[buf->in] = size;
		buf->in++;
		buf->in %= 10;
		if(feof(fr)){
			readover = 1;
			buf->over = 1;
		}
		V(semId, 1);
	}
	printf("write over...\n");
	fclose(fr);

	return 0;
}

int readbuf(const char* target){
	//取得共享缓冲区
	int shmId = shmget(shmKey, sizeof(Buffer), IPC_CREAT|0666);
	Buffer* buf = (Buffer*)shmat(shmId, NULL, SHM_R|SHM_W);

	//取得信号灯
	int semId = semget(semKey, 2, IPC_CREAT|0666);

	//写文件
	FILE *fw;
	fw = fopen(target, "wb");

	int writeover = 0;
	int size;
	
	while(!writeover){
		P(semId, 1);
		printf("read buf.\n");
		fwrite(buf->data[buf->out],sizeof(char), buf->length[buf->out] , fw);
		buf->out++;
		buf->out %= 10;
		if((buf->in == buf->out) && buf->over){
			writeover = 1;
		}
		V(semId, 0);
	}
	printf("read over...\n");
	fclose(fw);
	return 0;
}

int main(int argc, char* argv[]){
	//创建共享内存组
	int shmId = shmget(shmKey, sizeof(Buffer), IPC_CREAT | 0666);
	Buffer *buf = (Buffer*)shmat(shmId, NULL, SHM_R|SHM_W);
	buf->in = 0;
	buf->out = 0;
	buf->over = 0;
	//创建信号灯
	int semId =semget(semKey, 2, IPC_CREAT | 0666);

	//信号灯赋初值
	union semun arg1, arg2;
	arg1.val = 9;
	arg2.val = 0;
	semctl(semId, 0, SETVAL, arg1); // empty
	semctl(semId, 1, SETVAL, arg2); // full

	printf("开始创建进程！\n");
	//创建两个进程, 一个执行readbuf, 一个执行writebuf
	pid_t p1, p2;
	if((p1 = fork()) == 0){
		writebuf(argv[1]);
	}else if((p2 = fork()) == 0){
		readbuf(argv[2]);
	}else{

		
		//等待子进程结束
		wait(&p1);
		wait(&p2);

		//删除信号灯
		semctl(semId, 1, IPC_RMID, arg1);

		//删除共享缓冲区
		shmctl(shmId, IPC_RMID, 0);
	}
	return 0;
}
