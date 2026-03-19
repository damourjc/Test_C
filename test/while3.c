#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int compteur = 0;

    while (compteur < 10)
    {
        printf("La variable compteur vaut %d\n", compteur);
        compteur++;
    }
}