#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int age = 0;

    printf("Entrez votre age : ");
    scanf("%d", &age);

    if (age >= 2 && age < 6)
    {
        printf("Salut bebe !");
    }
    else if (age >= 6 && age < 12)
    {
        printf("Salut gamin !");
    }
    else if (age >= 12 && age < 16)
    {
        printf("Salut jeune !");
    }
    else if (age >= 16 && age < 18)
    {
        printf("Salut ado !");
    }
    else if (age >= 18 && age < 68)
    {
        printf("Salut adulte !");
    }
    else if (age >= 68)
    {
        printf("Salut papy !");
    }
    else
    {
        printf("Je n'ai aucune reponse pour ton age");
    }
}