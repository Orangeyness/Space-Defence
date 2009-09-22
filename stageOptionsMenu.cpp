#include <allegro.h>
#include <string>
#include <sstream>

#include "stageOptionsMenu.h"
#include "stageInterface.h"
#include "inputExtension.h"
#include "global.h"
#include "menuButton.h"

#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)
#define C_GRAY makecol(40, 40, 40)

using namespace stages;
using namespace inputExt;
using namespace global;
using namespace menu;

stageOptionsMenu::stageOptionsMenu(StageInterface* parent, BITMAP* preview) {
	rtnStage = parent;
	rtnPreview = preview;

	for (int x = 1; x < preview->w +2; x+= 2) {
		for (int y = x%2; y < preview->w +2; y+= 2) {
			putpixel(rtnPreview, x, y, C_GRAY);
			}		
		}

	resolutions[0][0] = 640;
	resolutions[0][1] = 480;
	resolutions[1][0] = 800;
	resolutions[1][1] = 600;
	resolutions[2][0] = 1024;
	resolutions[2][1] = 768;
	resolutions[3][0] = 1280;
	resolutions[3][1] = 1024;

	resolution = 0;
	for (int i = 0; i < RESOLUTION_COUNT; i++) {
		if (	resolutions[i][0] == globalData::gameResolutionX &&
				resolutions[i][1] == globalData::gameResolutionY) {
			resolution = i;
			break;			
			}
		}

	fullScreen = globalData::gameFullScreen;

	int Width = 300;
	int Height = 400;
	int X = SCREEN_W/2 - Width/2;
	int Y = SCREEN_H/2 - Height/2;

	ostringstream strBuilder;
	strBuilder << resolutions[resolution][0] << "x" << resolutions[resolution][1];

	bntApply = new Button(X + 10, Y + Height - 50, 80, 40, "Apply");
	bntCancel = new Button(X + 210, Y + Height - 50, 80, 40, "Cancel");
	bntReset = new Button(X + 110, Y + Height - 50, 80, 40, "Reset");
	bntResolution = new Button(X + 170, Y + 55, 100, 30,  strBuilder.str());
	bntFullScreen = new Button(X + 170, Y + 95, 100, 30, "On");

	bntResolution->Selected = true;
	bntResolution->Next = bntFullScreen;
	bntResolution->Prev = bntCancel;
	
	bntFullScreen->Next = bntApply;
	bntFullScreen->Prev = bntResolution;

	bntApply->Next = bntReset;
	bntApply->Prev = bntFullScreen;
	
	bntReset->Next = bntCancel;
	bntReset->Prev = bntApply;

	bntCancel->Next = bntResolution;
	bntCancel->Prev = bntReset;

	if (fullScreen == true) bntFullScreen->Value = "On";
	if (fullScreen == false) bntFullScreen->Value = "Off";
	}

stageOptionsMenu::~stageOptionsMenu() {
	delete rtnPreview;

	delete bntApply;
	delete bntCancel;
	delete bntReset;
	delete bntResolution;
	delete bntFullScreen;
	}

void stageOptionsMenu::draw(BITMAP *graphicsBuffer) {
	blit(rtnPreview, graphicsBuffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	

	int Width = 300;
	int Height = 400;
	int X = SCREEN_W/2 - Width/2;
	int Y = SCREEN_H/2 - Height/2;

	rectfill(graphicsBuffer, X, Y, X + Width, Y + Height, C_BLACK);
	rect(graphicsBuffer, X, Y, X + Width, Y + Height, C_GREEN);
	
	textout_ex(graphicsBuffer, font, "Options.", X + 10, Y + 10, C_GREEN, -1);
	line(graphicsBuffer, X + 10, Y + 30, X + Width - 10, Y + 30, C_GREEN);
	
	textout_ex(graphicsBuffer, font, "Resolution: ", X + 30, Y + 65, C_GREEN, -1);
	textout_ex(graphicsBuffer, font, "Fullscreen: ", X + 30, Y + 105, C_GREEN, -1);

	line(graphicsBuffer, X + 10, Y + Height -60, X + Width - 10, Y + Height - 60, C_GREEN);
	

	bntApply->draw(graphicsBuffer);
	bntCancel->draw(graphicsBuffer);
	bntReset->draw(graphicsBuffer);
	bntResolution->draw(graphicsBuffer);
	bntFullScreen->draw(graphicsBuffer);
	}

bool stageOptionsMenu::update() {
	bntApply->update();
	bntCancel->update();
	bntReset->update();
	bntResolution->update();
	bntFullScreen->update();
	
	if (((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntCancel->Selected) || keyboard::isKeyPressed(KEY_ESC)) {
		rtnStage->resume();
				
		globalData::gameCurrentStage = rtnStage;
		return STAGE_OVER;		
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntResolution->Selected) {
		resolution ++;
		if (resolution >= RESOLUTION_COUNT) resolution = 0;
		ostringstream strBuilder;
		strBuilder << resolutions[resolution][0] << "x" << resolutions[resolution][1];
		bntResolution->Value = strBuilder.str();
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntFullScreen->Selected) {
		fullScreen =! fullScreen;
		if (fullScreen == true) bntFullScreen->Value = "On";
		if (fullScreen == false) bntFullScreen->Value = "Off";
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntReset->Selected) {
		for (int i = 0; i < RESOLUTION_COUNT; i++) {
			if (	resolutions[i][0] == globalData::gameResolutionX &&
					resolutions[i][1] == globalData::gameResolutionY) {
				resolution = i;
				break;			
				}
			}

		fullScreen = globalData::gameFullScreen;
		if (fullScreen == true) bntFullScreen->Value = "On";
		if (fullScreen == false) bntFullScreen->Value = "Off";
		ostringstream strBuilder;
		strBuilder << resolutions[resolution][0] << "x" << resolutions[resolution][1];
		bntResolution->Value = strBuilder.str();
		}

	if ((keyboard::isKeyPressed(KEY_ENTER) || keyboard::isKeyPressed(KEY_ENTER_PAD)) && bntApply->Selected) {

		globalData::gameFullScreen = fullScreen;
		globalData::gameResolutionX = resolutions[resolution][0];
		globalData::gameResolutionY = resolutions[resolution][1];

		if (globalData::gameFullScreen) 
			set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, globalData::gameResolutionX, globalData::gameResolutionY, 0, 0);
		else
			set_gfx_mode(GFX_AUTODETECT_WINDOWED, globalData::gameResolutionX, globalData::gameResolutionY, 0, 0);
	
		destroy_bitmap(globalData::gameGraphicsBuffer);
		globalData::gameGraphicsBuffer = create_bitmap(SCREEN_W, SCREEN_H);

		rtnStage->resume();
				
		globalData::gameCurrentStage = rtnStage;
		return STAGE_OVER;		
		}
	
	return STAGE_RUNNING;	
	}

void stageOptionsMenu::pause() { }
void stageOptionsMenu::resume() { }
