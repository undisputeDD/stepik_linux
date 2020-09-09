#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pID = fork();
	if (pID == 0)
	{
		chdir("/");
		setsid();
		close(0);
		printf("%d\n", getpid());
		close(1);
		close(2);
	}
	return 0;
}
