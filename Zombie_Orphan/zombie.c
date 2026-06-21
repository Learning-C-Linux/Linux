#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        printf("failed\n");
        return -1;
    }
    else if(pid==0)
    {
        printf("child process");
        exit(0);
    }
    else 
    {
	wait();
        printf("parent process");
    }
    return 0;
}
