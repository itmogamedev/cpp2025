build:
	g++ -O2 -Iext/inc src/main.cpp -o out/main.exe -Lext/lib \
	-std=c++17                                               \
	-l:libsfml-graphics.a                                    \
    -l:libsfml-window.a                                      \
    -l:libsfml-system.a                                      \
    -lopengl32                                               \
    -lwinmm                                                  \
    -lgdi32											
	cp ext/dll/sfml-graphics-3.dll out
	cp ext/dll/sfml-system-3.dll   out
	cp ext/dll/sfml-window-3.dll   out

run:
	./out/main.exe
