CC = gcc
LIBS = -lgomp -lm
LIB_DIR =  
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp 

.PHONY: clean all

all: edgeDetector edgeDetector_mod edgeDetector_par

edgeDetector: edgeDetector.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -o $@ edgeDetector.c $(LIBS)

edgeDetector_mod: edgeDetector_mod.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -o $@ edgeDetector_mod.c $(LIBS)

edgeDetector_par: edgeDetector_par.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -o $@ edgeDetector_par.c $(LIBS)

stb_image.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

stb_image_write.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h


ex5cluster:  edgeDetector.sh
	rm simple.out
	qsub -q mv.q -pe openmp 8 edgeDetector.sh

ex5cluster2:  edgeDetector_table.sh
	rm simple.out
	qsub -q mv.q -pe openmp 8 edgeDetector_table.sh

clean:
	rm -f *.o *~ edgeDetector edgeDetector_mod edgeDetector_par
	
clear:
	rm -f *.o *~
