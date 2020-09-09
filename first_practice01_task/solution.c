#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* ft_strjoin(const char* str1, const char* str2)
{
	const int size = strlen(str1) + strlen(str2) + 1;
	char* result = (char *)malloc(sizeof(char) * (size + 1));
	result[size] = '\0';

	int i = 0;
	while (*str1 != '\0')
		result[i++] = *str1++;
	result[i++] = ' ';
	while (*str2 != '\0')
		result[i++] = *str2++;
	return result;
}

int main(int argc, char** argv)
{
	const char* command = ft_strjoin(argv[1], argv[2]);
	FILE* data_stream = popen(command, "r");
	int datac;
	int answer = 0;

	while ((datac = getc(data_stream)) != EOF)
		if (datac == '0')
			++answer;
	printf("%d\n", answer);
	pclose(data_stream);
	return 0;
}

