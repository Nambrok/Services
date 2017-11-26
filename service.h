#ifndef SERVICE_H
#define SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

enum {
        max, min, avg, med
};

struct service_t {
        int * data;
        int (*func)(struct service_t*);
        int nbData;
        int resultat;
        char * typeVar;
};
typedef struct service_t service_t;


#endif
