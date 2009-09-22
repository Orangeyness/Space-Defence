#include <allegro.h>
#include <string>
#include "menuButton.h"
#include "inputExtension.h"

#define C_BLACK makecol(0, 0, 0)
#define C_GREEN makecol(0, 255, 0)

using namespace menu;
using namespace std;
using namespace inputExt;

Button::Button(int xx, int yy, int w, int h, string caption) {
	X = xx;
	Y = yy;
	Width = w;
	Height = h;
	Value = caption;

	Selected = false;
	Next = NULL;
	Prev = NULL;	
	}

Button::~Button() {	
	}

void Button::update() {
	if (Selected) {
		if ((keyboard::isKeyPressed(KEY_DOWN) || keyboard::isKeyPressed(KEY_S)) && Next != NULL) {
			Next->Selected = true;
			Selected = false;		
			keyboard::clearKey(KEY_DOWN);	
			keyboard::clearKey(KEY_S);
			}
		if ((keyboard::isKeyPressed(KEY_UP) || keyboard::isKeyPressed(KEY_W)) && Prev != NULL) {
			Prev->Selected = true;
			Selected = false;			
			keyboard::clearKey(KEY_UP);
			keyboard::clearKey(KEY_W);
			}
		}	
	}

void Button::draw(BITMAP *G) {
	int textColor = C_GREEN;
	int bgColor = C_BLACK;
	
	if (Selected) {
		textColor = C_BLACK;
		bgColor = C_GREEN;		
		}

	rectfill(G, X, Y, X + Width, Y + Height, bgColor);
	rect(G, X, Y, X + Width, Y + Height, C_GREEN);
	textout_centre_ex(G, font, Value.c_str(), X + Width/2, Y + Height/2, textColor, -1);	
	}
