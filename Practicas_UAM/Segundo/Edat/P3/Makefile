CC = gcc -g
CFLAGS = -Wall -Wextra -pedantic -ansi -Iheaders
# LDLIBS = -lodbc

# recompile if this header changes
HEADERS = headers/utils.h headers/tester.h

ODIR = obj
SDIR = src

EXE = menu
_OBJ = tester.o checkUtils.o checkCreateTable.o checkReplaceExtensionByIdx.o \
checkCreateIndex.o checkPrint.o checkFindKey.o checkAddIndexEntry.o checkAddTableEntry.o \
Use.o Insert.o Print.o menu.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
#all : $(EXE)


$(ODIR)/%.o: $(SDIR)/%.c $(HEADERS)
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c -o $@ $<

$EXE: $(DEPS) $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LDLIBS)

clean :
	rm -f obj/*.o core $(EXE)

cleant :
	rm -f *table.dat *table.idxx