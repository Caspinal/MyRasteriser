#include "CPixelColour.h"


CPixelColour PixelColourMix(CPixelColour a, CPixelColour b, float t)
{
    CPixelColour result = {};
    
    result.r = ((a.r * (1.0f - t)) + (b.r * t));
    result.g = ((a.g * (1.0f - t)) + (b.g * t));
    result.b = ((a.b * (1.0f - t)) + (b.b * t));
    result.a = ((a.a * (1.0f - t)) + (b.a * t));
    
    return result;
}