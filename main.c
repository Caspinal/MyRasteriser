#include <stdlib.h>
#include <stdio.h>
#include "RaylibBackend.h"
#include <string.h>
#include "CValue.h"

#include <stdio.h>
#include <stdlib.h>
#include </opt/homebrew/include/icns.h>
#include "CPixelFormat.h"

int main(int argc, char** argv)
{    

    char* encoding = "RGBA8";
    CPixelFormatInitWithEncoding(0, encoding);
    char* encodingf = "RGBA32";
    CPixelFormatInitWithEncoding(0, encodingf);
     char* encoding8888 = "RGBA8888";
    CPixelFormatInitWithEncoding(0, encoding8888);
    //raylibWindow(1280, 800, "My Rasteriser");

    return 0;
}
