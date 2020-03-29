
dep_win_folder = dep_win
build_filestruct_linux 	= mkdir -p build
build_filestruct_win 	= mkdir -p build && cp $(dep_win_folder)/bin/*.dll build 

source = $(wildcard *.cpp)
header = $(wildcard *.h)
#libs = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
libs = -lSDL2 -lSDL2_image -lSDL2_ttf -lyaml-cpp

linux: $(source) $(header)
	g++ -g $(source) $(libs)

linux_release:
	$(build_filestruct_linux)
	g++ -O3 $(source) $(libs) -o build/bounce