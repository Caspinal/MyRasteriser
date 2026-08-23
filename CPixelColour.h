typedef struct
{
    float r;
    float g;
    float b;
    float a;

     void* data; //  may add a table for extra bits likes ICC later;
} CPixelColour;


CPixelColour PixelColourMix(CPixelColour a, CPixelColour b, float t);
