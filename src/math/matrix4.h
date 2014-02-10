#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include <iostream>
#include <string.h>
#include "vec3.h"
#include "vec4.h"
#include "mathshelpers.h"

class Matrix4 {
	public:
		union
	    {
	        float data[4][4];
			float array[16];
	    };
	    
		Matrix4(void);
		Matrix4(float elements[16]);
		~Matrix4(void);
		Matrix4& operator=(const Matrix4 &a);

		void ToZero();
		void ToIdentity();
		Vec3 GetPositionVector() const;
		void SetPositionVector(const Vec3 in);
		Vec3 GetScalingVector() const;
		void SetScalingVector(const Vec3 &in);

		static Matrix4 CreateRotation(float degrees, const Vec3 &axis);
		static Matrix4 CreateScale(const Vec3 &scale);
		static Matrix4 CreateTranslation(const Vec3 &translation);
		static Matrix4 CreatePerspective(float znear, float zfar, float aspect, float fov);
		static Matrix4 CreateOrthographic(float znear, float zfar,float right, float left, float top, float bottom);
		static Matrix4 CreateLookAt(const Vec3 &from, const Vec3 &lookingAt);

		static Matrix4 Identity();

		inline Matrix4 operator*(const Matrix4 &a) const {	
			Matrix4 out;

			for(unsigned int r = 0; r < 4; ++r) {
				for(unsigned int c = 0; c < 4; ++c) {
					out.array[c + (r*4)] = 0.0f;
					for(unsigned int i = 0; i < 4; ++i) {
						out.array[c + (r*4)] += this->array[c+(i*4)] * a.array[(r*4)+i];
					}
				}
			}

			return out;
		}

		inline Vec3 operator*(const Vec3 &v) const {
			Vec3 vec;

			float temp;

			vec.x = v.x * array[0] + v.y * array[4] + v.z * array[8]  + array[12];
			vec.y = v.x * array[1] + v.y * array[5] + v.z * array[9]  + array[13];
			vec.z = v.x * array[2] + v.y * array[6] + v.z * array[10] + array[14];

			temp =  v.x * array[3] + v.y * array[7] + v.z * array[11] + array[15];

			vec.x = vec.x / temp;
			vec.y = vec.y / temp;
			vec.z = vec.z / temp;

			return vec;
		};

		inline Vec4 operator*(const Vec4 &v) const {
			return Vec4(
				v.x*array[0] + v.y * array[4] + v.z * array[8]  + v.w * array[12],
				v.x*array[1] + v.y * array[5] + v.z * array[9]  + v.w * array[13],
				v.x*array[2] + v.y * array[6] + v.z * array[10] + v.w * array[14],
				v.x*array[3] + v.y * array[7] + v.z * array[11] + v.w * array[15]
			);
		};

		inline friend std::ostream& operator<<(std::ostream& o, const Matrix4& m) {
			o << "\t" << m.array[0]  << " " << m.array[1]  << " " << m.array[2]  << " " << m.array [3]  << std::endl;
			o << "\t" << m.array[4]  << " " << m.array[5]  << " " << m.array[6]  << " " << m.array [7]  << std::endl;
			o << "\t" << m.array[8]  << " " << m.array[9]  << " " << m.array[10] << " " << m.array [11] << std::endl;
			o << "\t" << m.array[12] << " " << m.array[13] << " " << m.array[14] << " " << m.array [15] << std::endl;
			return o;
		}
};

#endif
