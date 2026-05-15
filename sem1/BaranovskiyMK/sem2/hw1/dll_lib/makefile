build:
	g++ -c dll_lib.cpp -o dll_lib.o
	g++ -fpic -shared dll_lib.o -o dll_lib.so
	cp dll_lib.so ../main/libdll_lib.so	