CXX=g++
CFLAGS=-W -Wall -Wextra -ansi -pedantic -s -O2 -Werror -DTIXML_USE_STL $(INCLUDE)
INCLUDE=-Iheaders/ -Isrc/ -Ilib/ -Ilib/utils/ -Ilib/TmxParser/ -Ilib/TmxParser/base64/
LDFLAGS=-lsfml-system -lsfml-graphics -lsfml-window -ltinyxml
EXEC=bin/jlug
SRC= $(wildcard src/*.cpp) $(wildcard lib/*.cpp) $(wildcard lib/utils/*.cpp) $(wildcard lib/TmxParser/*.cpp) $(wildcard lib/TmxParser/base64/*.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

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
