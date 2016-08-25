//
// EngMath.h
//
// Generally modeled after android.opengl.matrix.java. Source:
// https://android.googlesource.com/platform/frameworks/base/+/froyo/opengl/java/android/opengl/Matrix.java
// Also GLM and GL/GLU.
// Then, modeled after much of the theoretical seeing here:
// http://www.opengl-tutorial.org/assets/faq_quaternions/index.html#Q60
// 
// TODO: Organize better, make this more functional, expand on it, better names, and better/actual documentation.
//

#ifndef ENGMATH_H
#define ENGMATH_H

// Make certain operations easier for me.
#define TRUE 1
#define FALSE 0

#include "Common/Precomp.h"
#include <math.h>

typedef float Vector2[2];		// float[2]
typedef float Vector3[3];		// float[3]
typedef float Vector4[4];		// float[4]
typedef float Quaternion[4];	// float[4]
typedef float Matrix3[9];		// float[9]
typedef float Matrix4[16];		// float[16]

static const Matrix4 identityMat4 = {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};

static const unsigned int SIZEOF_VEC2 = sizeof(float) * 2;
static const unsigned int SIZEOF_VEC3 = sizeof(float) * 3;
static const unsigned int SIZEOF_VEC4 = sizeof(float) * 4;
static const unsigned int SIZEOF_MAT3 = sizeof(float) * 9;
static const unsigned int SIZEOF_MAT4 = sizeof(float) * 16;

#if defined (__cplusplus)
extern "C" {
#endif

//
// MVP Matrix4 Functions
//
void getIdentityMatrix(Matrix4 m);
void getPerspectiveMatrixRH(Matrix4 m, float fovy, float aspect,
	float zNear, float zFar);
void getPerspectiveMatrixLH(Matrix4 m, float fovy, float aspect,
	float zNear, float zFar);
void getOrthographicMatrix(Matrix4 m, float left, float right,
	float bottom, float top, float zNear, float zFar);
void getLookAtRH(Matrix4 m, float eyeX, float eyeY, float eyeZ,
	float centerX, float centerY, float centerZ, 
	float upX, float upY, float upZ);
void getLookAtLH(Matrix4 m, float eyeX, float eyeY, float eyeZ,
	float centerX, float centerY, float centerZ,
	float upX, float upY, float upZ);

//
// Transformation Matrix Methods
//
void translateMatrix(Matrix4 m, float x, float y, float z);
void eulerRotateMatrix(Matrix4 m, int inDegrees, float angle_x, float angle_y, float angle_z);
void scaleMatrix(Matrix4 m, float x, float y, float z);
void transposeMatrix(Matrix4 m, Matrix4 mT);
void convertRHtoLH(Matrix4 mLH, Matrix4 mRH);

//
// Arithmetic
//
float lengthVec3(float x, float y, float z);
void mat4Mul(Matrix4 result, Matrix4 a, Matrix4 b);
void vec4Mul(Vector4 result, Matrix4 a, Vector4 b);

#if defined (__cplusplus)
}
#endif

#endif // ENGMATH_H

