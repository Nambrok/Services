#include "service.h"

int minimum(service_t * service){
        int * data = service->data; int i;
        int min = INT_MAX;
        for(i = 0; i< service->nbData; i++) {
                if(data[i] < min) {
                        min = data[i];
                }
        }
        return min;
}

int maximum(service_t * service){
        int * data = service->data; int i;
        int max = INT_MIN;
        for(i = 0; i< service->nbData; i++) {
                if(data[i] > max) {
                        max = data[i];
                }
        }
        return max;
}

int average(service_t * service){
        int * data = service->data; int i;
        int somme = 0;
        for(i = 0; i<service->nbData; i++) {
                somme += data[i];
        }
        return somme/(service->nbData);
}

void tri(int * tab, int n){
        int i, j;
        for(i = 0; i<n; i++) {
                int i_min = i;
                int v_min = tab[i];
                for(j = i+1; j<n; j++) {
                        if(tab[j]<tab[i_min]) {
                                i_min = j;
                                v_min = tab[j];
                        }
                }
                int tmp = tab[i];
                tab[i] = tab[i_min];
                tab[i_min] = tmp;
        }
}

int mediane(service_t * service){
        tri(service->data, service->nbData);
        if(service->nbData%2 == 0) {
                return service->data[(service->nbData/2)-1]+service->data[(service->nbData)/2];
        }
        else{
                return service->data[service->nbData/2];
        }
}

int afficherData(service_t * service){
        int i = 0;
        for(i = 0; i<service->nbData; i++) {
                printf("%d ", service->data[i]);
        }
        printf("\n");
}
