
#include "define.h"

bool isPointInRegion(int pointX, int pointY, int startX, int startY, int sizeX, int sizeY);

class a_math
{
public:
	static int round(float num);
	static float getDistance(int ax, int ay, int bx, int xy);
	static float getAngle(int ax, int ay, int bx, int by);
	static float polarX(float x, float dist, float angle);
	static float polarY(float y, float dist, float angle);
	static float a_math::randf(float min, float max);
	static int a_math::rand(int min, int max);
};