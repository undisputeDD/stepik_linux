#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

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
	DIR* d;
	struct dirent* dir;
	int res = 0;

	d = opendir("/proc/");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			int i = 0;
			int dir_len = strlen(dir->d_name);

			while (i < dir_len)
			{
				if (!(dir->d_name[i] >= '0' && dir->d_name[i] <= '9'))
					break;
				++i;
			}
			if (i == dir_len)
			{
				int status_len = 6 + dir_len + 7;
				char* status = (char *)malloc(sizeof(char) * (status_len + 1));
				status[status_len] = '\0';
				create_status(status, status_len, dir->d_name);
				//printf("%s\n", status);
				FILE * f = fopen(status, "r");
				//if (f == NULL)
				//	printf("NULL");
				ssize_t len;
				size_t size = 0;
				char* buf = 0;
				
				//printf("a\n");
				while ((len = getline(&buf, &size, f)) > 0)
				{
					//printf("%s\n", buf);
					buf[len] = '\0';
					if (strcmp(buf, "Name:	genenv\n") == 0)
						++res;
					free(buf);
					buf = 0;
					break;
				}
				fclose(f);
				free(status);
				status = 0;
			}
		}
		closedir(d);
	}
	printf("%d\n", res);
	return 0;
}
