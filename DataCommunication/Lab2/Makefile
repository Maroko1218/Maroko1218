src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = --std=c11 -g

run: sim
	./sim 2 0 0.5 100000 2

sim: $(obj)
	$(CC) $(CFLAGS) -o $@ $^
	
.PHONY: clean

clean:
	rm -f $(obj) sim

