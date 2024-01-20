.RECIPEPREFIX = >

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra #-Werror
LDLIBS = -lncurses `pkg-config --cflags --libs check` -lc

VIEWER_SRC_DIRS = .
VIEWER_SRC := $(foreach dir, $(VIEWER_SRC_DIRS), $(wildcard $(dir)/*.c))
VIEWER_OBJ := $(VIEWER_SRC:.c=.o)
VIEWER_TARGET = hexviewer

STRWRAP_SRC_DIRS = str_wrap
STRWRAP_SRC := $(foreach dir, $(STRWRAP_SRC_DIRS), $(wildcard $(dir)/*.c))
STRWRAP_OBJ := $(STRWRAP_SRC:.c=.o)
STRWRAP_TARGET = strwraplib.a

STRWRAP_TEST_SRC_DIRS = ./tests/string_tests
STRWRAP_TEST_SRC := $(foreach dir, $(STRWRAP_TEST_SRC_DIRS), $(wildcard $(dir)/*.c))
STRWRAP_TEST_OBJ := $(STRWRAP_TEST_SRC:.c=.o)
STRWRAP_TEST_NAME = ./tests/string_tests/string_tests


TARGETS = $(VIEWER_TARGET) $(STRWRAP_TARGET)

all: $(TARGETS)

$(VIEWER_TARGET): $(VIEWER_OBJ)

$(STRWRAP_TARGET): $(STRWRAP_OBJ)
> $(AR) rcs $@ $^


################ --- TESTS --- ####################
all_tests: $(STRWRAP_TEST_NAME)
> $(STRWRAP_TEST_NAME)

compile_all_tests: $(STRWRAP_TEST_NAME)

$(STRWRAP_TEST_NAME): $(STRWRAP_TEST_OBJ) $(STRWRAP_OBJ)


clean:
> rm -f $(VIEWER_OBJ)
> rm -f $(STRWRAP_OBJ)
> rm -f $(STRWRAP_TEST_OBJ)

clean_all: clean
> rm -f $(VIEWER_TARGET) 
> rm -f $(STRWRAP_TARGET) 
> rm -f $(STRWRAP_TEST_NAME) 
