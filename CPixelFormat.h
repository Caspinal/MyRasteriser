#ifndef CPixelFormat_h
#define CPixelFormat_h
#include "CPixelColour.h"
#include <stdlib.h>

 typedef struct CPixelFormat CPixelFormat;

 typedef CPixelColour (*CPixelFormatGetImp)(CPixelFormat* pf, int x, int y);
 typedef void (*CPixelFormatSetImp)(CPixelFormat* pf, int x, int y, CPixelColour colour);
 typedef CPixelColour (*CPixelFormatSampleImp)(CPixelFormat* pf,float u, float v);

 struct CPixelFormat
{
    int width;
    int height;
    char* name;
    char* encoding; // for example R8G8B8A8, R32F, etc.
    void* backing; 

    size_t bitsPerPixel;

    CPixelFormatGetImp getPixelColour;
    CPixelFormatSetImp setPixelColour;
    CPixelFormatSampleImp samplePixelColour;

};
#endif

void CPixelFormatSet(CPixelFormat* pf, int x, int y, CPixelColour colour);
CPixelColour CPixelFormatGet(CPixelFormat* pf, int x, int y);
CPixelColour CPixelFormatSample(CPixelFormat* pf,float u, float v);

void CPixelFormatInitWithEncoding(CPixelFormat* pf, char* encoding);