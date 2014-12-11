
#include "define.h"

#include "settings.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include "dialogInfo.h"
#include "math.h"
#include "paint.h"
#include "saveload.h"
#include "UI.h"

#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")


// main.cpp
int main();
void mainTimerChecking(int elapsedTime);
void mainEventCheck(sf::RenderWindow &winHandle);
void mainPaint(sf::RenderWindow &winHandle);
// math.cpp
int a_round(float num);


extern sf::Font gl_mainFont;
extern int debugInt[8];
extern int gl_dialogInfoCounter;
extern dialogInfo gl_dialogInfo[OBJECT_LIMIT];