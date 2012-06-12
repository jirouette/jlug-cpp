CXX=g++
CFLAGS=-W -Wall -Wextra -ansi -pedantic -s -O2 -DTIXML_USE_STL -DGL_GLEXT_PROTOTYPES $(INCLUDE)
INCLUDE=-Isrc/entities -Isrc/loadable -Isrc/models -Isrc/ -Isrc/utils -Isrc/geom -Ilib/ -Ilib/utils/ -Ilib/TmxParser/ -Ilib/TmxParser/base64/
LDFLAGS=-lsfml-system -lsfml-graphics -lsfml-window -ltinyxml -lGL -lglut -lGLU
EXEC=bin/jlug
SRC= $(wildcard src/geom/*.cpp) $(wildcard src/entities/*.cpp) $(wildcard src/loadable/*.cpp) $(wildcard src/models/*.cpp) $(wildcard src/utils/*.cpp) $(wildcard src/*.cpp) $(wildcard lib/*.cpp) $(wildcard lib/utils/*.cpp) $(wildcard lib/TmxParser/*.cpp) $(wildcard lib/TmxParser/base64/*.cpp)
OBJ= $(SRC:.cpp=.o)

build: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $(EXEC) $^ $(LDFLAGS)

main.o: *.hpp

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper: clean
	rm $(EXEC)

run:
	$(EXEC)

build-run: build run

