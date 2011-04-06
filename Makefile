DEFS	= -03
CC    = gcc
APP   = wilson

Default = $(APP)

$(APP): $(APP).c
	$(CC) $(APP).c -o $(APP)
primos: primos.c
	$(CC) -static $(LIBS) primos.c -o primos
clean:
	rm -f *.o $(APP)


