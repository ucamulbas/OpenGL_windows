CC= g++
FLAGS= -O3 -W -Wall -I..\..\Bibliotheque\include -L..\..\Bibliotheque\lib\x86 -lSDL2  -lglew32s -lopengl32 
DEFINE= -DSDL_MAIN_HANDLED -DGLEW_STATIC
SRC= $(wildcard source/*.cpp) 
OBJ= $(SRC:%.cpp=obj/%.o)

OpenGL:	$(OBJ) 
	$(CC) $^ -o $@ $(FLAGS) $(DEFINE)

obj/source/%.o:	source/%.cpp
	$(CC) -c -o $@ $^ $(FLAGS) $(DEFINE)

clean:	
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
	rm -f OpenGL
	rm -f OpenGL.exe