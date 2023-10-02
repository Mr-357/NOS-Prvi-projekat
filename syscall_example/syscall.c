#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main(int argc,char **argv){
    int pid,nice;
    if(argc != 3){
        printf("Too little or too much parameters.\n");
        return -1;
    }
    pid = atoi(argv[1]);
    nice = atoi(argv[2]);
    printf("Changing process:%d with nice:%d \n",pid,nice);
    long int ret =syscall(548,pid,nice);
    printf("Syscall returned:%ld \n",ret);
    return 0;
}