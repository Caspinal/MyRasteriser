#include "CPixelFormat.h"
#include <stdio.h>
#include <stdlib.h>
#include "CLMath.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

struct compoent 
{
    char* name;
    char* type;
    // min max vals? 
    size_t size;
    size_t byteOffset;

}

void CPixelFormatInitWithEncoding(CPixelFormat* pf, char* encoding)
{

    // try and find implementaion;


    //use slow path.

    // find component order

   int encodingLength = strlen(encoding);

   // struct for this? 
    int r = -1;
    size_t rSize;
    // type? f unorm? 
    int g = -1;
    size_t gSize;
    int b = -1;
    size_t bSize;
    int a = -1;
    size_t aSize;

  

    
   for(int i = 0; i < encodingLength; i++)
   {
        if(tolower(encoding[i]) == 'r')
        {
            r = i;
            continue;
        }

        if(tolower(encoding[i]) == 'g')
        {
            g = i;
            continue;
        }


        if(tolower(encoding[i]) == 'b')
        {
            b = i;
            continue;
        }

        if(tolower(encoding[i]) == 'a')
        {
            a = i;
            continue;
        }

        if(isdigit(encoding[i]))
        {
           
            char digits[100] = "";
            int di = 0;
            while (isdigit(encoding[i]) && i < encodingLength)
            {
                        digits[di] = encoding[i];
                        di++;
                        digits[di] = '\0';
                        
                      i++;
                
            };
            
           // back progagate found components and assign 
           // cehck if equel to found components; 

            printf("%s \n",digits);

            continue;
        }

    }

    // find bits
    // sum bits
    // alocate memory
     


};

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