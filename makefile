# Makefile Projet

CFLAGS = -Wall -std=c17 -pedantic
LDLIBS = -lMLV -lm
SRCS = $(wildcard src/*.c) 
OBJS = $(SRCS:src/%.c=obj/%.o)
EXEC = Test


$(EXEC): $(OBJS)
	gcc -Iinclude -o $@ $^ $(LDLIBS)

obj/%.o: src/%.c
	@mkdir -p obj
	gcc -Iinclude $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)