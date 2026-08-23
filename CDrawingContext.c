#include "CDrawingContext.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "CLMath.h"
#include "CPixelColour.h"



void drawRasterLineDDA();

void shade(int x, int y)
{
    // should be removed once clipping is added
    if(x < 0 || x >= 1280 || y < 0 || y >= 800)
    {
        return;
    }


    int index = (y * 1280*3) + (x*3);
                
              
                // Pure CPU pixel manipulation
                tmpBuffer[index + 0] = 255;
                tmpBuffer[index + 1] = 255;
                tmpBuffer[index + 2] = 255;
}

void shadeC(int x, int y, CPixelColour c)
{
    int index = (y * 1280*3) + (x*3);
                
              
                // Pure CPU pixel manipulation
                tmpBuffer[index + 0] = c.r * 255;
                tmpBuffer[index + 1] = c.g * 255;
                tmpBuffer[index + 2] = c.b * 255;
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

int imax(int a, int b)
{
    return (a > b) ? a : b;
}

int imin(int a, int b)
{
    return (a < b) ? a : b;
}

void drawRasterLineBresham(f4 a, f4 b)
{
    // Bresenham's line algorithm implementation
    int x0 = (int)a.x;
    int y0 = (int)a.y;
    int x1 = (int)b.x;
    int y1 = (int)b.y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        shade(x0, y0); // Shade the pixel at (x0, y0)

        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
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

float edgeFunction(f3 a, f3 b, f3 c);
inline float edgeFunction(f3 a, f3 b, f3 c) {
    
    f3 ba = f3Sub(b, a);
    f3 ca = f3Sub(c, a);
    
   //hort hand for area = f3(f3Cross(ba, ca)); its the z cros product
    float area = (ba.x * ca.y) - (ca.x * ba.y);
    
    return area;
}

void rasterTrianglePoint(PixelPoint p, PixelPoint a, PixelPoint b, PixelPoint c)
{
    f3 pf = {p.x, p.y, 0};
    f3 af = {a.x, a.y, 0};
    f3 bf = {b.x, b.y, 0};
    f3 cf = {c.x, c.y, 0};

    float area = edgeFunction(af, bf, cf);

    float w0 = edgeFunction(af, bf, pf) / area;
    float w1 = edgeFunction(bf, cf, pf) / area;
    float w2 = edgeFunction(cf, af, pf) / area;

    if(w0 >= 0 && w1 >= 0 && w2 >= 0)
    {

        CPixelColour C0 = {1.0, 0.0, 0.0, 1.0}; // Red
        CPixelColour C1 = {0.0, 1.0, 0.0, 1.0}; // Green
        CPixelColour C2 = {0.0, 0.0, 1.0, 1.0}; // Blue

        float z0 = 1.0f; // Depth for vertex a
        float z1 = 1.0f; // Depth for vertex b
        float z2 = 1.0f; // Depth for vertex c

        float inv_z0 = 1.0f / z0;
        float inv_z1 = 1.0f / z1; 
        float inv_z2 = 1.0f / z2;

        float interpolated_inv_z = w0 * inv_z0 + w1 * inv_z1 + w2 * inv_z2;

        float r_over_z = w0 * (C0.r * inv_z0) + w1 * (C1.r * inv_z1) + w2 * (C2.r * inv_z2);
        float g_over_z = w0 * (C0.g * inv_z0) + w1 * (C1.g * inv_z1) + w2 * (C2.g * inv_z2);
        float b_over_z = w0 * (C0.b * inv_z0) + w1 * (C1.b * inv_z1) + w2 * (C2.b * inv_z2);

        // 4. Multiply by z (divide by 1/z) to recover true values
        float true_z = 1.0f / interpolated_inv_z;
        
        CPixelColour outColour = {};
        
        outColour.r = r_over_z * true_z;
        outColour.g = g_over_z * true_z;
        outColour.b = b_over_z * true_z;

        outColour.a = 1.0f; // Assuming full opacity for this example

        shadeC(p.x, p.y, outColour);
    }
}

void rasterTrianglePointINT(PixelPoint p, PixelPoint a, PixelPoint b, PixelPoint c)
{
    int w0 = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    int w1 = (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x);
    int w2 = (a.x - c.x) * (p.y - c.y) - (a.y - c.y) * (p.x - c.x);

    if(w0 >= 0 && w1 >= 0 && w2 >= 0)
    {
        shade(p.x,p.y);
    }
}


void drawRasterTriangle(PixelPoint a, PixelPoint b, PixelPoint c)
{
    // get bounds of a b and c
    int minX = imin(imin(a.x, b.x), c.x);
    int maxX = imax(imax(a.x, b.x), c.x);
    int minY = imin(imin(a.y, b.y), c.y);
    int maxY = imax(imax(a.y, b.y), c.y);

    for(int y = minY; y <= maxY; y++)
    {
        for(int x = minX; x <= maxX; x++)
        {
            PixelPoint p = {x,y};

            rasterTrianglePoint(p,a,b,c);
        }
    }
}