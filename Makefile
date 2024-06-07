BIN= neuraltest
CXX= g++

SRCDIR= src
OBJDIR= obj
INCLUDE= -I ./include

SRC_MODULES= $(wildcard $(SRCDIR)/*.cpp)

CXXFLAGS= $(INCLUDE) -std=c++20 -DPLATFORM_DESKTOP -g

OBJ = $(SRC_MODULES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

PHONY: build run

run: $(BIN)
	./$(BIN) 0.25 1000 5 -1 1 50 exponential 3 1 4 1

build: $(OBJ) $(OBJDIR)
	$(CXX) -o $(BIN) $(OBJDIR)/*.o 

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@