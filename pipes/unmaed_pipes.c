#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int pipefd[2];
    char buf[20];
    if(pipe(pipefd)==-1)
    {
        printf("failed to create");
    }
    pid=fork();
    if(pid<0)
    {
        printf("failed to create");
    }
    else if(pid ==0)
    {
        close(pipefd[1]);
        read(pipefd[0],buf,5);
        buf[5] = '\0'; // Null terminate
        printf("Child read: %s\n", buf);
        close(pipefd[0]);
    }
    else
    {
        close(pipefd[0]);
        write(pipefd[1],"hello",5);
        close(pipefd[1]);
    }
    return 0;
}
