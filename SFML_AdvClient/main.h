
#include "define.h"

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//#include "F:\Workspace\CWork\SFML_AdvEditor\dialogInfo.h"
//#include "F:\Workspace\CWork\SFML_AdvEditor\saveload.h"
//#include "F:\Workspace\CWork\SFML_AdvEditor\math.h"
#include "E:\Workspace\CWork\SFML_AdvEditor\dialogInfo.h"
#include "E:\Workspace\CWork\SFML_AdvEditor\saveload.h"
#include "E:\Workspace\CWork\SFML_AdvEditor\math.h"

#include "camera.h"
#include "UI.h"
#include "game.h"
#include "keyboard.h"
#include "settings.h"
#include "paint.h"

#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")


int main(int argc, char* argv[]);
void mainArgumentParse(int argc, char* argv[], sf::RenderWindow &winHandle);
void mainTimerChecking(int elapsedTime, sf::RenderWindow &winHandle);
void mainEventCheck(sf::RenderWindow &winHandle);
void mainPaint(sf::RenderWindow &winHandle);


extern dialogInfo gl_dialogInfo[OBJECT_LIMIT];
extern int gl_dialogInfoCounter;
extern sf::Font gl_mainFont;
extern int gl_gameTexCount;
extern sf::Texture gl_gameTexture[128];
extern std::wstring gl_gameTexName[128];