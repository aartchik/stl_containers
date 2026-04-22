CXX = g++
CXXFLAGS =  -Wall -Werror -std=c++14 -Iinclude


#CXXFLAGS = -fsanitize -Wall -Werror -std=c++14 -Iinclude
#LDFLAGS = -fsanitize=address

EXE = list
SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(OBJECTS)
#	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE)

.PHONY: clean all
