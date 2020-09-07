#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

void create_status(char* status, int status_len, char* d_name)
{
	int i = 0;
	char proc_dir[] = "/proc/";
	while (i < status_len && i < 6)
	{
		status[i] = proc_dir[i];
		++i;
	}
	while (i < status_len && *d_name != '\0')
	{
		status[i] = *d_name;
		++d_name;
		++i;
	}
	status[i++] = '/';
	char genenv[] = "status";
	int j = 0;
	while (i < status_len && j < 6)
	{
		status[i] = genenv[j];
		++i;
		++j;
	}
}

int main()
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
