#ifndef _INPUT_EXTENSION_
#define _INPUT_EXTENSION_


namespace inputExt {
	#define KEY_COUNT 128

	class keyboard {
		private:
			static bool keyPressed[KEY_COUNT];
			static bool keyDown[KEY_COUNT];

		public:
			static bool isKeyDown(int key);
			static bool isKeyPressed(int key);

			static void update();
		};
	}

#endif
