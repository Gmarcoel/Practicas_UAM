CC = gcc -g
CFLAGS = -Wall -Wextra -pedantic -ansi -I -g -Iheaders -Iobj -Isrc
LDLIBS = -lodbc


ODIR = obj
SDIR = src
HDIR = headers

EXE = menu
_DEPS = odbc.h products.h orders.h customers.h
DEPS = $(patsubst %,$(HDIR)/%,$(_DEPS))
_OBJ = odbc.o menu.o products.o orders.o customers.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: dropdb createdb restore shell 
compile : $(EXE)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXE): $(DEPS) $(OBJ)
	$(CC) -o $(EXE) $^  $(LDLIBS)

clean :
	rm -f $(ODIR)/*.o core $(EXE)


# Database implementation

export PGDATABASE:=classicmodels
export PGUSER :=alumnodb
export PGPASSWORD :=alumnodb
export PGCLIENTENCODING:=LATIN9
export PGHOST:=localhost

DBNAME =$(PGDATABASE)
PSQL = psql
CREATEDB = createdb
DROPDB = dropdb --if-exists
PG_DUMP = pg_dump
PG_RESTORE = pg_restore


createdb:
	@echo Creando BBDD
	@$(CREATEDB)
dropdb:
	@echo Eliminando BBDD
	@$(DROPDB) $(DBNAME)
	rm -f *.log
dump:
	@echo creando dumpfile
	@$(PG_DUMP) > $(DBNAME).sql
restore:
	@echo restore data base
	@cat $(DBNAME).sql | $(PSQL)  
psql: shell
shell:
	@echo create psql shell
	@$(PSQL) 