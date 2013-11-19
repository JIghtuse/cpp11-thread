MKDIR := mkdir -p
CFLAGS := -Wall -Werror -Wextra -pedantic -std=c++11
LDFLAGS := -pthread
PROG := bin/accum
OBJS := $(patsubst src/%.cpp,obj/%.o, $(wildcard src/*.cpp))

.PHONY: all clean

all: build

build: $(PROG)

clean:
	rm -rf $(PROG) $(OBJS)

bin/accum: obj/accum.o

$(PROG):
	@$(MKDIR) $(dir $@)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $^

obj/%.o : src/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CFLAGS) -c -MD -o $@ $<
