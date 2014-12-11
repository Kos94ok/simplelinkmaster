
#include "define.h"

class paint
{
public:
	static void p_singleInfoLink(sf::Vector2f base, float dist, float angle, bool addPoint, sf::Transform &matrix, sf::RenderWindow &winHandle);
	static void p_dialogInfo(int id, bool sel, sf::Transform &matrix, sf::RenderWindow &winHandle);
	static void p_dialogInfoLinks(int id, sf::Transform &matrix, sf::RenderWindow &winHandle);
	static void p_editorBackground(sf::Transform &matrix, sf::RenderWindow &winHandle);
	static void p_menuButton(int id, sf::RenderWindow &winHandle);
	static void p_menuSlider(int id, sf::RenderWindow &winHandle);
	static void p_menuOverlay(sf::RenderWindow &winHandle);
};