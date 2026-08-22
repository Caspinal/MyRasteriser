#include "CDrawingContext.h"
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} PixelPoint;

void drawRasterLineDDA();

void shade(int x, int y)
{
    int index = (y * 1280*3) + (x*3);
                
              
                // Pure CPU pixel manipulation
                tmpBuffer[index + 0] = 255;
                tmpBuffer[index + 1] = 255;
                tmpBuffer[index + 2] = 255;
}

void shadeA(int x, int y, float a)
{
    int index = (y * 1280*3) + (x*3);
                
              
                // Pure CPU pixel manipulation
                tmpBuffer[index + 0] = 255 * a;
                tmpBuffer[index + 1] = 255 * a;
                tmpBuffer[index + 2] = 255 * a;
}

void drawRasterRect(int x, int y, int width, int height)
{

}


void drawRasterPoint(int xc, int yc, int r)
{
    

// Midpoint Circle Algorithm implementation

    int x = 0;
    int y = r;
    
    // Initial decision parameter for integer arithmetic
    int p = 1 - r; 

    // Plot the initial points on the axes
    shade(xc + x, yc + y);
    shade(xc - x, yc + y);
    shade(xc + x, yc - y);
    shade(xc - x, yc - y);
    shade(xc + y, yc + x);
    shade(xc - y, yc + x);
    shade(xc + y, yc - x);
    shade(xc - y, yc - x);

    // Loop until the boundary of the first octant is met (x equals y)
    while (x < y) {
        x++; // x always steps forward by 1 pixel in each loop iteration

        if (p < 0) {
            // Midpoint is inside the perimeter; choose the pixel straight ahead (same y)
            p = p + 2 * x + 1;
        } else {
            // Midpoint is outside or on the perimeter; choose the pixel diagonally down (decrement y)
            y--;
            p = p + 2 * x - 2 * y + 1;
        }
        
        // Plot the newly calculated boundary pixel across all 8 octants
        shade(xc + x, yc + y);
        shade(xc - x, yc + y);
        shade(xc + x, yc - y);
        shade(xc - x, yc - y);
        shade(xc + y, yc + x);
        shade(xc - y, yc + x);
        shade(xc + y, yc - x);
        shade(xc - y, yc - x);
    
    }

}

inline int imax(int a, int b)
{
    return (a > b) ? a : b;
}

inline int imin(int a, int b)
{
    return (a > b) ? a : b;
}

void drawRasterLine()
{
    drawRasterLineDDA();
    return;
    int x0 = 0;
    int y0 = 0;
    int x1 = 1279;
    int y1 = 1023;

    int yExtent = abs(y1 - y0);
    int xExtent = abs(x1 - x0);
    
    for(int yi = 0; yi < yExtent; yi++)
    {
        for(int xi = 0; xi < xExtent; xi++)
        {
            float topLeft = ((float)xi) - ((float)yi);
            float topRight = ((float)xi+0.5) - ((float)yi);

            float bottomLeft = ((float)xi) - ((float)yi+0.5);
            float bottomRight = ((float)xi+0.5) - ((float)yi+0.5);


           // float dc = ((float)xi + 0.5) - ((float)yi + 0.5);

            float t = (topLeft + topRight + bottomLeft + bottomRight) / 4.0;

            if(fabs(t) <= 1.5)
            {
                shadeA(xi,yi,(1.5-fabs(t)) / 1.5);
            }
        }
    }

}

void drawRasterLineDDA()
{
    int x0 = 0;
    int y0 = 0;
    int x1 = 100;
    int y1 = 600;

    int dx = x0 - x1;
    int dy = y0 - y1;


    int extent = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);
    
        float dxs = (float)dx / extent;
        float dys = (float)dy / extent;
        float x = x1;
        float y = y1;

        for(int i = 0; i <= extent; i++)
        {
            shade(x,y);
            x += dxs;
            y += dys;
        }
}

void drawRasterTriangle()
{
    
}