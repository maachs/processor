all: processor clean

# TODO .PHONY

flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

HEADERS = Stack.h StackFunc.h Processor.h ProcessorFunc.h ErrorCode.h
# TODO sources = onegin.cpp
# objects = onegin.o (or better convert .cpp to .o)
# executable = onegin.exe

# TODO think about multiple files

# TODO compile into a build folder
Processor: a.exe
	a.exe

a.exe: main.o Stack.o
	g++ main.o Stack.o

main.o: main.cpp $(HEADERS)
	g++ -c $(flags) main.cpp

Stack.o: Stack.cpp $(HEADERS)
	g++ -c $(flags) Stack.cpp

clean:
	rm -rf *.o *.exe
