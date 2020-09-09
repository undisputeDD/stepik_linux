#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void mysignal_handler(int signal)
{
        printf("%d\n", getpid());
        exit(0);
}

int main()
{
    pid_t pID = fork();
    if (pID == 0)
    {
        chdir("/");
        setsid();
        close(0);
        close(1);
        close(2);
        signal(SIGURG, mysignal_handler);
        sleep(1000);
    }
    return 0;
}
