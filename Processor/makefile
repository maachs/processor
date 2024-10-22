all: processor

# TODO .PHONY

flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

# TODO sources = onegin.cpp
# objects = onegin.o (or better convert .cpp to .o)
# executable = onegin.exe

# TODO think about multiple files

# TODO compile into a build folder

Processor: processor.exe
	processor.exe

processor.exe: Stack.o Proc.o
	g++ Stack.o Proc.o

Stack.o: Stack.cpp
	g++ -c $(flags) Stack.cpp

Proc.o: Proc.cpp
	g++ -c $(flags) Proc.cpp

clean:
	rm -rf *.o *.exe
