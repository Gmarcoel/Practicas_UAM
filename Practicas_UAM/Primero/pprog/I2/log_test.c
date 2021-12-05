#include "log.h"

int main(){
    Log* log;
    log = log_create(0);

    /*Name test*/
    printf("%s\n",log->name);

    log_set_name(log,"LOG");
    
    printf("%s\n",log->name);
    
    /*File test*/

    log_write(log,"HOLA");
    


    log_write(log,"ADIOS");
    return 0;    
}