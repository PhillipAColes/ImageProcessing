goal: image_processor.exe

GCC = g++
CCFLAGS = -std=c++14 -fbounds-check -Wall
OBJ = bmp.o input_parser.o

image_processor.exe: $(OBJ) main.o
	$(GCC) -o image_processor.exe $(OBJ) $(CCFLAGS) main.o

main.o: main.cpp
	$(GCC) -c main.cpp $(CCFLAGS)

bmp.o: bmp.cpp
	$(GCC) -c bmp.cpp $(CCFLAGS)

input_parser.o: input_parser.cpp
	$(GCC) -c input_parser.cpp $(CCFLAGS)

clean:
	rm main.o $(OBJ)

#OBJ = bruteforce.o utils.o

#exercise2.exe: $(OBJ) main.o
#	$(GCC) -o exercise2.exe $(OBJ) $(CCFLAGS) main.o

#main.o: main.cpp
#	$(GCC) -c main.cpp $(CCFLAGS)

#utils.o: utils.cpp
#	$(GCC) -c utils.cpp $(CCFLAGS)

#clean:
#	rm main.o $(OBJ)

