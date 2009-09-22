#ifndef _MENU_BUTTON_
#define _MENU_BUTTON_

#include <allegro.h>
#include <string>

using namespace std;

namespace menu {
	class Button {
		private:		
			int X;
			int Y;
			int Width;
			int Height;
			

	
		public:
			Button(int xx, int yy, int w, int h, string caption);
			~Button();

			string Value;
			bool Selected;			
			Button* Next;
			Button* Prev;	

			void update();			
			void draw(BITMAP *G);
		};	
	}

#endif
