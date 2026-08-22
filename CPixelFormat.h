typedef struct
{
    int width;
    int height;
    char* name;
    char* encoding; // for example R8G8B8A8, R32F, etc.
    void* backing; // I may change this to a CValue 
   
   // PixelColour* (*SampleFuncPTR)(void* backing, int x, int y);
} CPixelFormat;