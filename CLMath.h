//
//  CLMath.h
//  GLUTDisplay
//
//  Created by connor aspinall on 31/03/2024.
//

#ifndef CLMath_h
#define CLMath_h

#include <stdio.h>
#include <math.h>

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} f4;

typedef struct
{
    float x;
    float y;
    float z;
} f3;

typedef struct
{
    float m00;
    float m10;
    float m20;
    
    float m01;
    float m11;
    float m21;
    
    float m02;
    float m12;
    float m22;
    
} f3x3;

typedef struct
{
    float m00;
    float m10;
    float m20;
    float m30;
    
    float m01;
    float m11;
    float m21;
    float m31;
    
    float m02;
    float m12;
    float m22;
    float m32;
    
    float m03;
    float m13;
    float m23;
    float m33;
    
    
} f4x4;




float f3Mag (f3 a);
float f3Dot(f3 a, f3 b);
float f3Dist(f3 a, f3 b);

f3 f3Norm(f3 a);

f3 f3Add(f3 a, f3 b);
f3 f3Sub(f3 a, f3 b);
f3 f3Mul(f3 a, f3 b);
f3 f3Div(f3 a, f3 b);

f3 f3Normal(f3 a, f3 b);
f3 f3Cross(f3 a, f3 b);

f3 f3AddF (f3 a, float s);
f3 f3SubF(f3 a, float s);
f3 f3MulF(f3 a, float s);
f3 f3DivF(f3 a, float s);

f3x3 f3x3MulF3x3(f3x3 a, f3x3 b);
f3 f3x3MulF3(f3x3 a, f3 b);

f3x3 f3x3Zero(void);
f3x3 f3x3Ident(void);


f3x3 f3x3Scale(f3 a);
f3x3 f3x3Skew(void);
f3x3 f3x3Rot(f3 a, float r);

float degToRad(float a);

//f4x4 f4x4Ortho();
//f4x4 f4x4Project();

f4x4 f4x4Trans(f3 a);
f4x4 f4x4Ident(void);
f4x4 f4x4Ortho(float left, float right, float top, float bottom, float near, float far);
f4x4 f4x4Persp(float fovY, float aspect, float near, float far);
f4x4 f4x4Viewport(float x, float y, float width, float height, float minDepth, float maxDepth);
f4x4 f3x3Tof4x4(f3x3 a);
f4x4 f4x4MulF4x4(f4x4 a, f4x4 b);
f3 f4x4MulF3(f4x4 a, f3 b); // useless? 

f4 f4x4MulF4(f4x4 a, f4 b);

float lerpf(float a, float b, float t);
f3 lerpf3(f3 a, f3 b, float t);

float minf(float a, float b);
float maxf(float a, float b);

f4 f4ClipToScreen(f4 clipPos, f4x4 viewport);


#endif /* CLMath_h */
