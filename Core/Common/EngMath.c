//
// EngMath.c
// 

#include "EngMath.h"

void getIdentityMatrix(Matrix4 m)
{
    int i;
    for (i = 0; i<16; i++) {
		m[i] = 0;
	}
    for (i = 0; i < 16; i += 5) {
		m[i] = 1.0f;
	}
}

void getPerspectiveMatrixRH(Matrix4 m, float fovy, float aspect, float zNear, float zFar)
{
	// Implementation as seen from glm/gtc/matrix_transform.
	const float tanHalfFovy = tanf(fovy / 2.f);

	m[0] = 1.f / (aspect * tanHalfFovy);
	m[5] = 1.f / (tanHalfFovy);
	m[10] = -(zFar + zNear) / (zFar - zNear);
	m[11] = -1.f;
	m[14] = -(2.f * zFar * zNear) / (zFar - zNear);
	
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[12] = m[13] = m[15] = 0;
}
void getPerspectiveMatrixLH(Matrix4 m, float fovy, float aspect, float zNear, float zFar)
{
	// Implementation as seen from D3DXMatrixPerspectiveFovLH.
	const float yScale = 1.f / tanf(fovy / 2);
	const float xScale = yScale / aspect;

	m[0] = xScale;
	m[5] = yScale;
	m[10] = (zFar) / (zFar - zNear);
	m[11] = 1.f;
	m[14] = -(zFar * zNear) / (zFar - zNear);

	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[12] = m[13] = m[15] = 0;
}

void getOrthographicMatrix(Matrix4 m, float left, float right,
	float bottom, float top, float zNear, float zFar)
{
	const float r_width = 1.0f / (right - left);
	const float r_height = 1.0f / (top - bottom);
	const float r_depth = 1.0f / (zFar - zNear);
	const float x = 2.0f * (r_width);
	const float y = 2.0f * (r_height);
	const float z = -2.0f * (r_depth);
	const float tx = -(right + left) * r_width;
	const float ty = -(top + bottom) * r_height;
	const float tz = -(zFar + zNear) * r_depth;
	m[0] = x;
	m[5] = y;
	m[10] = z;
	m[12] = tx;
	m[13] = ty;
	m[14] = tz;
	m[15] = 1.0f;

	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = 0;
}

void getLookAtRH(Matrix4 m, float eyeX, float eyeY, float eyeZ,
	float centerX, float centerY, float centerZ, 
	float upX, float upY, float upZ) 
{
	// Algorithm as seen in gluLookAt() from GLUT.
	// Try to find something else.

	float fx = centerX - eyeX;
	float fy = centerY - eyeY;
	float fz = centerZ - eyeZ;

	// Normalize f
	float rlf = 1.0f / lengthVec3(fx, fy, fz);
	fx *= rlf;
	fy *= rlf;
	fz *= rlf;
	
	// compute s = f x up (x means "cross product")
	float sx = fy * upZ - fz * upY;
	float sy = fz * upX - fx * upZ;
	float sz = fx * upY - fy * upX;
	
	// and normalize s
	float rls = 1.0f / lengthVec3(sx, sy, sz);
	sx *= rls;
	sy *= rls;
	sz *= rls;
	
	// compute u = s x f
	float ux = sy * fz - sz * fy;
	float uy = sz * fx - sx * fz;
	float uz = sx * fy - sy * fx;
	m[0] = sx;
	m[1] = ux;
	m[2] = -fx;
	m[4] = sy;
	m[5] = uy;
	m[6] = -fy;
	m[8] = sz;
	m[9] = uz;
	m[10] = -fz;
	m[15] = 1.0f;

	m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	
	translateMatrix(m, -eyeX, -eyeY, -eyeZ);
}
void getLookAtLH(Matrix4 m, float eyeX, float eyeY, float eyeZ,
	float centerX, float centerY, float centerZ,
	float upX, float upY, float upZ)
{
	// Algorithm as seen in gluLookAt() from GLUT.
	// Try to find something else.

	float fx = eyeX - centerX;
	float fy = eyeY - centerY;
	float fz = eyeZ - centerZ;

	// Normalize f
	float rlf = 1.0f / lengthVec3(fx, fy, fz);
	fx *= rlf;
	fy *= rlf;
	fz *= rlf;

	// compute s = f x up (x means "cross product")
	float sx = fy * upZ - fz * upY;
	float sy = fz * upX - fx * upZ;
	float sz = fx * upY - fy * upX;

	// and normalize s
	float rls = 1.0f / lengthVec3(sx, sy, sz);
	sx *= rls;
	sy *= rls;
	sz *= rls;

	// compute u = s x f
	float ux = sy * fz - sz * fy;
	float uy = sz * fx - sx * fz;
	float uz = sx * fy - sy * fx;
	m[0] = sx;
	m[1] = ux;
	m[2] = -fx;
	m[4] = sy;
	m[5] = uy;
	m[6] = -fy;
	m[8] = sz;
	m[9] = uz;
	m[10] = -fz;
	m[15] = 1.0f;

	m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;

	translateMatrix(m, -eyeX, -eyeY, -eyeZ);
}

void transposeMatrix(Matrix4 m, Matrix4 mT)
{
    int i;
    for (i = 0; i < 4; i++)
	{
		int mBase = i * 4;
		m[i] = mT[mBase];
		m[i + 4] = mT[mBase + 1];
		m[i + 8] = mT[mBase + 2];
		m[i + 12] = mT[mBase + 3];
	}
}

//
// For view matrices, at least...
//
void convertRHtoLH(Matrix4 mLH, Matrix4 mRH)
{
    int i;
    for (i = 0; i < 16; i++)
	{
		if (i % 2 == 0)
			mLH[i] = mRH[i] * -1;
		else
			mLH[i] = mRH[i];
	}
}

float lengthVec3(float x, float y, float z) {
	return (float)sqrt(x * x + y * y + z * z);
}

void mat4Mul(Matrix4 result, Matrix4 a, Matrix4 b)
{

	float	a00 = a[0],  a01 = a[1],  a02 = a[2],  a03 = a[3],
			a10 = a[4],  a11 = a[5],  a12 = a[6],  a13 = a[7],
			a20 = a[8],  a21 = a[9],  a22 = a[10], a23 = a[11],
			a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15],

			b00 = b[0],  b01 = b[1],  b02 = b[2],  b03 = b[3],
			b10 = b[4],  b11 = b[5],  b12 = b[6],  b13 = b[7],
			b20 = b[8],  b21 = b[9],  b22 = b[10], b23 = b[11],
			b30 = b[12], b31 = b[13], b32 = b[14], b33 = b[15];

	result[0] =  b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
	result[1] =  b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
	result[2] =  b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
	result[3] =  b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;
	result[4] =  b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
	result[5] =  b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
	result[6] =  b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
	result[7] =  b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;
	result[8] =  b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
	result[9] =  b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
	result[10] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
	result[11] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;
	result[12] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
	result[13] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
	result[14] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
	result[15] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;
}

void vec4Mul(Vector4 result, Matrix4 a, Vector4 b)
{
	float	a00 = a[0], a01 = a[1], a02 = a[2], a03 = a[3],
			a10 = a[4], a11 = a[5], a12 = a[6], a13 = a[7],
			a20 = a[8], a21 = a[9], a22 = a[10], a23 = a[11],
			a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15],

			b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
		
	result[0] = a00 * b0 + a01 * b1 + a02 * b2 + a03 * b3;
	result[1] = a10 * b0 + a11 * b1 + a12 * b2 + a13 * b3;
	result[2] = a20 * b0 + a21 * b1 + a22 * b2 + a23 * b3;
	result[3] = a30 * b0 + a31 * b1 + a32 * b2 + a33 * b3;
}

//
// 
void translateMatrix(Matrix4 m, float x, float y, float z)
{
    int i;
    for (i = 0; i<4; i++) {
		m[12 + i] += m[i] * x + m[4 + i] * y + m[8 + i] * z;
	}
}

//
// Not yet implemented.
//
void eulerRotateMatrix(Matrix4 m, int inDegrees, float angle_x, float angle_y, float angle_z)
{
	// Algorithm as seen in:
	// http://www.opengl-tutorial.org/assets/faq_quaternions/index.html#Q60
	//

	if (inDegrees) {
		angle_x *= (float)(3.14 / 180.0);
		angle_y *= (float)(3.14 / 180.0);
		angle_z *= (float)(3.14 / 180.0);
	}

	float A = cosf(angle_x);
	float B = sinf(angle_x);
	float C = cosf(angle_y);
	float D = sinf(angle_y);
	float E = cosf(angle_z);
	float F = sinf(angle_z);
	float AD = A * D;
	float BD = B * D;

	m[0] *= C * E;
	m[1] = BD * E + A * F;
	m[2] = -AD * E + B * F;
	m[4] = -C * F;
	m[5] *= -BD * F + A * E;
	m[6] = AD * F + B * E;
	m[8] = D;
	m[9] = -B * C;
	m[10] *= A * C;
	m[15] = 1;

	m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0;
}

void scaleMatrix(Matrix4 m, float x, float y, float z)
{
	m[0] *= x;
	m[5] *= y;
	m[10] *= z;
}

