#ifndef __MATRIX3_H__
#define __MATRIX3_H__

#include "matrix4.h"

class Matrix3 {
	public:
	    union
	    {
	        float data[3][3];
	        float array[9];
	    };

	    Matrix3();
		Matrix3(float elements[9]);

	    void Transpose();
	    void ToIdentity();
	    void ToZero();

	    static Matrix3 Identity();
	    static Matrix3 GetInverse(const Matrix4& m);
};

#endif