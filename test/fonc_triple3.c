#include <stdio.h>
#include <stdlib.h>

int triple(int nombre)
{
    return 3 * nombre;
}    

int main(int argc, char *argv[])
{
    int nombreEntre = 0;
    
    printf("Entrez un nombre... ");
    scanf("%d", &nombreEntre);

    // Le résultat de la fonction est directement envoyé au printf et n'est pas stocké dans une variable
    printf("Le triple de ce nombre est %d\n", triple(nombreEntre));
     
    return 0;
}