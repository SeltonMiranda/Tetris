# Simple Tetris game for terminal

Only works in linux systems, require g++ compiler

# TODO List
- [ ] Rotate around the piece center
- [x] Include ncurses library to get buffer input instantly - Made I guess? It'll work for now
- [x] Clear completed rows
- [ ] Differentiate each piece by a color 
- [x] Make it runs slightly faster
- [ ] Encapsulate members from class 
- [ ] Create a queue of next pieces
- [ ] Make a scoreboard

## AFTER ALL IT IS DONE ABOVE
- [ ] Change piece class by an abstract block class
- [ ] Refactor to use an 1-dim array than 2-dim array for pieces and board

# To Run the game
```bash
$ git clone https://github.com/SeltonMiranda/Tetris && cd Tetris/
$ make
$ ./Game
```
