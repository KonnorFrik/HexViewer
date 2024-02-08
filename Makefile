.RECIPEPREFIX = >

CC = gcc
LOCAL_GCOVR = gcovr

CFLAGS = -std=c11 -Wall -Wextra #-Werror
LDLIBS = -lncurses `pkg-config --cflags --libs check` -lc
TEST_FLAGS = `pkg-config --cflags --libs check` -O0 -lc -lm -lgcov --coverage

COMMON_TEST_SRC_DIR = ./tests

VIEWER_SRC_DIRS = . formater views data str_wrap err_handle
VIEWER_SRC := $(foreach dir, $(VIEWER_SRC_DIRS), $(wildcard $(dir)/*.c))
VIEWER_OBJ := $(VIEWER_SRC:.c=.o)
VIEWER_TARGET = hexviewer

ERR_HANDLER_SRC_DIRS = err_handle 
ERR_HANDLER_SRC := $(foreach dir, $(ERR_HANDLER_SRC_DIRS), $(wildcard $(dir)/*.c))
ERR_HANDLER_OBJ := $(ERR_HANDLER_SRC:.c=.o)

STRWRAP_SRC_DIRS = str_wrap err_handle
STRWRAP_SRC := $(foreach dir, $(STRWRAP_SRC_DIRS), $(wildcard $(dir)/*.c))
STRWRAP_OBJ := $(STRWRAP_SRC:.c=.o)
STRWRAP_TARGET = strwraplib.a

STRWRAP_TEST_SRC_DIRS = ./tests/string_tests $(COMMON_TEST_SRC_DIR)
STRWRAP_TEST_SRC := $(foreach dir, $(STRWRAP_TEST_SRC_DIRS), $(wildcard $(dir)/*.c))
STRWRAP_TEST_OBJ := $(STRWRAP_TEST_SRC:.c=.o)
STRWRAP_TEST_NAME = ./tests/string_tests/string_tests

FORMATER_SRC_DIRS = formater
FORMATER_SRC = $(foreach dir, $(FORMATER_SRC_DIRS), $(wildcard $(dir)/*.c))
#FORMATER_OBJ = $(FORMATER_SRC:.c=.o)

FORMATER_TEST_SRC_DIRS = ./tests/formater_test $(COMMON_TEST_SRC_DIR)
FORMATER_TEST_SRC = $(foreach dir, $(FORMATER_TEST_SRC_DIRS), $(wildcard $(dir)/*.c))
FORMATER_TEST_NAME = ./tests/formater_test/format_tests

REPORT = REPORT.html

TARGETS = $(VIEWER_TARGET) #$(STRWRAP_TARGET)


all: $(TARGETS) clean

rebuild: clean_all all

$(VIEWER_TARGET): $(VIEWER_OBJ) #$(STRWRAP_TARGET)
#> $(CC) $(CFLAGS) $(VIEWER_OBJ) --static $(STRWRAP_TARGET) -o $@
> $(CC) $(CFLAGS) $(VIEWER_OBJ) -o $@

$(STRWRAP_TARGET): $(STRWRAP_OBJ) #$(ERR_HANDLER_OBJ)
> $(AR) rcs $@ $(STRWRAP_OBJ)

gcov_report: test
> $(LOCAL_GCOVR) -f err_.*\.c -f str_.*\.c -f hex_.*\.c --html --html-details -o $(REPORT) 
> @printf "\n\tREPORT FILE FOR OPEN: '\033[38;5;46m$(REPORT)\033[0m'\n"

################ --- TESTS --- ####################
test: compile_all_tests
> @$(STRWRAP_TEST_NAME)
> @$(FORMATER_TEST_NAME)

compile_all_tests: $(STRWRAP_TEST_NAME) $(FORMATER_TEST_NAME)

$(STRWRAP_TEST_NAME): $(STRWRAP_TEST_SRC) $(STRWRAP_SRC) $(ERR_HANDLER_SRC)
> $(CC) $(STRWRAP_TEST_SRC) $(STRWRAP_SRC) $(ERR_HANDLER_SRC) $(TEST_FLAGS) -o $@

$(FORMATER_TEST_NAME): $(FORMATER_SRC) $(FORMATER_TEST_SRC) $(STRWRAP_SRC) $(ERR_HANDLER_SRC)
> $(CC) $(FORMATER_SRC) $(FORMATER_TEST_SRC) $(STRWRAP_SRC) $(ERR_HANDLER_SRC) $(TEST_FLAGS) -o $@

clean:
> rm -f $(VIEWER_OBJ)
> rm -f $(STRWRAP_OBJ)
> rm -f $(STRWRAP_TEST_OBJ)
> rm -f $(ERR_HANDLER_OBJ)
#> rm -f $(FORMATER_OBJ)
> rm -f $(foreach dir, $(VIEWER_SRC_DIRS)\
 					   $(FORMATER_TEST_SRC_DIRS)\
 					   $(FORMATER_SRC_DIRS)\
	                   $(STRWRAP_SRC_DIRS)\
					   $(STRWRAP_TEST_SRC_DIRS),\
					   $(wildcard $(dir)/*.gcda))

> rm -f $(foreach dir, $(VIEWER_SRC_DIRS)\
 					   $(FORMATER_TEST_SRC_DIRS)\
 					   $(FORMATER_SRC_DIRS)\
           	           $(STRWRAP_SRC_DIRS)\
	                   $(STRWRAP_TEST_SRC_DIRS),\
					   $(wildcard $(dir)/*.gcno))

clean_all: clean
> rm -f $(VIEWER_TARGET) 
> rm -f $(STRWRAP_TARGET) 
> rm -f $(STRWRAP_TEST_NAME) 
> rm -f $(FORMATER_TEST_NAME) 
> rm -f $(wildcard ./*.html)
> rm -f $(wildcard ./*.css)
