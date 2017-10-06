#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

enum{
  max, min, avg, med
};

struct service_t{
  int * data;
  int (*func)(struct service_t*);
  int nbData;
  int resultat;
};
typedef struct service_t service_t;

int minimum(service_t * service){
    int * data = service->data; int i;
    int min = INT_MAX;
    for(i = 0; i< service->nbData; i++){
      if(data[i] < min){
        min = data[i];
      }
    }
    return min;
}

int maximum(service_t * service){
    int * data = service->data; int i;
    int max = INT_MIN;
    for(i = 0; i< service->nbData; i++){
      if(data[i] > max){
        max = data[i];
      }
    }
    return max;
}

int average(service_t * service){
  int * data = service->data; int i;
  int somme = 0;
  for(i = 0; i<service->nbData; i++){
    somme += data[i];
  }
  return somme/(service->nbData);
}

void tri(int * tab, int n){
  int i, j;
  for(i = 0; i<n; i++){
    int i_min = i;
    int v_min = tab[i];
    for(j = i+1; j<n; j++){
      if(tab[j]<tab[i_min]){
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
  if(service->nbData%2 == 0){
    return service->data[(service->nbData/2)-1]+service->data[(service->nbData)/2];
  }
  else{
    return service->data[service->nbData/2];
  }
}

int afficherData(service_t * service){
  int i = 0;
  for(i = 0; i<service->nbData; i++){
    printf("%d ", service->data[i]);
  }
  printf("\n");
}

void initiationService(service_t * service, int data[], int tailleData, int idService){
  int i = 0;
  int * newData = malloc(tailleData * sizeof(int));
  for(i = 0; i<tailleData; i++){
    newData[i] = data[i];
  }
  service->data = newData;
  service->nbData = tailleData;
  service->resultat = 0;

  switch (idService) {
    case min:
      service->func = &(minimum);
      break;
    case max:
      service->func = &(maximum);
      break;
    case avg:
      service->func = &(average);
      break;
    case med:
      service->func = &(mediane);
      break;
    default:
      fprintf(stderr, "Le service n'est pas reconnue.\n");
      service->func = &(afficherData);
      break;
  }
}

void extractionService(char* file){ //Exctraction Service doit créer des services pour chaque demande du client puis l'exécuter(et afficher).
  service_t newService;
  char * nomRequete; char * typeDeTraitement; char * typeVar;
  FILE * fi = NULL; int etape = 0; int i;
  char buffer[256]; char * res;
  int dataTmp[1024]; int taille;
  fi = fopen(file, "r");
  if(fi){
    while(fgets(buffer, 256, fi) != NULL){
      if(etape == 0){
        res = strtok(buffer, ":");
        nomRequete = strtok(NULL, "\n"); //Nom de la demande de service du client
        if(nomRequete != NULL){
            printf("Requete : %s\n", nomRequete);
        }
      }
      else if(etape == 1){
        res = strtok(buffer, ":");
        typeVar = strtok(NULL, "\n\0");
        printf("Type des variables : %s\n", typeVar);
      }
      else if(etape == 2){
        res = strtok(buffer, ":");
        i = 0; taille = 0;
        res = strtok(NULL, ";\n\0");
        while(res != NULL){
          dataTmp[i++] = atoi(res);
          taille++;
          res = strtok(NULL, ";\n\0");
        }
      }
      else if(etape == 3){
        res = strtok(buffer, ":");
        typeDeTraitement = strtok(NULL, "\n");//type de traitement à effectuer sur les data.
        printf("Type de traitement demandé : %s\n", typeDeTraitement);

        //Puis à la dernière étape, on lance le service.
        if(typeDeTraitement[0] == 'm' && typeDeTraitement[1] == 'a'){
          initiationService(&newService, dataTmp, taille, max);
          printf("maximum\n");
        }
        else if(typeDeTraitement[0] == 'm' && typeDeTraitement[1] == 'i'){
          initiationService(&newService, dataTmp, taille, min);
          printf("minimum\n");
        }
        else if(typeDeTraitement[0] == 'a'){
          initiationService(&newService, dataTmp, taille, avg);
          printf("average\n");
        }
        else if(typeDeTraitement[0] == 'm' && typeDeTraitement[1] == 'e'){
          initiationService(&newService, dataTmp, taille, med);
          printf("mediane\n");
        }

        printf("Résultats : %d\n", newService.func(&newService));
      }
      etape =(etape+1) % 4 ;
    }
  }
  else{
    fprintf(stderr, "Erreur : lors de l'ouverture du fichier %s.\n", file);
  }
}

int main(int argc, char* argv[]){
  if(argc > 1){
    extractionService(argv[1]);
  }

  return 0;
}
