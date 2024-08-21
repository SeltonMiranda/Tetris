CFLAGS = -Wall -Wextra -Wshadow
LIBS = Piece.o Tetris.o
MAIN = Game

$(MAIN) : main.o $(LIBS)
	g++ -o $(MAIN) main.o $(LIBS)

%.o : %.cpp %.hpp
	g++ -c $< $(CFLAGS)

clean: 
	rm -f *.o *.gch
purge:
	rm -f *.o *.gch $(MAIN)
