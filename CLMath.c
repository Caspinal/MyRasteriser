//
//  LMath.c
//  GLUTDisplay
//
//  Created by connor aspinall on 31/03/2024.
//

#include "CLMath.h"


inline f4 f3ToF4(f3 a){
    f4 result = {};
    result.x = a.x;
    result.y = a.y;
    result.z = a.z;
    result.w = 1.0f;
    
    return result;
}

inline f3 f4ToF3(f4 a){
    f3 result = {};
    result.x = a.x;
    result.y = a.y;
    result.z = a.z;
    
    
    return result;
}

inline float f3Mag (f3 a)
{
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline float f3Dot(f3 a, f3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

 float pow2(float a)
{
    return a*a;
}

inline float f3Dist(f3 a, f3 b)
{
    return sqrt(pow2(a.x - b.x)+pow2(a.y - b.y)+pow2(a.z - b.z));
}

inline f3 f3Norm(f3 a)
{
    float m = f3Mag(a);
    return f3DivF(a, m);
}

inline f3 f3Nrml(f3 a,f3 b)
{
    //exit(1);
    float m = f3Mag(a);
    return f3DivF(a, m);
}

inline f3 f3Add(f3 a, f3 b)
{
    f3 result = {};
    
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    
    return result;
}

inline f3 f3Sub(f3 a, f3 b)
{
    f3 result = {};
    
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    
    return result;
}

inline f3 f3Mul(f3 a, f3 b)
{
    f3 result = {};
    
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    
    return result;
}

inline f3 f3Div(f3 a, f3 b)
{
    f3 result = {};
    
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    
    return result;
}

inline f3 f3Cross(f3 a, f3 b)
{
    f3 result = {};
    
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    
    return result;
}

inline f3 f3Normal(f3 a, f3 b) {
    f3 r;

    f3 fab;

    fab.x = a.x - b.x;
    fab.y = a.y - b.y;
    fab.z = 0.0;

    // get unit direction
    r = f3Norm(fab);
    //printf("%f %f %f \n",r.x,r.y,r.z);

    // rotate 90 degress

    float x = -r.y;
    float y = +r.x;

    r = (f3){x,y,0};

    return r;
}

inline f3 f3AddF (f3 a, float s)
{
    f3 result = {};
    
    result.x = a.x + s;
    result.y = a.y + s;
    result.z = a.z + s;
    
    return result;
}

 inline f3 f3SubF(f3 a, float s)
{
    f3 result = {};
    
    result.x = a.x - s;
    result.y = a.y - s;
    result.z = a.z - s;
    
    return result;
}

inline f3 f3MulF(f3 a, float s)
{
    f3 result = {};
    
    result.x = a.x * s;
    result.y = a.y * s;
    result.z = a.z * s;
    
    return result;
}

inline f3 f3DivF(f3 a, float s)
{
    f3 result = {};
    
    result.x = a.x / s;
    result.y = a.y / s;
    result.z = a.z / s;
    
    return result;
}

inline f3 f3x3MulF3(f3x3 a, f3 b)
{
    f3 result = {};
    
    result.x = a.m00 * b.x + a.m10 * b.y + a.m20 * b.z;
    result.y = a.m01 * b.x + a.m11 * b.y + a.m21 * b.z;
    result.z = a.m02 * b.x + a.m12 * b.y + a.m22 * b.z;
    
    return result;
}

 inline f3 f4x4MulF3(f4x4 a, f3 b)
{
    f3 result = {};
    float w = 1.0;
    
    result.x = a.m00 * b.x + a.m10 * b.y + a.m20 * b.z + a.m30 * w;
    result.y = a.m01 * b.x + a.m11 * b.y + a.m21 * b.z + a.m31 * w;
    result.z = a.m02 * b.x + a.m12 * b.y + a.m22 * b.z + a.m32 * w;
   // result.z = a.m02 * b.x + a.m12 * b.y + a.m22 * b.z;
    
    return result;
}

inline f4 f4x4MulF4(f4x4 a, f4 b)
{
    f4 result = {};
    
    result.x = a.m00 * b.x + a.m10 * b.y + a.m20 * b.z + a.m30 * b.w;
    result.y = a.m01 * b.x + a.m11 * b.y + a.m21 * b.z + a.m31 * b.w;
    result.z = a.m02 * b.x + a.m12 * b.y + a.m22 * b.z + a.m32 * b.w;
    result.w = a.m03 * b.x + a.m13 * b.y + a.m23 * b.z + a.m33 * b.w;
    
    return result;
}

inline f3x3 f3x3MulF3x3(f3x3 a, f3x3 b)
{
    f3x3 result = {};
    
    result.m00 = a.m00*b.m00 + a.m10*b.m01 + a.m20*b.m02;
    result.m10 = a.m00*b.m10 + a.m10*b.m11 + a.m20*b.m12;
    result.m20 = a.m00*b.m20 + a.m10*b.m21 + a.m20*b.m22;
    
    result.m01 = a.m01*b.m00 + a.m11*b.m01 + a.m21*b.m02;
    result.m11 = a.m01*b.m10 + a.m11*b.m11 + a.m21*b.m12;
    result.m21 = a.m01*b.m20 + a.m11*b.m21 + a.m21*b.m22;
    
    result.m02 = a.m02*b.m00 + a.m12*b.m01 + a.m22*b.m02;
    result.m12 = a.m02*b.m10 + a.m12*b.m11 + a.m22*b.m12;
    result.m22 = a.m02*b.m20 + a.m12*b.m21 + a.m22*b.m22;
    
    
    return result;
}


inline f4x4 f4x4MulF4x4(f4x4 a, f4x4 b)
{
    f4x4 result = {0};
    
    // Row 0
    result.m00 = a.m00*b.m00 + a.m10*b.m01 + a.m20*b.m02 + a.m30*b.m03;
    result.m10 = a.m00*b.m10 + a.m10*b.m11 + a.m20*b.m12 + a.m30*b.m13;
    result.m20 = a.m00*b.m20 + a.m10*b.m21 + a.m20*b.m22 + a.m30*b.m23;
    result.m30 = a.m00*b.m30 + a.m10*b.m31 + a.m20*b.m32 + a.m30*b.m33;
    
    // Row 1
    result.m01 = a.m01*b.m00 + a.m11*b.m01 + a.m21*b.m02 + a.m31*b.m03;
    result.m11 = a.m01*b.m10 + a.m11*b.m11 + a.m21*b.m12 + a.m31*b.m13;
    result.m21 = a.m01*b.m20 + a.m11*b.m21 + a.m21*b.m22 + a.m31*b.m23;
    result.m31 = a.m01*b.m30 + a.m11*b.m31 + a.m21*b.m32 + a.m31*b.m33;
    
    // Row 2
    result.m02 = a.m02*b.m00 + a.m12*b.m01 + a.m22*b.m02 + a.m32*b.m03;
    result.m12 = a.m02*b.m10 + a.m12*b.m11 + a.m22*b.m12 + a.m32*b.m13;
    result.m22 = a.m02*b.m20 + a.m12*b.m21 + a.m22*b.m22 + a.m32*b.m23;
    result.m32 = a.m02*b.m30 + a.m12*b.m31 + a.m22*b.m32 + a.m32*b.m33; // FIXED: m32
    
    // Row 3
    result.m03 = a.m03*b.m00 + a.m13*b.m01 + a.m23*b.m02 + a.m33*b.m03;
    result.m13 = a.m03*b.m10 + a.m13*b.m11 + a.m23*b.m12 + a.m33*b.m13;
    result.m23 = a.m03*b.m20 + a.m13*b.m21 + a.m23*b.m22 + a.m33*b.m23;
    result.m33 = a.m03*b.m30 + a.m13*b.m31 + a.m23*b.m32 + a.m33*b.m33;
    
    return result;
}

inline f4x4 f3x3Tof4x4(f3x3 a)
{
    f4x4 result = f4x4Ident();
    
    result.m00 = a.m00;
    result.m10 = a.m10;
    result.m20 = a.m20;
    result.m01 = a.m01;
    result.m11 = a.m11;
    result.m21 = a.m21;
    result.m02 = a.m02;
    result.m12 = a.m12;
    result.m22 = a.m22;
    
    return result;
}

inline f3x3 f3x3Ident(void)
{
    f3x3 result = {};
    
    result.m00 = 1;
    result.m10 = 0;
    result.m20 = 0;
    
    result.m01 = 0;
    result.m11 = 1;
    result.m21 = 0;
    
    result.m02 = 0;
    result.m12 = 0;
    result.m22 = 1;
    
    return result;
}

inline f4x4 f4x4Ident(void)
{
    f4x4 result = {};
    
    result.m00 = 1;
    result.m10 = 0;
    result.m20 = 0;
    result.m30 = 0;
    
    result.m01 = 0;
    result.m11 = 1;
    result.m21 = 0;
    result.m31 = 0;
    
    result.m02 = 0;
    result.m12 = 0;
    result.m22 = 1;
    result.m32 = 0;
    
    result.m03 = 0;
    result.m13 = 0;
    result.m23 = 0;
    result.m33 = 1;
    
    return result;
}

inline f4x4 f4x4Ortho(float left, float right, float top, float bottom, float near, float far)
{
    f4x4 result = {};
    
    result.	m00 = 2.0 / (right-left);
    result.m10 = 0;
    result.m20 = 0;
    result.m30 =  - (right+left) / (right-left);
    
    result.m01 = 0;
    result.m11 = 2.0 / (bottom-top);
    result.m21 = 0;
    result.m31 =  - (bottom+top) / (bottom-top);
    
    result.m02 = 0;
    result.m12 = 0;
    result.m22 =  -2.0 / (far-near);
    result.m32 = -(far+near) / (far-near);
    
    result.m03 = 0;
    result.m13 = 0;
    result.m23 = 0;
    result.m33 = 1;
    
    return result;
}

inline f4x4 f4x4Persp(float fovY, float aspect, float near, float far)
{
    f4x4 result = {};
    
    // fovY should be in radians
    float tanHalfFovY = tanf(fovY * 0.5f);
    
    // Column 0
    result.m00 = 1.0f / (aspect * tanHalfFovY);
    result.m01 = 0.0f;
    result.m02 = 0.0f;
    result.m03 = 0.0f;
    
    // Column 1
    result.m10 = 0.0f;
    result.m11 = 1.0f / tanHalfFovY;
    result.m12 = 0.0f;
    result.m13 = 0.0f;
    
    // Column 2
    result.m20 = 0.0f;
    result.m21 = 0.0f;
    result.m22 = -(far + near) / (far - near);
    result.m23 = -1.0f; // Perspective divide (copies -Z into W, row 3)
    
    // Column 3
    result.m30 = 0.0f;
    result.m31 = 0.0f;
    result.m32 = -(2.0f * far * near) / (far - near); // Z translation (row 2)
    result.m33 = 0.0f;
    
    return result;
}

inline f4 f4ClipToScreen(f4 clipPos, f4x4 viewport)
{
    // 1. Perspective Divide (Clip Space -> NDC)
    float w = (clipPos.w == 0.0f) ? 0.00001f : clipPos.w; // Prevent divide by zero
    f4 ndc = { clipPos.x / w, clipPos.y / w, clipPos.z / w, 1.0f }; // W must be reset to 1.0!
    
    // 2. Viewport Transform (NDC -> Screen Space)
    return f4x4MulF4(viewport, ndc);
}

// Creates a matrix that maps Normalized Device Coordinates (NDC) to Screen Space.
// x, y: The lower-left (or upper-left, depending on API) corner of the viewport.
// width, height: The dimensions of the viewport in pixels.
// minDepth, maxDepth: Usually 0.0f and 1.0f.
inline f4x4 f4x4Viewport(float x, float y, float width, float height, float minDepth, float maxDepth)
{
    f4x4 result = f4x4Ident();
    
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;
    float halfDepth = (maxDepth - minDepth) * 0.5f;
    
    // Scale factors (Diagonal)
    result.m00 = halfWidth;
    result.m11 = -halfHeight; // assumes top left is 0,0 make positve for bottom left
    result.m22 = halfDepth;
    
    // Translation factors (4th column)
    result.m30 = x + halfWidth;
    result.m31 = y + halfHeight;
    result.m32 = minDepth + halfDepth; // Equivalent to (minDepth + maxDepth) / 2.0f
    
    return result;
}

inline f4x4 f4x4Trans(f3 a)
{
    f4x4 result = f4x4Ident();
    
    result.m30 = a.x;
    result.m31 = a.y;
    result.m32 = a.z;
    return result;
}

inline f3x3 f3x3Scale(f3 a)
{
    f3x3 result = f3x3Ident();
    
    result.m00 = a.x;
    result.m11 = a.y;
    result.m22 = a.z;
    
    return result;
}

inline f3x3 f3x3Rot(f3 a, float r){

    f3x3 result = f3x3Ident();
    
    float s = sinf(r);
    float c = cosf(r);
    float cm = 1.0-c;
    
    
    result.m00 = c + pow2(a.x) * cm;
    result.m10 = a.x * a.y * cm - (a.z * s);
    result.m20 = a.x * a.z * cm + (a.y * s);
    
    result.m01 = a.y * a.x * cm + (a.z * s);
    result.m11 = c + pow2(a.y) * cm;
    result.m21 = a.y * a.z * cm - (a.x*s);
    
    result.m02 = a.z * a.x * cm - (a.y * s);
    result.m12 = a.z * a.y * cm + (a.x * s);
    result.m22 = c + pow2(a.z) * cm;
    
    /*
    result.m00 = c;
   // result.m10 =
    result.m20 = s;
    
    //result.m01 = a.y * a.x * cm + (a.z * s);
   // result.m11 = c + pow2(a.y) * cm;
   // result.m21 = a.y * a.z * cm - (a.x*s);
    
    result.m02 = -s;
    //result.m12 = a.z * a.y * cm + (a.x * s);
    result.m22 = c;
    */
    
    return result;
}


inline float degToRad(float a)
{
    return  a * (M_PI / 180.0);
}

inline float lerpf(float a, float b, float t) {
    return (((float)a * (1.0f - t)) + ((float)b * t));
}

inline f3 lerpf3(f3 a, f3 b, float t)
{
    f3 r = {};
    r.x =  lerpf(a.x, b.x, t);
    r.y =  lerpf(a.y, b.y, t);
    r.z =  lerpf(a.z, b.z, t);
    return r;
}

inline f4 lerpf4(f4 a, f4 b, float t)
{
    f4 r = {};
    r.x =  lerpf(a.x, b.x, t);
    r.y =  lerpf(a.y, b.y, t);
    r.z =  lerpf(a.z, b.z, t);
    r.w =  lerpf(a.w, b.w, t);
    return r;
}

inline f3 biLerpf3(f3 t, f3 a, f3 b, f3 c, f3 d)
{
    f3 r = {};
  
    f3 ab = lerpf3(a, b, t.x);
    f3 cd = lerpf3(c, d, t.x);
    
    r = lerpf3(ab, cd, t.y);
    
    return r;
}


float minf(float a, float b)
{
    if(a < b)
    {
        return a;
    }
    return b;
}

float maxf(float a, float b)
{
    if(a > b)
    {
        return a;
    }
    return b;
}
