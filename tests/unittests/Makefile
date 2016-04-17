
CXX=g++
CPPFLAGS=-g --std=c++11
INCLUDES=-I../../src/ -Isrc/
FLAGS=$(CPPFLAGS) $(INCLUDES)

VARTABLESRC=../../src/vartable.cpp ../../src/nodes.cpp ../../src/classes.cpp ../../src/func.cpp
.PHONY: vartabletest
vartabletest:
	$(CXX) $(FLAGS) $(VARTABLESRC) src/vartabletest.cpp -o vartabletest

clean:
	rm vartabletest
