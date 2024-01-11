# Makefile Projet

CFLAGS = -Wall -std=c17 -pedantic -g -g3 -MMD
LDLIBS = -lMLV -lm
SRCS = $(wildcard src/*.c) 
OBJS = $(SRCS:src/%.c=obj/%.o)
EXEC = Test

$(EXEC): $(OBJS)
	gcc -Iinclude -o $@ $^ $(LDLIBS)

obj/%.o: src/%.c
	@mkdir -p obj
	gcc -Iinclude $(CFLAGS) -c $< -o $@

-include $(wildcard obj/*.d)

clean:
	rm -f $(EXEC) $(OBJS) obj/*.d
