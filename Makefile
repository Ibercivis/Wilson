DEFS	= -03
CC    = gcc
APP   = wilson
LIBS  = -lgmp

Default = $(APP)

$(APP): $(APP).c
	$(CC) $(LIBS) $(APP).c -o $(APP)
clean:
	rm -f *.o $(APP)


