# makefile customisé pour le tp3

# 1. nom du programme
EXE=perlinGeneration

# 2. flags de compilation allegro
FLAGS=`allegro-config --libs` -Wall -Winit-self -O3

# 3. liste des fichiers à compiler
SHARED=$(wildcard src/misc/*.cpp)
MODEL=$(wildcard src/model/environnement/*.cpp) $(wildcard src/model/joueur/*.cpp)
VIEW=$(wildcard src/vue/*.cpp)
CONTROLLER=$(wildcard src/controlleur/*.cpp)
ROOT=$(wildcard src/*.cpp)
SRC=$(SHARED) $(MODEL) $(VIEW) $(CONTROLLER) $(ROOT)

# 4. liste des fichiers objets à linker
OBJ=$(SRC:.cpp=.o)

###################################################

all: $(EXE) clean_obj

Debug: $(EXE) clean_obj
	mkdir bin || true
	mkdir bin/Debug || true
	cp $(EXE) bin/Debug
	cp -R res bin/Debug

Release: $(EXE) clean_obj
	mkdir bin || true
	mkdir bin/Release || true
	cp $(EXE) bin/Release
	cp -R res bin/Release

$(EXE): $(OBJ)
	@echo "\n=== linking des objets ===\n"
	g++ -o $@ $^ $(FLAGS)
	@echo "done.\n"

%.o: %.cpp %.h
	@echo "\n > compilation de $<"
	g++ -o $@ -c $< $(FLAGS)

cleanDebug: clean

cleanRelease: clean

clean: clean_obj
	rm -f $(EXE)
	rm -f $(EXE).layout
	rm -f $(EXE).depend
	rm -Rf bin
	
clean_obj:
	@echo "\n=== Clean up du projet ===\n"
	rm -f $(OBJ)
	@echo "done.\n"
