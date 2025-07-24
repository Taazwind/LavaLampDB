CC = gcc
SRC_DIR = src
OBJ_DIR = obj
SRC = main.c $(SRC_DIR)/grille.c
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/grille.o
CFLAGS = -Wall -Wextra -Werror -Isrc
EXEC = prog


all: $(EXEC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all clean
