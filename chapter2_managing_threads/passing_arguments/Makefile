MKDIR := mkdir -p
CFLAGS := -Wall -Werror -Wextra -pedantic -std=c++11
LDFLAGS := -pthread
PROG := bin/args
OBJS := $(patsubst src/%.c,obj/%.o, $(wildcard src/*.c))

.PHONY: all clean

all: build

build: $(PROG)

clean:
	rm -rf $(PROG) $(OBJS)

bin/args: obj/args.o

$(PROG):
	@$(MKDIR) $(dir $@)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $^

obj/%.o : src/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CFLAGS) -c -MD -o $@ $<
