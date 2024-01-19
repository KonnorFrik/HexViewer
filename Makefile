.RECIPEPREFIX = >

cmp = gcc
cflags = -Wall -Werror -Wextra -std=c11
LIBS = -lncurses

SRC_DIRS = .
SRC = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c)) 
OBJ = $(SRC:.c=.o)


main: $(OBJ)
> $(cmp) $(OBJ) $(LIBS) -o $@

%.o: %.c
> $(cmp) $(cflags) -c $? -o $@


clean:
> rm -f $(OBJ)

show:
> @echo $(SRC)
> @echo $(OBJ)

