IDIR =include
SDIR=src
BDIR=build
CC=gcc
CFLAGS=-std=gnu99 -I$(IDIR) -DLINUX -O0

STDLIB=stdlib

ODIR=obj
LDIR =../lib

LIBS=-lm -lreadline -lcurl

_DEPS = Lval.h ParserDefinition.h Builtins.h mpc.h Environment.h Curl.h Maths.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Lval.o ParserDefinition.o Builtins.o mpc.o Environment.o Curl.o Maths.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tamara: $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)
	cp -r $(STDLIB)/* $(BDIR)

.PHONY: clean tests dirs

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(BDIR)/*

tests:	tamara tests/*.ta
	./$(BDIR)/tamara tests/*.ta

$(shell mkdir -p $(ODIR))
$(shell mkdir -p $(BDIR))
