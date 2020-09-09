#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PROCDIR_LEN 6
#define STATUS_LEN 7

char* itoa(int pid)
{
	int size = 0;
	int pid_rem = pid;
	while (pid_rem != 0)
	{
		pid_rem /= 10;
		++size;
	}
	char* result = (char *)malloc(sizeof(char) * (size + 1));
	result[size] = '\0';
	while (pid != 0)
	{
		result[--size] = pid % 10 + '0';
		pid /= 10;
	}
	return result;
}

char* proc_dir_to_str(char* arg)
{
	size_t result_len = PROCDIR_LEN + strlen(arg) + STATUS_LEN;
	char* result = (char *)malloc(sizeof(char) * (result_len + 1));
	result[result_len] = '\0';
	char* proc_dir = "/proc/";
	char* status_file = "/status";
	
	int i = 0;
	while (*proc_dir != '\0')
		result[i++] = *proc_dir++;
	while (*arg != '\0')
		result[i++] = *arg++;
	while (*status_file != '\0')
		result[i++] = *status_file++;
	return result;
}

int main(int argc, char** argv)
{
	int cur_proc = atoi(argv[1]);
	printf("%d\n", cur_proc);
	while (cur_proc != 1) //&& cur_proc != 0)
	{
		char* buf = 0;
		size_t size = 0;
		ssize_t len;
		char* scur_proc = itoa(cur_proc);
		//printf("%s\n", scur_proc);
		char* proc_status = proc_dir_to_str(scur_proc);

		FILE* f = fopen(proc_status, "r");
		if (f)
		{
			while ((len = getline(&buf, &size, f)) > 0)
			{
				buf[len] = '\0';
				if (strncmp(buf, "PPid", 4) == 0)
				{
					cur_proc = atoi(buf + 6);
					printf("%d\n", cur_proc);
					break;
				}
			}
		}
		free(scur_proc);
		free(buf);
		free(proc_status);
		fclose(f);
	}
	return 0;
}
