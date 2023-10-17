#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define MAX_IDS 200

typedef struct _Set Set;


/*Functions*/

Set* set_create(Id id);
STATUS set_destroy(Set* set);
STATUS set_add_id(Set* set, Id id);
STATUS set_del_id(Set* set, Id id);




