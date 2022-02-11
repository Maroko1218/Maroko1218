src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = --std=c11 -g

run: sim
	./sim 20 0.2 0.2 10 5

sim: $(obj)
	$(CC) $(CFLAGS) -o $@ $^
	
.PHONY: clean

clean:
	rm -f $(obj) sim

