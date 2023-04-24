#include "matrix.hpp"

void multiplyMatrices(int la, int ca, const float* A, // matriz A, dimensões la x ca
                      int lb, int cb, const float* B, // matriz B, dimensões lb x cb
                      float* R, int* lr = NULL, int* cr = NULL){ // matriz R, dimensões ca x lb
    if (ca == lb) {
		if (lr) *lr = ca; // Se for NULL, então é porque não se pretende guardar as dimensões da matriz resultado
		if (cr) *cr = lb; // Se for NULL, então é porque não se pretende guardar as dimensões da matriz resultado
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
	m[12] =    0; m[13] =    0; m[14] =    0; m[15] = 1;
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

float length(float *a){
	return sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
}

void changeLength(float *a, float newLength){
	normalize(a);
	a[0] *= newLength;
	a[1] *= newLength;
	a[2] *= newLength;
}

void getCatmullRomPoint(float t, vector<float> p0, vector<float> p1, vector<float> p2, vector<float> p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[16] = {-0.5f,  1.5f, -1.5f,  0.5f,
				    1.0f, -2.5f,  2.0f, -0.5f,
				   -0.5f,  0.0f,  0.5f,  0.0f,
				    0.0f,  1.0f,  0.0f,  0.0f}; // 4x4
	// Matriz P -> contém os pontos de controlo da curva
	float P[12] = {p0[0],p0[1],p0[2],
				   p1[0],p1[1],p1[2], 
				   p2[0],p2[1],p2[2],
				   p3[0],p3[1],p3[2]}; //4x3
	float A[12]; // 4x3
	// Compute A = M * P
    multiplyMatrices(4,4,m,4,3,P,A);
	float T[4] = {t*t*t,t*t,t,1}, DERT[4] = {3*t*t,2*t,1,0}; // T-> 1x4, DERT -> 1x4
	// Compute pos = T * A
    if(pos) multiplyMatrices(1,4,T,4,3,A,pos);
	// compute deriv = T' * A
	if(deriv) multiplyMatrices(1,4,DERT,4,3,A,deriv);
}

void getGlobalCatmullRomPoint(float gt, vector<vector<float>> controlPoints, float *pos, float *deriv) {
	size_t POINT_COUNT = controlPoints.size();
	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4]; 
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;	
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT; 
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, controlPoints[indices[0]], controlPoints[indices[1]], controlPoints[indices[2]], controlPoints[indices[3]], pos, deriv);
}

void bezierCurvePoint(float t, vector<vector<float>> controlPoints, float* res, float* deriv){
    float M[16] = { 1.0f,  3.0f, -3.0f, 1.0f,
                    3.0f, -6.0f,  3.0f, 0.0f,
                   -3.0f,  3.0f,  0.0f, 0.0f,
                    1.0f,  0.0f,  0.0f, 0.0f}; // 4x4
	vector<float> p0 = controlPoints[0], p1 = controlPoints[1], p2 = controlPoints[2], p3 = controlPoints[3];
    float P[12] = {p0[0],p0[1],p0[2],
				   p1[0],p1[1],p1[2],
				   p2[0],p2[1],p2[2],
				   p3[0],p3[1],p3[2]}; // 4x3
	float T[4] = {t*t*t,t*t,t,1.0f}, DERT[4] = {3.0f*t*t,2.0f*t,1.0f,0.0f}; // T->1x4; DERT->1x4
	float MP[12]; // 4x3
	multiplyMatrices(4,4,M,4,3,P,MP);
	if(res) multiplyMatrices(1,4,T,4,3,MP,res);
	if(deriv) multiplyMatrices(1,4,DERT,4,3,MP,deriv);
}

void surfacePoint(float u, float v, vector<vector<float>> patch, float* res, float* deriv){
	vector<vector<float>> curve0 = {patch[0],patch[1],patch[2],patch[3]};
	vector<vector<float>> curve1 = {patch[4],patch[5],patch[6],patch[7]};
	vector<vector<float>> curve2 = {patch[8],patch[9],patch[10],patch[11]};
	vector<vector<float>> curve3 = {patch[12],patch[13],patch[14],patch[15]};
	float p0_[3], p1_[3], p2_[3], p3_[3];
	bezierCurvePoint(u,curve0,p0_,NULL);
	bezierCurvePoint(u,curve1,p1_,NULL);
	bezierCurvePoint(u,curve2,p2_,NULL);
	bezierCurvePoint(u,curve3,p3_,NULL);
	vector<float> p0 = {p0_[0],p0_[1],p0_[2]}, p1 = {p1_[0],p1_[1],p1_[2]}, p2 = {p2_[0],p2_[1],p2_[2]}, p3 = {p3_[0],p3_[1],p3_[2]};
	vector<vector<float>> newCurve = {p0,p1,p2,p3};
	bezierCurvePoint(v,newCurve,res,deriv);
}