
#include "main.h"

sf::Text brushText;
sf::RectangleShape brushRect;
sf::VertexArray brushQuad(sf::Quads, 4);
sf::Vertex brushQuadVertex[4];
sf::CircleShape brushCircle;

// Draw a single link with angle and distance
void paint::p_singleInfoLink(sf::Vector2f base, float dist, float angle, bool addPoint, sf::Transform &matrix, sf::RenderWindow &winHandle)
{
	int lineWidth = 2;

	brushQuad.clear();
	brushQuadVertex[0].color = sf::Color(0, 0, 0);
	brushQuadVertex[0].position.x = a_math::polarX(base.x, lineWidth, angle + 90);
	brushQuadVertex[0].position.y = a_math::polarY(base.y, lineWidth, angle + 90);
	brushQuadVertex[1].color = sf::Color(0, 0, 0);
	brushQuadVertex[1].position.x = a_math::polarX(base.x, lineWidth, angle - 90);
	brushQuadVertex[1].position.y = a_math::polarY(base.y, lineWidth, angle - 90);
	brushQuadVertex[2].color = sf::Color(0, 0, 0);
	brushQuadVertex[2].position.x = a_math::polarX(brushQuadVertex[1].position.x, dist, angle);
	brushQuadVertex[2].position.y = a_math::polarY(brushQuadVertex[1].position.y, dist, angle);
	brushQuadVertex[3].color = sf::Color(0, 0, 0);
	brushQuadVertex[3].position.x = a_math::polarX(brushQuadVertex[0].position.x, dist, angle);
	brushQuadVertex[3].position.y = a_math::polarY(brushQuadVertex[0].position.y, dist, angle);
	brushQuad.append(brushQuadVertex[0]);
	brushQuad.append(brushQuadVertex[1]);
	brushQuad.append(brushQuadVertex[2]);
	brushQuad.append(brushQuadVertex[3]);

	winHandle.draw(brushQuad, matrix);
}

// Draw dialogInfo objects
void paint::p_dialogInfo(int id, bool sel, sf::Transform &matrix, sf::RenderWindow &winHandle)
{
	int screenX = -camera::viewportOffsetX ;
	int screenY = -camera::viewportOffsetY;
	int screenFarX = (camera::resolutionX - camera::viewportOffsetX);
	int screenFarY = (camera::resolutionY - camera::viewportOffsetY);
	// Render only if the object is visible
	if (gl_dialogInfo[id].e_isVisible)
	{
		brushText.setFont(gl_mainFont);

		// Hovered
		brushRect.setPosition(0, 0);
		brushRect.setOrigin(0, 0);
		if (gl_dialogInfo[id].e_isHovered && mouse::attachId != ATTACH_SELECTIONBOX)
		{
			brushRect.setOrigin(-gl_dialogInfo[id].e_boxPosX - 6, -gl_dialogInfo[id].e_boxPosY - 6);
			brushRect.setSize(sf::Vector2f(gl_dialogInfo[id].e_boxSizeX - 12, gl_dialogInfo[id].e_boxSizeY - 11));
			brushRect.setFillColor(sf::Color(0, 0, 0, 0));
			brushRect.setOutlineColor(sf::Color(75, 75, 200, 150));
			brushRect.setOutlineThickness(6.00f);
			winHandle.draw(brushRect, matrix);
		}
		// Main render
		brushRect.setOrigin(-gl_dialogInfo[id].e_boxPosX - 6, -gl_dialogInfo[id].e_boxPosY - 6);
		brushRect.setSize(sf::Vector2f(gl_dialogInfo[id].e_boxSizeX - 12, gl_dialogInfo[id].e_boxSizeY - 11));
		if (!sel)
		{
			if (gl_dialogInfo[id].type == DIALOGTYPE_ACTION || gl_dialogInfo[id].type == DIALOGTYPE_SUCCESS || gl_dialogInfo[id].type == DIALOGTYPE_FAILURE)
				{ brushRect.setFillColor(sf::Color(settings::dialogActionColor.x, settings::dialogActionColor.y, settings::dialogActionColor.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_TELEPORT) { brushRect.setFillColor(sf::Color(settings::dialogTeleportColor.x, settings::dialogTeleportColor.y, settings::dialogTeleportColor.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_VARIABLE) { brushRect.setFillColor(sf::Color(settings::dialogVariableColor.x, settings::dialogVariableColor.y, settings::dialogVariableColor.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_CONDITION) { brushRect.setFillColor(sf::Color(settings::dialogConditionColor.x, settings::dialogConditionColor.y, settings::dialogConditionColor.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_IMAGE) { brushRect.setFillColor(sf::Color(settings::dialogImageColor.x, settings::dialogImageColor.y, settings::dialogImageColor.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_SOUND) { brushRect.setFillColor(sf::Color(settings::dialogSoundColor.x, settings::dialogSoundColor.y, settings::dialogSoundColor.z, 200)); }
			else { brushRect.setFillColor(sf::Color(settings::dialogInfoColor.x, settings::dialogInfoColor.y, settings::dialogInfoColor.z, 200)); }
		}
		else
		{
			if (gl_dialogInfo[id].type == DIALOGTYPE_ACTION || gl_dialogInfo[id].type == DIALOGTYPE_SUCCESS || gl_dialogInfo[id].type == DIALOGTYPE_FAILURE)
				{ brushRect.setFillColor(sf::Color(settings::dialogActionColorSel.x, settings::dialogActionColorSel.y, settings::dialogActionColorSel.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_TELEPORT) { brushRect.setFillColor(sf::Color(settings::dialogTeleportColorSel.x, settings::dialogTeleportColorSel.y, settings::dialogTeleportColorSel.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_VARIABLE) { brushRect.setFillColor(sf::Color(settings::dialogVariableColorSel.x, settings::dialogVariableColorSel.y, settings::dialogVariableColorSel.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_CONDITION) { brushRect.setFillColor(sf::Color(settings::dialogConditionColorSel.x, settings::dialogConditionColorSel.y, settings::dialogConditionColorSel.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_IMAGE) { brushRect.setFillColor(sf::Color(settings::dialogImageColorSel.x, settings::dialogImageColorSel.y, settings::dialogImageColorSel.z, 200)); }
			else if (gl_dialogInfo[id].type == DIALOGTYPE_SOUND) { brushRect.setFillColor(sf::Color(settings::dialogSoundColorSel.x, settings::dialogSoundColorSel.y, settings::dialogSoundColorSel.z, 200)); }
			else { brushRect.setFillColor(sf::Color(settings::dialogInfoColorSel.x, settings::dialogInfoColorSel.y, settings::dialogInfoColorSel.z, 200)); }
		}
		brushRect.setOutlineThickness(3.00f);
		brushRect.setOutlineColor(sf::Color(0, 0, 0));
		// Check for markings
		if (id == dialogInfo::entryPoint) { brushRect.setOutlineColor(sf::Color(0, 0, 255)); }
		else if (gl_dialogInfo[id].type == DIALOGTYPE_SUCCESS) { brushRect.setOutlineColor(sf::Color(150, 255, 150)); }
		else if (gl_dialogInfo[id].type == DIALOGTYPE_FAILURE) { brushRect.setOutlineColor(sf::Color(255, 150, 150)); }
		else if (id == dialogInfo::bsodPoint) { brushRect.setOutlineColor(sf::Color(190, 0, 190)); }
		// Flushing
		winHandle.draw(brushRect, matrix);
		// Editor dialog name
		gl_dialogInfo[id].e_boxTitleDraw.setOrigin(-gl_dialogInfo[id].e_boxPosX, -gl_dialogInfo[id].e_boxPosY);
		winHandle.draw(gl_dialogInfo[id].e_boxTitleDraw, matrix);
		// In-game dialog description
		for (int i = 0; i < gl_dialogInfo[id].g_descriptionStringsUsed; i++)
		{
			gl_dialogInfo[id].e_descriptionDraw[i].setOrigin(-gl_dialogInfo[id].e_boxPosX, -gl_dialogInfo[id].e_boxPosY);
			gl_dialogInfo[id].e_descriptionDraw[i].setPosition(10, 20 * i + 45);
			winHandle.draw(gl_dialogInfo[id].e_descriptionDraw[i], matrix);
		}
	}
}

// Draw links between objects
void paint::p_dialogInfoLinks(int id, sf::Transform &matrix, sf::RenderWindow &winHandle)
{
	brushText.setFont(gl_mainFont);
	int sel = 0;

	for (int i = 0; i < gl_dialogInfo[id].hook_amount; i++)
	{
		if (gl_dialogInfo[id].e_isVisible || gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_isVisible)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);

			// Check for selection
			sel = 0;
			if (mouse::selectDialogInfoBox == id && mouse::selectDialogLink == i)
			{
				if (mouse::attachDialogLinkPoint == ATTACH_POINT_A) { sel = ATTACH_POINT_A; }
				else if (mouse::attachDialogLinkPoint == ATTACH_POINT_B) { sel = ATTACH_POINT_B; }
			}
			// Drawing the line
			int lineWidth = 2;
			bool enableBetterLinks = false;
			
			float angle = a_math::getAngle(
				gl_dialogInfo[id].e_hook_pointAposX[i] + gl_dialogInfo[id].e_boxPosX,
				gl_dialogInfo[id].e_hook_pointAposY[i] + gl_dialogInfo[id].e_boxPosY, 
				gl_dialogInfo[id].e_hook_pointBposX[i] + gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxPosX,
				gl_dialogInfo[id].e_hook_pointBposY[i] + gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxPosY);
			float dist = a_math::getDistance(
				gl_dialogInfo[id].e_hook_pointAposX[i] + gl_dialogInfo[id].e_boxPosX,
				gl_dialogInfo[id].e_hook_pointAposY[i] + gl_dialogInfo[id].e_boxPosY,
				gl_dialogInfo[id].e_hook_pointBposX[i] + gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxPosX,
				gl_dialogInfo[id].e_hook_pointBposY[i] + gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxPosY);

			sf::Vector2f base(gl_dialogInfo[id].e_hook_pointAposX[i] + gl_dialogInfo[id].e_boxPosX, gl_dialogInfo[id].e_hook_pointAposY[i] + gl_dialogInfo[id].e_boxPosY);
			sf::Vector2f curPos = base;
			sf::Vector2f target(gl_dialogInfo[id].e_hook_pointBposX[i] + gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxPosX, gl_dialogInfo[id].e_hook_pointBposY[i] + gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxPosY);
			bool attachAtoLX = false, attachAtoTY = false, attachAtoRX = false, attachAtoBY = false;
			bool attachBtoLX = false, attachBtoTY = false, attachBtoRX = false, attachBtoBY = false;
			float moveAngle = a_math::round(angle / 90.00f) * 90;
			float baseMoveNode = 5, moveNode = baseMoveNode;
			int step = 0;
			// Old link drawing
			if (!enableBetterLinks)
			{
				paint::p_singleInfoLink(base, dist, angle, false, matrix, winHandle);
			}
			// New link drawing
			else
			{
				if (gl_dialogInfo[id].e_hook_pointAposX[i] < 20) { attachAtoLX = true; moveAngle = 0.00f; }
				if (gl_dialogInfo[id].e_hook_pointAposY[i] < 20) { attachAtoTY = true; moveAngle = -90.00f; }
				if (abs(gl_dialogInfo[id].e_hook_pointAposX[i] - gl_dialogInfo[id].e_boxSizeX) < 20) { attachAtoRX = true; moveAngle = 180.00f; }
				if (abs(gl_dialogInfo[id].e_hook_pointAposY[i] - gl_dialogInfo[id].e_boxSizeY) < 20) { attachAtoBY = true; moveAngle = 90.00f; }

				if (gl_dialogInfo[id].e_hook_pointBposX[i] < 20) {
					paint::p_singleInfoLink(target, moveNode * 4, 0.00f, false, matrix, winHandle);
					target.x = a_math::polarX(target.x, moveNode * 4, 0.00f);	target.y = a_math::polarY(target.y, moveNode * 4, 0.00f);
				}
				if (gl_dialogInfo[id].e_hook_pointBposY[i] < 20) {
					paint::p_singleInfoLink(target, moveNode * 4, -90.00f, false, matrix, winHandle);
					target.x = a_math::polarX(target.x, moveNode * 4, -90.00f);	target.y = a_math::polarY(target.y, moveNode * 4, -90.00f);
				}
				if (abs(gl_dialogInfo[id].e_hook_pointBposX[i] - gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxSizeX) < 20) {
					paint::p_singleInfoLink(target, moveNode * 4, 180.00f, false, matrix, winHandle);
					target.x = a_math::polarX(target.x, moveNode * 4, 180.00f);	target.y = a_math::polarY(target.y, moveNode * 4, 180.00f);
				}
				if (abs(gl_dialogInfo[id].e_hook_pointBposY[i] - gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxSizeY) < 20) {
					paint::p_singleInfoLink(target, moveNode * 4, 90.00f, false, matrix, winHandle);
					target.x = a_math::polarX(target.x, moveNode * 4, 90.00f);	target.y = a_math::polarY(target.y, moveNode * 4, 90.00f);
				}

				while ((abs(base.x - target.x) > 5 || abs(base.y - target.y) > 5) && step < 100)
				{
					moveNode = baseMoveNode;

					dist = a_math::getDistance(base.x, base.y, target.x, target.y);
					angle = a_math::getAngle(base.x, base.y, target.x, target.y);
					
					//if (dist > 40) { moveNode *= 6; }
					//else if (dist > 10) { moveNode *= 3; }

					moveAngle = a_math::round(angle / 90.00f) * 90;
					
					moveNode *= sqrt(dist);

					//if (dist > 10) {  }
					//else { paint::p_singleInfoLink(base, dist, angle, false, matrix, winHandle); step = 100; }

					/*if (angle == 90 || angle == -90 && abs(base.y - target.y) < moveNode)
					{
						moveNode = base.x - target.x;
					}
					else if (abs(base.x - target.x) < moveNode) { moveNode = target.x - base.x; }*/

					//if (moveNode < 0) { moveNode *= -1; moveAngle += 180.00f; }

					paint::p_singleInfoLink(base, moveNode, moveAngle, false, matrix, winHandle);
					base.x = a_math::polarX(base.x, moveNode, moveAngle);
					base.y = a_math::polarY(base.y, moveNode, moveAngle);

					step += 1;
				}
			}

			int circleRad = 4;
			brushCircle.setOrigin(
				-gl_dialogInfo[id].e_hook_pointAposX[i] + circleRad - gl_dialogInfo[id].e_boxPosX,
				-gl_dialogInfo[id].e_hook_pointAposY[i] + circleRad - gl_dialogInfo[id].e_boxPosY);
			brushCircle.setRadius(circleRad);
			brushCircle.setOutlineThickness(2);
			brushCircle.setOutlineColor(sf::Color(0, 0, 0));
			if (mouse::selectDialogInfoBox == id && mouse::selectDialogLink == i && mouse::attachDialogLinkPoint == ATTACH_POINT_A)
			{
				brushCircle.setFillColor(sf::Color(0, 200, 0));
			}
			else { brushCircle.setFillColor(sf::Color(0, 255, 0)); }
			winHandle.draw(brushCircle, matrix);

			// dialogInfo (type = DIALOGTYPE_ACTION)
			brushCircle.setOrigin(
				-gl_dialogInfo[id].e_hook_pointBposX[i] + circleRad - gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxPosX,
				-gl_dialogInfo[id].e_hook_pointBposY[i] + circleRad - gl_dialogInfo[gl_dialogInfo[id].hook_actionId[i]].e_boxPosY);
			if (mouse::selectDialogInfoBox == id && mouse::selectDialogLink == i && mouse::attachDialogLinkPoint == ATTACH_POINT_B)
			{
				brushCircle.setFillColor(sf::Color(100, 100, 200));
			}
			else { brushCircle.setFillColor(sf::Color(150, 150, 255)); }
			winHandle.draw(brushCircle, matrix);
		}
	}
}

// Draw background grid
void paint::p_editorBackground(sf::Transform &matrix, sf::RenderWindow &winHandle)
{
	/*brushRect.setOrigin(0, 0);
	brushRect.setSize(sf::Vector2f(1, camera::resolutionY));
	brushRect.setOutlineThickness(0);
	brushRect.setFillColor(sf::Color(0, 100, 0, 255));
	for (int x = (-camera::viewportOffsetX / GRID_STEP); x < camera::resolutionX / GRID_STEP + 1 - camera::viewportOffsetX / GRID_STEP; x++)
	{
		brushRect.setPosition(x * GRID_STEP, -camera::viewportOffsetY);
		winHandle.draw(brushRect, matrix);
	}
	brushRect.setSize(sf::Vector2f(camera::resolutionX, 1));
	for (int y = (-camera::viewportOffsetY / GRID_STEP); y < camera::resolutionY / GRID_STEP + 1 - camera::viewportOffsetY / GRID_STEP; y++)
	{
		brushRect.setPosition(-camera::viewportOffsetX, y * GRID_STEP);
		winHandle.draw(brushRect, matrix);
	}*/
}

// Paint menu buttons
void paint::p_menuButton(int id, sf::RenderWindow &winHandle)
{
	brushRect.setPosition(0, 0);
	brushRect.setOrigin(0, 0);
	//sf::Text brushText;
	//sf::RectangleShape brushRect;
	// Base rect
	brushRect.setPosition(UI::btn[id].posX, UI::btn[id].posY);
	brushRect.setFillColor(sf::Color(255, 255, 255));
	brushRect.setOutlineThickness(0.00f);
	brushRect.setSize(sf::Vector2f(UI::btn[id].sizeX, UI::btn[id].sizeY));
	brushRect.setTexture(NULL);
	if (!UI::btn[id].hovered) { brushRect.setFillColor(sf::Color(255, 255, 255, 0)); }
	else { brushRect.setFillColor(sf::Color(0, 0, 0, 100)); }
	winHandle.draw(brushRect);
	// Button text
	int charSize = 24;

	if (!UI::btn[id].textCenter) { brushText.setPosition(UI::btn[id].posX + 10, UI::btn[id].posY + 4); }
	else
	{
		brushText.setPosition(UI::btn[id].posX + (UI::btn[id].sizeX - getVisualOffsetX(UI::btn[id].text.length(), UI::btn[id].text, charSize)) / 2, UI::btn[id].posY + 4);
	}
	brushText.setColor(sf::Color(255, 255, 255));
	brushText.setString(UI::btn[id].text);
	brushText.setCharacterSize(charSize);
	brushText.setFont(gl_mainFont);
	winHandle.draw(brushText);
}

// Paint menu sliders
void paint::p_menuSlider(int id, sf::RenderWindow &winHandle)
{
	brushRect.setPosition(0, 0);
	brushRect.setOrigin(0, 0);
	// Base rect
	brushRect.setPosition(UI::sld[id].posX, UI::sld[id].posY);
	brushRect.setFillColor(sf::Color(255, 255, 255));
	brushRect.setOutlineThickness(0.00f);
	brushRect.setSize(sf::Vector2f(UI::sld[id].sizeX, UI::sld[id].sizeY));
	brushRect.setTexture(NULL);
	winHandle.draw(brushRect);
	// Slider
	brushRect.setPosition(UI::sld[id].posX + (UI::sld[id].sliderValue / UI::sld[id].sliderMaxValue) * UI::sld[id].sizeX, UI::sld[id].posY);
	brushRect.setFillColor(sf::Color(0, 0, 255));
	winHandle.draw(brushRect);
	//brushRect.
	// Button text
	/*int charSize = 24;

	brushText.setPosition(UI::btn[id].posX + 10, UI::btn[id].posY + 4);
	brushText.setColor(sf::Color(255, 255, 255));
	brushText.setString(UI::btn[id].text);
	brushText.setCharacterSize(charSize);
	brushText.setFont(gl_mainFont);
	winHandle.draw(brushText);*/
}

// Paint menu overlays
void paint::p_menuOverlay(sf::RenderWindow &winHandle)
{
	// Creating brushes
	//sf::Text brushText;
	//sf::RectangleShape brushRect;
	brushRect.setPosition(0, 0);
	brushRect.setOrigin(0, 0);
	// Main menu
	brushRect.setFillColor(sf::Color(0, 0, 0, 100));
	brushRect.setPosition(camera::resolutionX - 350, 0);
	brushRect.setSize(sf::Vector2f(300, camera::resolutionY));
	brushRect.setOutlineThickness(2.00f);
	brushRect.setOutlineColor(sf::Color(0, 0, 0));
	winHandle.draw(brushRect);

	// Create
	if (UI::menuLevel == MENU_CREATE)
	{
		brushRect.setFillColor(sf::Color(0, 0, 0, 100));
		brushRect.setPosition(camera::resolutionX - 552, 52);
		brushRect.setSize(sf::Vector2f(200, 150));
		brushRect.setOutlineThickness(2.00f);
		winHandle.draw(brushRect);
	}
	// Add object
	else if (UI::menuLevel == MENU_ADDOBJECT)
	{
		brushRect.setFillColor(sf::Color(0, 0, 0, 100));
		brushRect.setPosition(camera::resolutionX - 552, 102);
		brushRect.setSize(sf::Vector2f(200, 350));
		brushRect.setOutlineThickness(2.00f);
		winHandle.draw(brushRect);
	}
	// Tools
	else if (UI::menuLevel == MENU_TOOLS)
	{
		brushRect.setFillColor(sf::Color(0, 0, 0, 100));
		brushRect.setPosition(camera::resolutionX - 552, 152);
		brushRect.setSize(sf::Vector2f(200, 325));
		brushRect.setOutlineThickness(2.00f);
		winHandle.draw(brushRect);
	}
	// Other
	else if (UI::menuLevel == MENU_OTHER)
	{
		brushRect.setFillColor(sf::Color(0, 0, 0, 100));
		brushRect.setPosition(camera::resolutionX - 552, 202);
		brushRect.setSize(sf::Vector2f(200, 300));
		brushRect.setOutlineThickness(2.00f);
		winHandle.draw(brushRect);
	}
}