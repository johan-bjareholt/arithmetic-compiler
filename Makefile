CXX=g++
NAME=compiler
CPPFLAGS=-g --std=c++11
INCLUDES=-Isrc/ -Ibuild/
FLAGS=$(CPPFLAGS) $(INCLUDES)

MAINCPP=src/main.cpp
OBJ=build/nodes.o build/vartable.o build/classes.o build/func.o \
	build/grammar.tab.o \
	build/lex.yy.c

# Link & compile
.PHONY: $(NAME)
$(NAME): $(OBJ)
	$(CXX) $(FLAGS) -o $(NAME) $(MAINCPP) $(OBJ)

#	Compiles source files
build/%.o: src/%.cpp build/
	$(CXX) -c $(FLAGS) -o $@ $<

# Grammar
build/grammar.tab.o: build/grammar.tab.cc build/
	$(CXX) $(FLAGS) -o build/grammar.tab.o -c build/grammar.tab.cc
build/grammar.tab.cc: src/grammar.yy build/
	bison -o build/grammar.tab.cc src/grammar.yy


# Lexing
build/lex.yy.c: src/lex.ll build/grammar.tab.cc build/
	flex -o build/lex.yy.c -c src/lex.ll

# Create build folder
build/:
	mkdir -p build

# Clean
clean:
	rm -r build $(NAME)
