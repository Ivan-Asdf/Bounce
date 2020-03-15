
dep_win_folder = dep_win
build_filestruct_linux 	= mkdir -p build
build_filestruct_win 	= mkdir -p build && cp $(dep_win_folder)/bin/*.dll build 

source = $(wildcard *.cpp)
header = $(wildcard *.h)
#libs = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
libs = -lSDL2 -lSDL2_gfx

linux: $(source) $(header)
	gcc -g $(source) $(libs)

linux_release:
	$(build_filestruct_linux)
	gcc -O3 $(source) $(libs) -o build/bounce

# Run make(mingw64) in bash(git bash, cygwin..)
windows: $(source) $(header)
	$(build_filestruct_win)
	gcc -g $(source) -o build/tetris -I$(dep_win_folder)/include -L$(dep_win_folder)/lib -lmingw32 $(libs)
	
windows_release: $(source) $(header)
	$(build_filestruct_win)
	gcc -O3 -mwindows $(source) -o build/tetris -I$(dep_win_folder)/include -L$(dep_win_folder)/lib -lmingw32 $(libs)