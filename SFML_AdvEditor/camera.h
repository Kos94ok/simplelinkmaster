
//#include "define.h"

class camera
{
public:
	static bool fullscreen;
	static bool borderless;
	static sf::View view;
	static int resolutionX;
	static int resolutionY;	
	static int viewportOffsetX;
	static int viewportOffsetY;
	static float viewportZoom;

	static void applyTransformI(sf::Vector2i &data);
	static void applyTransformF(sf::Vector2f &data);
};