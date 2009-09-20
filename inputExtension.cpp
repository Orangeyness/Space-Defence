#include <allegro.h>
#include "inputExtension.h"

namespace inputExt {

	bool keyboard::keyPressed[KEY_COUNT] = { false };
	bool keyboard::keyDown[KEY_COUNT] = { false };

	bool keyboard::isKeyDown(int key) {
		return keyboard::keyDown[key];		
		}

	bool keyboard::isKeyPressed(int key){
		return keyboard::keyPressed[key];		
		}

	void keyboard::update() {
		for(int i = 0; i < KEY_COUNT; i++) {
			if (keyboard::keyPressed[i] == true) keyboard::keyPressed[i] = false;
			if (key[i]) {
				if (!keyboard::keyDown[i]) {
					keyboard::keyPressed[i] = true;
					keyboard::keyDown[i] = true;						
					}
				}	
					else
				{
				keyboard::keyDown[i] = false;
				}			
			}
		}

	}

