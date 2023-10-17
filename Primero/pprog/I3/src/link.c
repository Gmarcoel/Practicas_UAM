/***
 * @brief Link functions
 * @file link.c
 * @author Gabriela Trabajo
 * @version 1.0 
 * @date 24/03/20
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "types.h"
#include "link.h"

struct _Link
{
    Id idLink;
    char name[WORD_SIZE + 1];
    Id id1; /*space 1*/
    Id id2; /*space 2*/
    CONNECTION state; /*open or close*/
};

Link *link_create()
{

    Link *newLink = NULL;

    newLink = (Link *)malloc(sizeof(Link));

    if (newLink == NULL)
    {
        return NULL;
    }

    newLink->idLink = NO_ID;
    newLink->name[0] = '\0'; /*revisar*/
    newLink->id1= NO_ID;
    newLink->id2= NO_ID;
    newLink->state= -1;

    return newLink;
}

STATUS link_destroy(Link *ln)
{
    if (ln == NULL)
        return ERROR;

    free(ln);
    ln = NULL;

    return OK;
}

STATUS link_set_idLink(Link *ln, Id id)
{

    if (ln == NULL || id == NO_ID)
        return ERROR;

    ln->idLink = id;

    return OK;
}

STATUS link_set_name(Link *ln, char *name)
{

    if (ln == NULL || name == NULL)
        return ERROR;

    if (!strcpy(ln->name, name)) return ERROR;

    return OK;
}

STATUS link_set_id1(Link *ln, Id id)
{

    if (ln == NULL || id == NO_ID)
        return ERROR;

    ln->id1=id;

    return OK;
}

STATUS link_set_id2(Link *ln, Id id)
{

    if (ln == NULL || id == NO_ID)
        return ERROR;

    ln->id2 = id;

    return OK;
}

STATUS link_set_connection(Link *ln, Id id1, Id id2)
{

    if (ln == NULL || id1 == NO_ID  || id2 == NO_ID)
        return ERROR;

    if (link_set_id1(ln, id1) == ERROR || link_set_id2(ln, id2) == ERROR)
        return ERROR;

    return OK;
}

STATUS link_set_status(Link *ln, CONNECTION state)
{

    if (ln == NULL || (state != CLOSED && state != OPEN))
        return ERROR;

    ln->state = state;

    return OK;
}

Id link_get_idLink(Link *ln)
{
    if (ln == NULL) return NO_ID;
    return ln->idLink;

}

const char *link_get_name(Link *ln)
{
    if (!ln) return NULL;
    return ln->name;
}

Id link_get_id1(Link *ln)
{
    if (ln == NULL) return NO_ID;
    return ln->id1;
}

Id link_get_id2(Link *ln)
{
    if (ln == NULL) return NO_ID;
    return ln->id2;
}

CONNECTION link_get_status(Link *ln)
{
    if (ln == NULL) return -1;
    return ln->state;
}

Id link_get_otherId(Link *ln, Id id)
{
    if(ln==NULL || id==NO_ID) return NO_ID;

    if(id==link_get_id1(ln))
    {
        return link_get_id2(ln);
    }
    else if(id==link_get_id2(ln))
    {
        return link_get_id1(ln);
    }
    else
    {
        return NO_ID;
    }
}


STATUS link_print(Link *ln)
{
    Id idaux = NO_ID, idaux2 = NO_ID;

    if (ln == NULL) return ERROR;

    fprintf(stdout, "Link name: %s\n", ln->name);

    idaux=link_get_idLink(ln);
    if (idaux == NO_ID) return ERROR;
    fprintf(stdout, "Link id: %ld\n", idaux);

    idaux=link_get_id1(ln);
    idaux2=link_get_id2(ln);
    if (idaux == NO_ID || idaux2 == NO_ID) return ERROR;
    fprintf(stdout, "Connects spaces with ids %ld and %ld\n", idaux, idaux2);

    fprintf(stdout, "The status of the link is:\n"); 
    if(link_get_status(ln) == OPEN){
        fprintf(stdout, "Open");
    }
    else if(link_get_status(ln) == CLOSED){
        fprintf(stdout, "Closed");
    }
    else{
        return ERROR;
    }
    
    return OK;
}