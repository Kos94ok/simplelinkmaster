
#include "main.h"

float PI = 3.14159f;
float RADTODEG = 180.00f / PI;
float DEGTORAD = PI / 180.00f;


int a_math::round(float num)
{
	return num < 0 ? num - 0.5 : num + 0.5;
}

float a_math::getDistance(int ax, int ay, int bx, int by)
{
	float dx = bx - ax;
	float dy = by - ay;
	return sqrt(dx * dx + dy * dy);
}

float a_math::getAngle(int ax, int ay, int bx, int by)
{
	return RADTODEG * atan2((float)by - ay, (float)bx - ax);
}

float a_math::polarX(float x, float dist, float angle)
{
	return x + dist * cos(angle * DEGTORAD);
}

float a_math::polarY(float y, float dist, float angle)
{
	return y + dist * sin(angle * DEGTORAD);
}

float a_math::randf(float min, float max)
{
	return min + ((float)std::rand() / RAND_MAX) * (max - min);
}

int a_math::rand(int min, int max)
{
	if (min == max) { return min; }
	if (min < max) { return a_math::round(a_math::randf(min, max)); }
	if (min > max) { return a_math::round(a_math::randf(max, min)); }
	return 0;
}

bool isPointInRegion(int pointX, int pointY, int startX, int startY, int sizeX, int sizeY)
{
	if (pointX > startX + sizeX) { return false; }
	if (pointY > startY + sizeY) { return false; }
	if (pointX < startX) { return false; }
	if (pointY < startY) { return false; }
	return true;
}