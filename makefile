# Makefile Projet

CFLAGS = -Wall -std=c17 -pedantic -MMD
LDLIBS = -lMLV -lm
SRCS = $(wildcard src/*.c) 
OBJS = $(SRCS:src/%.c=bin/%.o)
EXEC = TowerDefense

$(EXEC): $(OBJS)
	gcc -Iinclude -o $@ $^ $(LDLIBS)

bin/%.o: src/%.c
	@mkdir -p bin
	gcc -Iinclude $(CFLAGS) -c $< -o $@

-include $(wildcard bin/*.d)

clean:
	rm -f $(EXEC) $(OBJS) bin/*.d
