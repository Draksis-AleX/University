#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error(char* str){
    perror(str);
    exit(-1);
}

char* scrivi(char testo[50]){
    do
    {
        printf("Inserisci un parola di massimo 50 caratteri: \n\t >>");
        scanf("%s", testo);
    } while (strlen(testo) > 50);
    return testo;
}

int main(int argc, char const *argv[])
{
    FILE* file;
    if((file = fopen("file", "wb+")) == NULL) error("<<Errore>> : Apertura file.\n");

    char text[50];
    scrivi(text);

    while (strcmp(text, "FINE") != 0)   
    {
        fprintf(file, "%s ", text);
        scrivi(text);
    }
    
    fclose(file);
    return 0;
}
