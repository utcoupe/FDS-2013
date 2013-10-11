DEBUG=yes
SDL=yes

CC=gcc
SOURCES=src/main.c src/fast_math.c src/analyzer.c
OBJS=$(SOURCES:.c=.o)

EXEC=hokuyo
LFLAGS=-Wall -Werror `urg_c-config --libs` -lm
CFLAGS=-Wall `urg_c-config --cflags`

ifeq ($(DEBUG),yes)
	CFLAGS += -D DEBUG
else
	CFLAGS += -Werror
	LFLAGS += -Werror
endif

ifeq ($(SDL),yes)
	SOURCES+= src/sdl.c
	LFLAGS+= `sdl-config --libs` 
	CFLAGS+= -D SDL `sdl-config --cflags` 
	EXEC=hokuyo_sdl
endif

all: $(EXEC)

$(EXEC): $(OBJS) 
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -f src/*.o
mrproper: clean
	rm $(EXEC)

.PHONY: clean
