#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main()
{
	char* buf = 0;
	int len;
	size_t size = 0;
	DIR* d;
	struct dirent* dir;

	d = opendir("/proc/");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			int i = 0;
			int dir_len = strlen(dir->d_name);

			for (; i < dir_len; ++i)
				if (!(dir->d_name[i] >= '0' && dir->d_name[i] <= '9'))
					break;
			if (i == dir_len)
				printf("dir\n");
		}
		closedir(d);
	}
	
}
