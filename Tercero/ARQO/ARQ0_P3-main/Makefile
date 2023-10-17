LIBS = 
LIB_DIR = 
FLAGS = -O3 -g -Wall -D_GNU_SOURCE -I$(LIB_DIR) -I$(CDIR) -I$(EX1DIR) -I$(EX2DIR) -I$(EX3DIR) -I$(HDIR)
#ODIR=obj
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))
#_DEPS = 
HDIR=$(patsubst %,./headers,*)
CDIR=$(patsubst %,./common,*)
EX1DIR=./ex1
EX2DIR=./ex2
EX3DIR=$(patsubst %,./ex3,*)

.PHONY: clean all

all: exercise1 exercise3

fast: $(CDIR)/fast.c $(CDIR)/arqo3.c $(HDIR)/arqo3.h
	gcc $(FLAGS) $(LIB_DIR) -o $(CDIR)/fast $^ $(LIBS)

slow: $(CDIR)/slow.c $(CDIR)/arqo3.c
	gcc $(FLAGS) $(LIB_DIR) -o $(CDIR)/slow $^ $(LIBS) $(DEPS)

exercise1: fast slow
	bash ex1/slow_fast_time.sh

exercise2: 
	bash ex2/ex2.sh

exercise3: $(EX3DIR)/ex3_normal.c $(EX3DIR)/ex3_trasposed.c $(CDIR)/arqo3.c $(DEPS)
	gcc $(FLAGS) $(LIB_DIR) -o $(EX3DIR)/ex3_normal $(EX3DIR)/ex3_normal.c $(CDIR)/arqo3.c $(LIBS)
	gcc $(FLAGS) $(LIB_DIR) -o $(EX3DIR)/ex3_trasposed $(EX3DIR)/ex3_trasposed.c $(CDIR)/arqo3.c $(LIBS)
	bash ex3/ex3.sh

exercise4: $(EX3DIR)/ex3_normal.c $(EX3DIR)/ex3_trasposed.c $(CDIR)/arqo3.c $(DEPS)
	gcc $(FLAGS) $(LIB_DIR) -o $(EX3DIR)/ex3_normal $(EX3DIR)/ex3_normal.c $(CDIR)/arqo3.c $(LIBS)
	gcc $(FLAGS) $(LIB_DIR) -o $(EX3DIR)/ex3_trasposed $(EX3DIR)/ex3_trasposed.c $(CDIR)/arqo3.c $(LIBS)
	bash ex4/ex4.sh

run1: 
	bash ex1/slow_fast_time.sh
run2: 
	bash ex2/ex2.sh
run3: 
	bash ex3/ex3.sh
run4: 
	bash ex4/ex4.sh

plot1:
	Rscript ex1/plot_slow_fast.r
plot2:
	Rscript ex2/ex2.r
plot3:
	Rscript ex3/ex3.r
plot4:
	Rscript ex4/ex4.r

ex1cluster:  ex1/slow_fast_time.sh
	qsub -q intel.q script.q ex1/slow_fast_time.sh

ex2cluster: ex2/ex2.sh
	qsub -q intel.q script.q ex2/ex2.sh

ex3cluster: ex3/ex3.sh
	qsub -q intel.q script.q ex3/ex3.sh

ex4cluster: ex4/ex4.sh
	qsub -q intel.q script.q ex4/ex4.sh

clean:
	rm -f *.o *~ fast slow
	rm -f $(CDIR)/fast $(CDIR)/slow
	rm -f $(EX3DIR)/ex3_normal $(EX3DIR)/ex3_trasposed