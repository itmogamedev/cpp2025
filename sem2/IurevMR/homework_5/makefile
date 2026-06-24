SRC = $(filter-out src/min_main.cpp,$(wildcard src/*.cpp))
OUT = out/main.exe

build:
	mkdir -p out
	clang++ -std=c++17 -Isrc -Iext/inc $(SRC) -o $(OUT) \
	-Lext/lib \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system
	cp ext/bin/*.dll out

run:
	cd out && ./main.exe