CXX = g++
RM = rm -f
CCPFLAGS = -o -Wall -Iinclude 
LDFLAGS = $(shell allegro-config --cflags)
LDLIBS = $(shell allegro-config --libs)
SRCS = global.cpp objectBullet.cpp stageInGame.cpp inputExtension.cpp objectParticle.cpp stageInGameMenu.cpp main.cpp stageAboutGame.cpp stageOpeningMenu.cpp menuButton.cpp stageGameOver.cpp stageOptionsMenu.cpp objectAsteroid.cpp stageHighScores.cpp stagePauseMenu.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

SpaceDefence : $(OBJS)
	$(CXX) $(LDFLAGS) -o SpaceDefence $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

clean:
	$(RM) $(OBJS)
