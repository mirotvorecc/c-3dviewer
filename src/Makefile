.PHONY: all, install, uninstall, clean, dvi, dist, tests, gcov_report
#        +      +         +         +                +         +

TARGET = my3dViewer
VERSION=v1.0
CC = gcc
CFLAGS = -Werror -Wextra -Wall 
C11 = -std=c11

COVERAGE_DIR = ./coverage/

PKG_CONFIG = $(shell which pkg-config)
PKG_CONFIG_FLAGS = --libs --cflags

CHECK_LINK = $(shell $(PKG_CONFIG) $(PKG_CONFIG_FLAGS) check)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

USER_NAME = $(shell whoami)
PWD = $(shell pwd)

RM = rm -rf
CLANG = clang-format -style=google

SRC_DIR = ./my3dViewer/
OBJ_DIR = ./objects/
BUILD_DIR = ./build/

INSTALL_DIR=./install/
DIST_DIR=./$(TARGET)_$(VERSION)/

SRC_C = $(wildcard $(SRC_DIR)*.c)
SRC_CPP = $(wildcard $(SRC_DIR)*.cpp)

PRINT = 
TEST_DIR =./tests/
TEST_SRC = $(wildcard $(TEST_DIR)*.c)

SRC_OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_C))  #  ./objects/main.o
TEST_OBJ = $(patsubst $(TEST_DIR)%.c, $(OBJ_DIR)%.o, $(TEST_SRC))  #  ./objects/main.o

ifdef GCOV_BUILD
	CFLAGS += $(GCOV_FLAGS)
	OBJ_DIR = $(COVERAGE_DIR)
endif

all: 
	@qmake6 CONFIG+=release -o $(BUILD_DIR)Makefile $(SRC_DIR)/$(TARGET).pro
	@cd $(BUILD_DIR) && make all && make clean

install : all
	@echo "Installing $(TARGET) in $(INSTALL_DIR)"
	@mkdir -p $(INSTALL_DIR)
	@cp -r $(BUILD_DIR) $(INSTALL_DIR)

uninstall: 
	$(RM)I $(INSTALL_DIR)

$(OBJ_DIR)%.o : $(TEST_SRC)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(C11) -I$(SRC_DIR) -c $< -o $@

stat_lib : $(TEST_OBJ)
	@ar rc $(OBJ_DIR)$(TARGET).a $(OBJ_DIR)*.o
	@ranlib $(OBJ_DIR)$(TARGET).a

test : clean_obj stat_lib
	@$(CC) $(CFLAGS) -I$(SRC_DIR) $(TEST_SRC) $(SRC_C) $(CHECK_LINK) $(OBJ_DIR)$(TARGET).a -o $(OBJ_DIR)$(TARGET)_test.o -lm
	$(OBJ_DIR)$(TARGET)_test.o

gcov_report : gcov_build grBuild grRun icov htmlGen open_gr

gcov_build : 
	@$(MAKE) stat_lib GCOV_BUILD+=1

grBuild :
	@$(CC) $(CFLAGS) -I$(SRC_DIR) $(GCOV_FLAGS) $(TEST_SRC) $(SRC_C) $(CHECK_LINK) $(COVERAGE_DIR)$(TARGET).a -o icovOutput

grRun :
	@./icovOutput

icov :
	@lcov -t "test" -o icovOutput.info -c -d ./

htmlGen :
	@genhtml -o $(COVERAGE_DIR) icovOutput.info

open_gr :
	@open $(COVERAGE_DIR)index.html
	@mv *.gcda *.o *.a *.gcba *.info *.gcno icovOutput $(COVERAGE_DIR)

dist:
	@echo "Creating distribution archive..."
	@rm -rf $(DIST_DIR)
	@mkdir -p $(DIST_DIR)/tests
	@cp -r $(TARGET) Makefile $(DIST_DIR)
	@cp -r $(TEST_DIR) $(DIST_DIR)tests
	@tar cvzf $(TARGET)_$(VERSION).tar.gz $(DIST_DIR)
	@rm -rf $(DIST_DIR)
	@echo "Distribution archive created: $(TARGET)_$(VERSION).tar.gz"

pdf	: dvi
	@echo "Creating PDF file"
	@dvipdf $(TARGET).dvi
	@$(RM) *.aux *.log

dvi	: $(TARGET).tex
	@echo "Creating DVI file"
	@latex $(TARGET).tex
	@$(RM) *.aux *.log

rebuild: clean all

clean : clean_build clean_obj clean_gr clean_dvi

clean_build :
	$(RM) $(BUILD_DIR)

clean_obj :
	$(RM) $(OBJ_DIR)

clean_gr :
	$(RM) $(COVERAGE_DIR)

clean_dvi:
	$(RM) $(TARGET).dvi $(TARGET).pdf

format:
	$(CLANG) -i $(SRC_C) $(SRC_CPP) $(TEST_SRC)