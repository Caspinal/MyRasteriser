#include "CPixelFormat.h"
#include <stdio.h>
#include <stdlib.h>
#include "CLMath.h"

CPixelFormat* CPixelFormatCreate(int width, int height, char* name, char* encoding, void* backing)
{
    CPixelFormat* pf = (CPixelFormat*)malloc(sizeof(CPixelFormat));
    pf->width = width;
    pf->height = height;
    pf->name = name;
    pf->encoding = encoding;
    pf->backing = NULL; // Initialize backing to NULL

    if(backing == NULL)
    {
        pf->backing = malloc(width * height * 4 * sizeof(float)); // Assuming 4 floats per pixel (RGBA)
    }
    else
    {
        pf->backing = backing;
    }

    return pf;
}

CPixelColour CPixelFormatGetPixelColour(CPixelFormat* pf, int x, int y)
{
    return pf->getPixelColour(pf, x, y);
}

void CPixelFormatSetPixelColour(CPixelFormat* pf, int x, int y, CPixelColour colour)
{
    pf->setPixelColour(pf, x, y, colour);
}

CPixelColour CPixelFormatGetPixelColourSample(CPixelFormat* pf, float u, float v)
{
    return pf->samplePixelColour(pf, u, v);
}


CPixelColour CPixelFormatNearestSample(CPixelFormat* pf, float u, float v, CPixelColour colour)
{
       f2 texPos = (f2){u * pf->width, v * pf->height};
        
        // pixel center?
        texPos.x+=0.5;
        texPos.y+=0.5;
        
        return pf->getPixelColour(pf,texPos.x,texPos.y);
}

CPixelColour CPixelFormatBilinearSample(CPixelFormat* pf, float u, float v, CPixelColour colour)
{
  
}

CPixelColour CPixelFormatBicubicSample(CPixelFormat* pf, float u, float v, CPixelColour colour)
{
  
}
/** 
PixelColour sample(PixelFormat* src, point uv)
{
    // nearest
    PixelColour sampleCol = {};
    
    if(!smooth)
    {
        point texPos = (point){uv.x * src->width, uv.y * src->height,0};
        
        
        // pixel center?
        texPos.x+=0.5;
        texPos.y+=0.5;
        
        sampleCol = PixelFormat_getColour(src,texPos.x,texPos.y);
    }else
    {
        point texPos = (point){uv.x * src->width, uv.y * src->height,0};
        
        
        // pixel center
        texPos.x+=0.5;
        texPos.y+=0.5;
        
        
        // linear
        int w = src->width;
        int h = src->height;
        
        PixelColour n1 = {};
        PixelColour n2 = {};
        PixelColour n3 = {};
        
        int x0 = floor(texPos.x);
        int x1 = x0+1;
        
        int y0 = floor(texPos.y);
        int y1 = y0+1;
        
        
        
        PixelColour n0 = PixelFormat_getColour(src,x0,y0);
        
        if(x1 < w)
        {
            n1 = PixelFormat_getColour(src,x1,y0);
        }
        
        
        if(y1 < h)
        {
            n2 = PixelFormat_getColour(src,x0,y1);
        }
        
        if(x1 < w && y1 < h)
        {
            n3 = PixelFormat_getColour(src,x1,y1);
        }
        
        float tx = texPos.x - x0;
        float ty = texPos.y - y0;
        
        
        
        PixelColour c0 = PixelColourMix(n0, n1, tx);
        PixelColour c1 = PixelColourMix(n2, n3, tx);
        
        sampleCol = PixelColourMix(c0, c1, ty);
        
    }
    
    // cubic
    return sampleCol;
}
**/