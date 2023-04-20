#include "matrix.hpp"

void multiplyMatrices(int la, int ca, const float* A, // matriz A, dimensões la x ca
                      int lb, int cb, const float* B, // matriz B, dimensões lb x cb
                      float* R, int* lr = NULL, int* cr = NULL){ // matriz R, dimensões ca x lb
    if (lr) *lr = ca; // Se for NULL, então é porque não se pretende guardar as dimensões da matriz resultado
    if (cr) *cr = lb; // Se for NULL, então é porque não se pretende guardar as dimensões da matriz resultado
    if (ca == lb) {
		for (int i = 0; i < la; i++) {
			for (int j = 0; j < cb; j++) {
				R[i*cb+j] = 0;
				for (int k = 0; k < ca; k++) {
					R[i*cb+j] += A[i*ca+k] * B[k*cb+j];
				}
			}
		}
    }
} 

void buildRotMatrix(const float *x, const float *y, const float *z, float *m) {
	m[0]  = x[0]; m[1]  = x[1]; m[2]  = x[2]; m[3]  = 0;
	m[4]  = y[0]; m[5]  = y[1]; m[6]  = y[2]; m[7]  = 0;
	m[8]  = z[0]; m[9]  = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0   ; m[13] =    0; m[14] =    0; m[15] = 1;
}

void cross(const float *a, const float *b, float *res) {
	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {
	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[16] = {-0.5f,  1.5f, -1.5f,  0.5f,
				    1.0f, -2.5f,  2.0f, -0.5f,
				   -0.5f,  0.0f,  0.5f,  0.0f,
				    0.0f,  1.0f,  0.0f,  0.0f}; // 4x4
	float P[12] = {p0[0],p0[1],p0[2],
				   p1[0],p1[1],p1[2], 
				   p2[0],p2[1],p2[2],
				   p3[0],p3[1],p3[2]}; //4x3
	float A[12]; // 4x3
	// Compute A = M * P
    multiplyMatrices(4,4,m,4,3,P,A);
	float T[4] = {t*t*t,t*t,t,1}, DERT[4] = {3*t*t,2*t,1,0}; // T-> 1x4, DERT -> 1x4
	// Compute pos = T * A
	// multiplyMatrices(1,4,4,3,T,A,pos);
    multiplyMatrices(1,4,T,4,3,A,pos);
	// compute deriv = T' * A
	multiplyMatrices(1,4,DERT,4,3,A,deriv);
}
