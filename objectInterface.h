//REUBEN BELL
//objectInterface.h
//20/11/09
/*
	Interface for object class.
	--	objects represent somthing on the screen,
		e.g. an asteroid.
	
		I do realise object is probably a crap name
		seeing as most things are objects.... still.
		And yeah they are much different to stages 
		at the moment.
*/

#include <allegro.h>

#ifndef _OBJECT_INTERFACE_
#define _OBJECT_INTERFACE_

namespace objects {

	class ObjectInterface {
		public:
			virtual bool update() = 0; //updates the object. false = delete object, true = keep object
			virtual void draw(BITMAP *graphicsBuffer) = 0; //draws the object onto the given bitmap.
		};
	
	}

#endif
