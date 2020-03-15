
source = $(wildcard *.cpp)
header = $(wildcard *.h)
#libs = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
libs = -lSDL2 -lSDL2_gfx

target: $(source) $(header)
	g++ -g $(source) $(libs)
