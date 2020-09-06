#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{ 
	char* buf = 0;
	int len;
	size_t size = 0;
	FILE * f;

	f = fopen("/proc/self/status", "r");

	while((len = getline(&buf, &size, f)) > 0)
	{
		//printf("%d\n", len);
		buf[len] = '\0';
		//printf("buffer: %s\n", buf);
		if (strncmp("PPid", buf, 4) == 0)
		{
			char* tmp = buf;
			while (*tmp != '\0' && !(*tmp >= 0 && *tmp <= 9))
				++tmp;
			//printf("tmp = %s\n", tmp);
			printf("%d\n", atoi(tmp));
			free(buf);
			buf = 0;
			break;
		}
		free(buf);
		buf = 0;
	}
	fclose(f);
	return 0;
}
