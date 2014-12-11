
#include "main.h"

void camera::applyTransformI(sf::Vector2i &data)
{
	data.x -= camera::resolutionX / 2;
	data.y -= camera::resolutionY / 2;
	data.x /= viewportZoom;
	data.y /= viewportZoom;
	data.x += camera::resolutionX / 2;
	data.y += camera::resolutionY / 2;
	data.x -= viewportOffsetX;
	data.y -= viewportOffsetY;
}

void camera::applyTransformF(sf::Vector2f &data)
{
	data.x -= camera::resolutionX / 2;
	data.y -= camera::resolutionY / 2;
	data.x /= viewportZoom;
	data.y /= viewportZoom;
	data.x += camera::resolutionX / 2;
	data.y += camera::resolutionY / 2;
	data.x -= viewportOffsetX;
	data.y -= viewportOffsetY;
}