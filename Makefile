BIN= neuraltest
CXX= g++

SRCDIR= src
OBJDIR= obj
INCLUDE= -I ./include

SRC_MODULES= $(wildcard $(SRCDIR)/*.cpp)

CXXFLAGS= $(INCLUDE) -std=c++20 -DPLATFORM_DESKTOP

OBJ = $(SRC_MODULES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

PHONY: build run

run: $(BIN)
	./$(BIN)

build: $(OBJ) $(OBJDIR)
	$(CXX) -o $(BIN) $(OBJDIR)/*.o

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@