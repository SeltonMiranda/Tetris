INCLUDES_DIR = includes
SRC_DIR = src
BUILD_DIR = build

CFLAGS = -Wall -Wextra -I$(INCLUDES_DIR)
LIBS = $(BUILD_DIR)/Piece.o $(BUILD_DIR)/Game.o $(BUILD_DIR)/Constants.o
MAIN = Tetris

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

$(MAIN): $(BUILD_DIR)/main.o $(LIBS)
	@mkdir -p $(dir $@)
	g++ -o $(MAIN) $(BUILD_DIR)/main.o $(LIBS) $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDES_DIR)/%.hpp
	@mkdir -p $(dir $@)
	g++ -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(dir $@)
	g++ -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR)

purge:
	rm -rf $(MAIN) $(BUILD_DIR)

.phony: clean purge all
