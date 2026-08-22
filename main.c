#include <stdlib.h>
#include <stdio.h>
#include "RaylibBackend.h"
#include <string.h>
#include "CValue.h"

int main(int argc, char** argv)
{
    int a = 2;
    int b = 10;

    FILE* file;
    char* encodingA = @encode(FILE);
   // printf("%i\n", memcmp(&a, &b, sizeof(int)));
    printf("Encoding of cValueA: %s\n", encodingA);

    raylibWindow(1280, 800, "My Rasteriser");
    return 0;
}
