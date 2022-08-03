goal: image_processor.exe

GCC = g++
CCFLAGS = -std=c++14 -fbounds-check -Wall
OBJ = bmp.o cmd_input.o

image_processor.exe: $(OBJ) main.o
	$(GCC) -o image_processor.exe $(OBJ) $(CCFLAGS) main.o

main.o: main.cpp
	$(GCC) -c main.cpp $(CCFLAGS)

bmp.o: bmp.cpp
	$(GCC) -c bmp.cpp $(CCFLAGS)

cmd_input.o: cmd_input.cpp
	$(GCC) -c cmd_input.cpp $(CCFLAGS)

clean:
	rm main.o $(OBJ)