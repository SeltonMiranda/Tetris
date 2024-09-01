CFLAGS = -Wall -Wextra
LIBS = Piece.o Game.o Constants.o
MAIN = Tetris

$(MAIN) : main.o $(LIBS)
	g++ -o $(MAIN) main.o $(LIBS) $(CFLAGS)

Piece.o: Piece.cpp Piece.hpp TetrisTypes.hpp
	g++ -c $< $(CFLAGS)

Game.o: Game.cpp Game.hpp TetrisTypes.hpp
	g++ -c $< $(CFLAGS)

%.o : %.cpp %.hpp
	g++ -c $< $(CFLAGS)

clean: 
	rm -f *.o *.gch
purge:
	rm -f *.o *.gch $(MAIN)
