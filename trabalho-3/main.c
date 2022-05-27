#include <stdio.h>
#include <stdlib.h>


void ler_arquivo(char historia[]){
    FILE* file = fopen("historia.txt", "r");
    int i = 0;
    if(file){
        for(i; (historia[i] = fgetc(file)) != EOF; i++){ 
        }
        historia[i] = '\0';
    }
    else
        printf("Erro ao abrir o arquivo");
    fclose(file);
}

void menu_opcoes(){
    printf("\na - Ler um arquivo texto\nb - Apresentar o arquivo invertido\nc - Procurar uma palavra.\n");
}

int main(){

    char historia[5876];
    char opcao;

    menu_opcoes();
    scanf("%c", &opcao);
    switch(opcao){

    case 'a':
        ler_arquivo(historia);
    }

    return 0;
}