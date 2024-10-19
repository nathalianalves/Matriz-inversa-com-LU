compilationParameters = -Wall -lm -O0
programName = inversaAux

all: $(programName)

$(programName): inversa.c LU.c estruturas.c timeStamp.c
	gcc inversa.c LU.c estruturas.c timeStamp.c -o $(programName) $(compilationParameters)

clean:
	rm -f *.o *.gch

purge:
	make clean
	rm -f $(programName)
