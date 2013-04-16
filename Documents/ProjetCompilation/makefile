################################
# Definition des variables
################################

# Compilation
CC = g++
LEX = flex
BISON = bison
DEBUG = -ggdb
CFLAGS = -W $(DEBUG) -Wall -ansi -pedantic -I inc/
LFLAGS = -lfl

# Dossier
SRCD = src/
SRCC = res/
INCD = inc/
OBJD = temp/

# Nom parser & lexer
LEXER = lexer
PARSER = parser

# Liste des fichiers
LSRCS=$(SRCC)$(LEXER).l
YSRCS=$(SRCC)$(PARSER).y
SRCS=$(wildcard $(SRCD)*.cpp) $(YSRCS:$(SRCC)%.y=$(SRCD)%.cpp) $(LSRCS:$(SRCC)%.l=$(SRCD)%.cpp)

OBJS = $(SRCS:$(SRCD)%.cpp=$(OBJD)%.o)
DEPS = $(SRCS:$(SRCD)%.cpp=$(OBJD)%.d)

BIN = compilateur

# Regles de production

default:
	@clear
	@make -s c
	@clear
	@make -s all
	@echo

all: $(BIN)

test :
	@echo $(SRCS)
	@echo $(DEPS)
	@echo $(OBJS)

# Executable
$(BIN): $(OBJS)
	@echo
	@echo "\033[44m\033[30m=== $@ ===\033[m\033[m"
	$(CC) -o $@ $^ $(LFAGS) $(CFLAGS)
	@echo "\033[44m\033[30m-> ok\033[m\033[m"
	@echo

# Objets
$(OBJD)%.o: $(SRCD)%.cpp
	@echo "\033[42m\033[30m-> $@\033[m\033[m"
	$(CC) -o $@ -c $< $(CFLAGS)

# Dependances
$(OBJD)%.d: $(SRCD)%.cpp
	$(CC) $(CFLAGS) -MM -MD -o $@ $<

# Bison
$(SRCD)%.cpp: $(SRCC)%.y
	$(BISON) -do $@ $<
	mv $(SRCD)$(PARSER).hpp $(INCD)

# Flex
$(SRCD)%.cpp: $(SRCC)%.l $(INCD)$(PARSER).hpp
	$(LEX) -o $@ $<

-include $(DEPS)

clean:
	rm -rf $(OBJS)
	rm -rf $(DEPS)
	rm -rf $(SRCD)parser.cpp $(SRCD)lexer.cpp $(INCD)parser.hpp
	rm -f */*~
	rm -f *~

c: clean
	rm -rf $(BIN)

.PHONY: clean c
