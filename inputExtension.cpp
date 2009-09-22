#include <allegro.h>
#include "inputExtension.h"

namespace inputExt {

	bool keyboard::keyPressed[KEY_COUNT] = { false };
	bool keyboard::keyDown[KEY_COUNT] = { false };
	bool keyboard::keyReleased[KEY_COUNT] = { false };

	bool keyboard::isKeyDown(int key) {
		return keyboard::keyDown[key];		
		}

	bool keyboard::isKeyPressed(int key){
		return keyboard::keyPressed[key];		
		}

	bool keyboard::isKeyReleased(int key) {
		return keyboard::keyReleased[key];		
		}

	void keyboard::clearKey(int key) {
		keyboard::keyPressed[key] = false;
		}

	void keyboard::update() {
		for(int i = 0; i < KEY_COUNT; i++) {
			if (keyboard::keyPressed[i] == true) keyboard::keyPressed[i] = false;
			if (keyboard::keyReleased[i] == true) keyboard::keyReleased[i] = false;
			if (key[i]) {
				if (!keyboard::keyDown[i]) {
					keyboard::keyPressed[i] = true;
					keyboard::keyDown[i] = true;						
					}
				}	
					else
				{
				if (keyboard::keyDown[i] == true) {
					keyboard::keyDown[i] = false;
					keyboard::keyReleased[i] = true;					
					}
				}			
			}
		}

	}

