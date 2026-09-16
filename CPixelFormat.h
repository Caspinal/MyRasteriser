
typedef struct
{
    int width;
    int height;
    char* name;
    char* encoding; // for example R8G8B8A8, R32F, etc.
   // bool hasBacking
    void* backing; // I may change this to a CValue 
   
   // PixelColour* (*SampleFuncPTR)(void* backing, int x, int y);
} CPixelFormat;

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