//REUBEN BELL
//12:47 AM 20/11/2009
//The entry point for the game, space defence.
//Just messing with shit at the moment.

#include <allegro.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	if (allegro_init() != 0) return EXIT_FAILURE;
	
	install_timer();
	install_keyboard();
	
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	clear_to_color(screen, makecol(255, 255, 255));	
	triangle(screen, 20, 20, 50, 50, 50, 100, makecol(50, 50, 50));
	
	while(!keypressed());

	return EXIT_SUCCESS;
	}
