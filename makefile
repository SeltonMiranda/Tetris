CFLAGS = -Wall -Wextra
LIBS = Piece.o Game.o Constants.o
MAIN = Tetris

$(MAIN) : main.o $(LIBS)
	g++ -o $(MAIN) main.o $(LIBS)

%.o : %.cpp %.hpp
	g++ -c $< $(CFLAGS)

clean: 
	rm -f *.o *.gch
purge:
	rm -f *.o *.gch $(MAIN)
