all: processor

flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

processor: Stack.o Proc.o Instructions.o
	g++ Stack.o Proc.o Instructions.o

Stack.o: ./src/Stack.cpp
	g++ -I ./include/ -c $(flags) ./src/Stack.cpp

Proc.o: ./src/Proc.cpp
	g++ -I ./include/ -c $(flags) ./src/Proc.cpp

Instructions.o: ./src/Instructions.cpp
	g++ -I ./include/ -c $(flags) ./src/Instructions.cpp

clean:
	rm -rf *.o *.exe
