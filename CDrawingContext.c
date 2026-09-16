#include "CDrawingContext.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "CLMath.h"
#include "CPixelColour.h"



void drawRasterLineDDA();

void shadeC(int x, int y, CPixelColour c)
{
    // should be removed once clipping is added
    if(x < 0 || x >= 1280 || y < 0 || y >= 800)
    {
        return;
    }
    int index = (y * 1280*3) + (x*3);
                
              
                // Pure CPU pixel manipulation
                tmpBuffer[index + 0] = c.r * 255;
                tmpBuffer[index + 1] = c.g * 255;
                tmpBuffer[index + 2] = c.b * 255;
}

void shade(int x, int y)
{
    shadeC(x,y,(CPixelColour){1.0,1.0,1.0,1.0});
}

void shadeA(int x, int y, float a)
{
    shadeC(x,y,(CPixelColour){1.0*a,1.0*a,1.0*a,1.0}); // no actual blending here.
}

bool depthTest(int x, int y, float z)
{
    // should be removed once clipping is added
    if(x < 0 || x >= 1280 || y < 0 || y >= 800)
    {
        return false;
    }
   float target = tmpDepthBuffer[(y * 1280) + x];
    return  z <= target;
}

void depthSet(int x, int y, float z)
{ 
    // should be removed once clipping is added
    if(x < 0 || x >= 1280 || y < 0 || y >= 800)
    {
        return;
    }
    tmpDepthBuffer[(y * 1280) + x] = z;
}


void drawRasterRect(int x, int y, int width, int height)
{

}


void drawRasterPoint(int xc, int yc, int r)
{
    
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


float clipDist(f4 a)
{
    // Evaluates near-plane distance in homogeneous clip space (OpenGL: z + w >= 0)
    return a.z + a.w; 
}

// MUST be called BEFORE perspective divide (while w is intact)
bool clipTriangleNearPlane(f4 a, f4 b, f4 c, f4* vertexListOut, int* triangleCountOut)
{
    bool didClip = false;

    float dists[3] = { clipDist(a), clipDist(b), clipDist(c) };
    f4 verts[3] = { a, b, c };

    int insideCount = 0;
    int outsideCount = 0;

    f4 inside[3];
    f4 outside[3];

    for (int i = 0; i < 3; i++)
    {
        if (dists[i] >= 0.0f)
            inside[insideCount++] = verts[i];
        else
            outside[outsideCount++] = verts[i];
    }

    switch (insideCount)
    {
    case 0:
        didClip = true; 
        *triangleCountOut = 0;
        break;

    case 1:
        {
            didClip = true; 
            float inside0  = clipDist(inside[0]);
            float outside0 = clipDist(outside[0]);
            float outside1 = clipDist(outside[1]);

            float t0 = inside0 / (inside0 - outside0);
            float t1 = inside0 / (inside0 - outside1);

            vertexListOut[0] = inside[0];
            vertexListOut[1] = lerpf4(inside[0], outside[0], t0);
            vertexListOut[2] = lerpf4(inside[0], outside[1], t1);

            *triangleCountOut = 1;
        }
        break;

    case 2:
        {
            didClip = true; 
            float inside0  = clipDist(inside[0]);
            float inside1  = clipDist(inside[1]);
            float outside0 = clipDist(outside[0]); // Only 1 outside vertex!

            // Interpolate inside[0] -> outside[0] and inside[1] -> outside[0]
            float t0 = inside0 / (inside0 - outside0);
            float t1 = inside1 / (inside1 - outside0);

            f4 v0_new = lerpf4(inside[0], outside[0], t0);
            f4 v1_new = lerpf4(inside[1], outside[0], t1);

            // First triangle of the output quad
            vertexListOut[0] = inside[0];
            vertexListOut[1] = inside[1];
            vertexListOut[2] = v0_new;

            // Second triangle of the output quad
            vertexListOut[3] = inside[1];
            vertexListOut[4] = v1_new;
            vertexListOut[5] = v0_new;

            *triangleCountOut = 2;
        }
        break;

    case 3:
        didClip = false;
        vertexListOut[0] = a;
        vertexListOut[1] = b;
        vertexListOut[2] = c;
        *triangleCountOut = 1;
        break;
    }

    return didClip;
}

inline float edgeFunction(f3 a, f3 b, f3 c) {
    
    f3 ba = f3Sub(b, a);
    f3 ca = f3Sub(c, a);
    
   //short hand for area = f3(f3Cross(ba, ca)); its the z cros product
    float area = (ba.x * ca.y) - (ba.y * ca.x);
    
    return area;
}

float topleftBias(f3 a, f3 b)
{
    f2 d = (f2){ b.x - a.x, b.y - a.y };

    // CCW Winding Top-Left Definition:
    // Top edge: horizontal (d.y == 0) and pointing left (d.x < 0)
    // Left edge: going down in screen space (d.y > 0)
    bool isTopEdge  = (d.y == 0.0f && d.x < 0.0f);
    bool isLeftEdge = (d.y > 0.0f);


    return (isTopEdge || isLeftEdge) ? 0.0f : -0.0001f;
}


f3 snap_to_subpixel(f4 v) {

    float SUBPIXEL_STEP =  16.0f;
    return (f3){
        .x = floorf(v.x * SUBPIXEL_STEP + 0.5f) / SUBPIXEL_STEP,
        .y = floorf(v.y * SUBPIXEL_STEP + 0.5f) / SUBPIXEL_STEP,
        .z = v.z
    };
}

void rasterTrianglePointV(PixelPoint p, Vertex av, Vertex bv, Vertex cv)
{

    f4 a = av.pos;
    f4 b = bv.pos;
    f4 c = cv.pos;

   // 1. Sample at pixel CENTER (p.x + 0.5, p.y + 0.5)
    f3 pf = { (float)p.x + 0.5f, (float)p.y + 0.5f, 0.0f };
    // f3 af = snap_to_subpixel(a);
    // f3 bf = snap_to_subpixel(b);
    // f3 cf = snap_to_subpixel(c);
    f3 af = { a.x, a.y, 0.0f };
    f3 bf = { b.x, b.y, 0.0f };
    f3 cf = { c.x, c.y, 0.0f };
    // f3 af = { (int)a.x+0.5f, (int)a.y+0.5f, 0.0f };
    // f3 bf = { (int)b.x+0.5f,(int)b.y+0.5f, 0.0f };
    // f3 cf = { (int)c.x+0.5f, (int)c.y+0.5f, 0.0f };

    float area = edgeFunction(af, bf, cf);
    if (area == 0.0f) return; // Degenerate triangle check

    float invArea = 1.0f / area;

    // 2. Compute normalized barycentric coordinates first
    float w0 = edgeFunction(bf, cf, pf); // Weight for vertex A
    float w1 = edgeFunction(cf, af, pf); // Weight for vertex B
    float w2 = edgeFunction(af, bf, pf); // Weight for vertex C

    // 3. Apply bias directly to normalized weights
   float w0b = topleftBias(bf, cf);
   float w1b = topleftBias(cf, af);
    float w2b = topleftBias(af, bf);

    if ((w0+w0b) >= 0.0f && (w1+w1b) >= 0.0f && (w2+w2b) >= 0.0f)
    {
         float invArea = 1.0f / area;

            w0 *= invArea; 
            w1 *= invArea; 
            w2 *= invArea; 

        // 2. Linear screen-space depth (if a.z, b.z, c.z are post-divide NDC z [0, 1])
           float current_z = w0 * a.z + w1 * b.z + w2 * c.z;

        // Perspective-correct color interpolation using clip W (a.w, b.w, c.w)
        float inv_w0 = 1.0f / a.w;
        float inv_w1 = 1.0f / b.w;
        float inv_w2 = 1.0f / c.w;
        float interpolated_inv_w = w0 * inv_w0 + w1 * inv_w1 + w2 * inv_w2;

        CPixelColour C0 = av.col;
        CPixelColour C1 = bv.col;
        CPixelColour C2 = cv.col;

        float r_over_w = w0 * (C0.r * inv_w0) + w1 * (C1.r * inv_w0) + w2 * (C2.r * inv_w0);
        float g_over_w = w0 * (C0.g * inv_w1) + w1 * (C1.g * inv_w1) + w2 * (C2.g * inv_w1);
        float b_over_w = w0 * (C0.b * inv_w2) + w1 * (C1.b * inv_w2) + w2 * (C2.b * inv_w2);

        float true_w = 1.0f / interpolated_inv_w;

        CPixelColour outColour = {
            .r = r_over_w * true_w,
            .g = g_over_w * true_w,
            .b = b_over_w * true_w,
            .a = 1.0f
        };

        if (current_z < 0.0f || current_z > 1.0f) {
            return;
        }

        if (depthTest(p.x, p.y, current_z)) {
            shadeC(p.x, p.y, outColour);
            depthSet(p.x, p.y, current_z);
        }
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
void drawRasterTriangleV(Vertex av, Vertex bv, Vertex cv);
void DrawQuad(Vertex* v, f4x4 viewport)
{
    // Transform all 4 unique vertices ONCE to avoid duplicate work or float drift
    v[0].pos = f4ClipToScreen(v[0].pos, viewport);
    v[1].pos = f4ClipToScreen(v[1].pos, viewport);
    v[2].pos = f4ClipToScreen(v[2].pos, viewport);
    v[3].pos = f4ClipToScreen(v[3].pos, viewport);

   // Triangle 1 (CCW): v[0] -> v[2] -> v[1]
    drawRasterTriangleV(v[0], v[2], v[1]);

    // Triangle 2 (CCW): v[0] -> v[3] -> v[2]
    drawRasterTriangleV(v[0], v[3], v[2]);
}

void rasterEdge(Vertex a, Vertex b, Vertex av, Vertex bv, Vertex cv)
{
    int x0 = a.pos.x;
    int y0 = a.pos.y;
    int x1 = b.pos.x;
    int y1 = b.pos.y;

    int dx = x0 - x1;
    int dy = y0 - y1;


    int extent = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);
    
        float dxs = (float)dx / extent;
        float dys = (float)dy / extent;
        float x = x1;
        float y = y1;

        for(int i = 0; i <= extent; i++)
        {
            CPixelColour c = (CPixelColour){1.0,0.0,0.0,1.0};
            //shadeC(x,y,c);
            PixelPoint p = {x,y};
            rasterTrianglePointV(p,av,bv,cv);
            x += dxs;
            y += dys;
        }
}



void fillBottomFlatTriangle2(Vertex top, Vertex middle, Vertex bottom, Vertex av, Vertex bv, Vertex cv)
{

Vertex vLeft = middle;
Vertex vRight = bottom;

if(bottom.pos.x < middle.pos.x)
{
vLeft = bottom;
vRight = middle;
}

// top.pos.y-=1.0;
// vLeft.pos.y+=1.0;
// vLeft.pos.x-=1.0;

// vRight.pos.y+=1.0;
// vRight.pos.x+=1.0;

float leftSlope = (vLeft.pos.x - top.pos.x) / (vLeft.pos.y - top.pos.y);
float rightSlope = (vRight.pos.x - top.pos.x) / (vRight.pos.y - top.pos.y);

// Use ceilf to find the first integer scanline STRICTLY INSIDE the triangle
int startY = top.pos.y;//(int)ceilf(top.pos.y);
int endY = (middle.pos.y+0.5f);// - 1; // -1 applies standard top-left fill rules

// Subpixel pre-step to the first actual integer scanline
float left = top.pos.x;// + ((float)startY - top.pos.y) * leftSlope;
float right = top.pos.x;// + ((float)startY - top.pos.y) * rightSlope;

for (int y = startY; y < endY; y++)
{
int xStart = left;//(int)ceilf(left);
int xEnd = right;//(int)ceilf(right);// - 1;

for (int x = xStart; x <= xEnd; x++)
{
PixelPoint p = {x,y};
//shade(x,y);
rasterTrianglePointV(p,av,bv,cv);
}

left += leftSlope;
right += rightSlope;
}


rasterEdge(top, vLeft, av, bv, cv);
rasterEdge(vLeft, vRight, av, bv, cv); 
rasterEdge(top, vRight, av, bv, cv);        

}

void fillTopFlatTriangle2(Vertex top, Vertex middle, Vertex bottom, Vertex av, Vertex bv, Vertex cv)
{
// flat top
Vertex vLeft = top;
Vertex vRight = middle;

if(middle.pos.x < top.pos.x)
{
vLeft = middle;
vRight = top;
}


float leftSlope = (vLeft.pos.x - bottom.pos.x) / (vLeft.pos.y - bottom.pos.y);
float rightSlope = (vRight.pos.x - bottom.pos.x) / (vRight.pos.y - bottom.pos.y);

//float left = bottom.pos.x;
// float right = bottom.pos.x;

int startY = bottom.pos.y;//(int)ceilf(bottom.pos.y);
int endY = middle.pos.y;//(int)ceilf(middle.pos.y);//-1; // -1 applies standard top-left fill rules

float left = bottom.pos.x;//bottom.pos.x + ((float)startY - bottom.pos.y) * leftSlope;
float right = bottom.pos.x;// + ((float)startY - bottom.pos.y) * rightSlope;

for (int y = startY; y > endY; y--)
{
int xStart = left;
int xEnd = right;//(int)ceilf(right);// - 1;

for (int x = xStart; x <= xEnd; x++)
{
PixelPoint p = {x,y};
//shade(x,y);
rasterTrianglePointV(p,av,bv,cv);
}


left -= leftSlope;
right -= rightSlope;
}

rasterEdge(bottom, vLeft, av, bv, cv);
rasterEdge(vLeft, vRight, av, bv, cv); 
rasterEdge(bottom, vRight, av, bv, cv);   

}


int compareY(const void* a, const void* b)
{
    Vertex stopA = *((Vertex*)a);
    Vertex stopB= *((Vertex*)b);
    
    if( stopA.pos.y < stopB.pos.y)
    {
        return -1;
    }
   
    if( stopA.pos.y > stopB.pos.y)
    {
        return 1;
    }
    
    
    return 0;
}


void drawRasterTriangleV(Vertex av, Vertex bv, Vertex cv)
{


   // av.pos = (f4){640,0,0,0};
   // bv.pos = (f4){0,800,0,0};
   // cv.pos = (f4){1289,800,0,0};

    float edge = edgeFunction(f4ToF3(av.pos),f4ToF3(bv.pos),f4ToF3(cv.pos));

    if(edge == 0 || edge < 0) // back face culling
    {
        return;
    }


   

    Vertex pointsYSort[3] = {av,bv,cv};
    
    qsort(&pointsYSort[0], 3, sizeof(Vertex), compareY);
    
 
    Vertex top = pointsYSort[0];
    Vertex middle = pointsYSort[1];
    Vertex bottom = pointsYSort[2];

  
   


    if(top.pos.y == middle.pos.y)
    {
        // flat top
        fillTopFlatTriangle2(top, middle, bottom, av, bv, cv);

    }else if(middle.pos.y == bottom.pos.y)
    {
        // flat bottom
        fillBottomFlatTriangle2(top, middle, bottom, av, bv, cv);

    }else
    {

        float y = middle.pos.y;
        float s = (bottom.pos.x - top.pos.x) / (bottom.pos.y - top.pos.y);
        float x = top.pos.x + (y- top.pos.y) * s;

        Vertex new;
        new.pos.x = x;
        new.pos.y = y;

       //  new.pos = f3ToF4(snap_to_subpixel(new.pos));

        fillBottomFlatTriangle2(top,middle,new, av, bv, cv);
        fillTopFlatTriangle2(middle,new,bottom, av, bv, cv);
      
    }

    

}

