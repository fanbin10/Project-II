CPP = g++
CFLAGS = -Wall -g -c

all: shoot

shoot: main.o shoot.o 
	$(CPP)  main.o shoot.o  -o shoot

main.o: main.cpp
	$(CPP) $(CFLAGS) main.cpp -o main.o

shoot.o: shoot.cpp
	$(CPP) $(CFLAGS) shoot.cpp -o shoot.o

check-syntax:
	$(CPP) -o nul -S ${CHK_SOURCES}
run:
	./shoot 0.8

clean:

	rm -rf *.o *.txt shoot