# This is a new Makefile for the working fault-tolerant-spm project

TARGET=testdriver

CPP = g++
CPPFLAGS = -std=c++11

SRCDIR = src
HDRDIR = include
OBJDIR = build
BINDIR = build

SOURCES  = $(wildcard $(SRCDIR)/*.cpp)
INCLUDES = $(wildcard $(HDRDIR)/*.hpp)
OBJECTS  = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	g++ -o $@ -I $(HDRDIR) $(OBJECTS)
	-@echo "Finished building."

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	g++ $(CPPFLAGS) -c -I $(HDRDIR) $< -o $@
	-@echo "Compiled "$<" to object file successfully."

.PHONY: clean

clean:
	@rm $(OBJECTS) 2>/dev/null || true
	@echo "Finished cleaning."

realclean: clean
	@rm $(BINDIR)/$(TARGET) 2>/dev/null || true
	@echo "Finished cleaning target."
