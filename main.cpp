//REUBEN BELL
//12:47 AM 20/11/2009
//The entry point for the game, space defence.
//Just messing with shit at the moment.

#include <allegro.h>
#include <stdlib.h>

#define GFX_TYPE GFX_AUTODETECT_WINDOWED
#define GFX_WIDTH 640
#define GFX_HEIGHT 480

#define FPS_TARGET 30

volatile int updateCount;

void timerUpdater() { updateCount++; }
END_OF_FUNCTION(timerUpdater);

int main(int argc, char * argv[]) {
	if (allegro_init() != 0) return EXIT_FAILURE;
	LOCK_VARIABLE(updateCount);
	LOCK_FUNCTION(timerUpdater);
	
	install_timer();
	install_keyboard();
	
	set_gfx_mode(GFX_TYPE, GFX_WIDTH, GFX_HEIGHT, 0, 0);

	install_int(timerUpdater, 1000 / FPS_TARGET);

	while(!keypressed()) {
		clear_to_color(screen, makecol(255, 255, 255));	
		textprintf_ex(screen, font, 20, 20, makecol(10, 10, 10), -1, "Counter: %d", updateCount);
		
		rest(10);
		}

	return EXIT_SUCCESS;
	}
END_OF_MAIN();
