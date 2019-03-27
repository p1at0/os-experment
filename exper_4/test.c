#include<string.h>
#include<stdlib.h>
#include<stdio.h>
char _buf[1024];
int main(){
  char* buf = _buf;
  long MemTotal, MemFree, Buffers, Cached;
	int i = 0;
  int line = 1;
  FILE* fp = fopen("/proc/meminfo", "r");
	
  while(fgets(buf, 1024, fp) != 0 && line < 6){ 
    i = 0;
    printf("%s", buf);
    while(buf[i++] != ':');
    buf += i;
    i = 0;
    while(buf[i++] == ' ');
    i--;
    buf += i;
    i = 0;
    while(buf[i++] != ' ');
    buf[i - 1] = '\0';
    printf("%s\n",buf);
    switch(line){
      case 1:
        MemTotal = atol(buf);
        break;
      case 2:
        MemFree = atol(buf);
        break;
      case 4:
        Buffers = atol(buf);
        break;
      case 5:
        Cached = atol(buf);
        break;
      default:
        break;
    } 
    line++;
  }
  fclose(fp);
  printf("MemTotal:%ld\tMemFree:%ld\tBuffers:%ld\tCached:%ld",MemTotal, MemFree, Buffers, Cached);
  return 0;
}

