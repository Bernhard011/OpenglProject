#pragma once
#include "Math.h"


class Vector2 {
private:
	Math math;

public:
	float x;
	float y;

public:
	Vector2(float xPos, float yPos) {
		x = xPos;
		y = yPos;
	}
	Vector2(float xPos) {
		x = xPos;
		y = 0;
	}
	Vector2() {
		x = 0;
		y = 0;
	}

public:
	void Lerp(Vector2 a, Vector2 b,  float t) { // Lerp(from, to, time)
		if(t >= 1)
			t = 1;
		float xPos = math.Lerp(a.x, b.x, t);
		float yPos = math.Lerp(a.y, b.y, t);
		x = xPos;
		y = yPos;
	}
	float* ToFloat() const{
		float list[2] = { x, y };
		return list;
	}
	float ToFloatX() const{ //Returns the x value of the vector
		return x;
	}
	float ToFloatY() const{ //Returns the y value of the vector
		return y;
	}
};

class Vector3 {
private:
	Math math;

public:
	float x;
	float y;
	float z;

public:
	Vector3(float xPos, float yPos, float zPos) {
		x = xPos;
		y = yPos;
		z = zPos;
	}
	Vector3(float xPos, float yPos) {
		x = xPos;
		y = yPos;
		z = 0;
	}
	Vector3(float xPos) {
		x = xPos;
		y = 0;
		z = 0;
	}
	Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}

public:
	void Lerp(Vector3 a, Vector3 b, float t) { // Lerp(from, to, time)
		if (t >= 1)
			t = 1;
		float xPos = math.Lerp(a.x, b.x, t);
		float yPos = math.Lerp(a.y, b.y, t);
		float zPos = math.Lerp(a.z, b.z, t);
		x = xPos;
		y = yPos;
		z = zPos;
	}
	float* ToFloat() const{
		float list[3] = { x,y,z };
		return list;
	}
	float ToFloatZ() const{
		return z;
	}
	float ToFloatX() const{ //Returns the x value of the vector
		return x;
	}
	float ToFloatY() const{ //Returns the y value of the vector
		return y;
	}
};

class Vector4 {
private:
	Math math;

public:
	float x;
	float y;
	float z;
	float w;

public:
	Vector4(float xPos, float yPos, float zPos, float wPos) {
		x = xPos;
		y = yPos;
		z = zPos;
		w = wPos;
	}
	Vector4(float xPos, float yPos, float zPos) {
		x = xPos;
		y = yPos;
		z = zPos;
		w = 0;
	}
	Vector4(float xPos, float yPos) {
		x = xPos;
		y = yPos;
		z = 0;
		w = 0;
	}
	Vector4(float xPos) {
		x = xPos;
		y = 0;
		z = 0;
		w = 0;
	}
	Vector4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

public:
	void Lerp(Vector4 a, Vector4 b, float t) { // Lerp(from, to, time)
		if (t >= 1)
			t = 1;
		float xPos = math.Lerp(a.x, b.x, t);
		float yPos = math.Lerp(a.y, b.y, t);
		float zPos = math.Lerp(a.z, b.z, t);
		float wPos = math.Lerp(a.w, b.w, t);
		x = xPos;
		y = yPos;
		z = zPos;
		w = wPos;
	}
	float* ToFloat() const {
		float list[4] = { x, y, z, w };
		return list;
	}
	float ToFloatW() const {
		return w;
	}
	float ToFloatZ() const {
		return z;
	}
	float ToFloatX() const { //Returns the x value of the vector
		return x;
	}
	float ToFloatY() const { //Returns the y value of the vector
		return y;
	}
};
