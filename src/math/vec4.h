#ifndef __VECTOR4_H__
#define __VECTOR4_H__

class Vec4 {
	public:
		float x;
		float y;
		float z;
		float w;

		Vec4(void) {
			x = y = z = w = 1.0f;
		}

		Vec4(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
};

#endif