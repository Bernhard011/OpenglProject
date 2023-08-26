#pragma once


class Math {
public: 
	float Lerp(float a, float b, float t) {
		if (t >= 1)
			t = 1;
		float result = a * (1.0f - t) + (b * t); //Formula for a Lerp is: a*(1-t)+(b*t)
		return result;
	}
};