#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int (*someSecretFunction)(int);

bool init_library(const char* libName, const char* funcName)
{
    void *hdl = dlopen(libName, RTLD_LAZY);
    if (hdl == NULL)
        return false;

    someSecretFunction = (int (*)(int))dlsym(hdl, funcName);
    if (someSecretFunction == NULL)
        return false;
    return true;
}

int main(int argc, char** argv)
{
    if (init_library(argv[1], argv[2]) == true)
        printf("%d\n", someSecretFunction(atoi(argv[2]));
    return 0;
}
