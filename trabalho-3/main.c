#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int tam = 0;
typedef struct {
    char palavra[20];
    char sinais[1];
}P;

void ler_arquivo(P historia[]){
    FILE* file = fopen("historia.txt", "r");
    char vet[50];
    
    char tmp;
    if(file){
        while (!feof(file) && !ferror(file)){
            tmp = fgetc(file);
            int i = 0;
            while ((tmp != ' ') ){
                vet[i] = tmp;
                tmp = fgetc(file);
                if (tmp == EOF){
                    break;
                }
                i++;
            }
            vet[i] = '\0';
            if(vet[0] != '\0'){
                strcpy(historia[tam].palavra,vet);
                tam++;
            }
        }
        printf("\nArquivo lido com sucesso\n");
    }
    else
        printf("Erro ao abrir o arquivo");
    fclose(file);
}

void arquivo_invertido(P historia[]){
    int i = tam;
    while (i != 0)
    {
        printf("%s ", historia[i].palavra);
        i--;
    }
    printf("\n\n");
}

void menu_opcoes(){
    printf("\na - Ler um arquivo texto\nb - Apresentar o arquivo invertido\nc - Procurar uma palavra.\n\n");
}

int main(){

    P historia[1000];
    char opcao;

    do
    {
        menu_opcoes();
        scanf("%c", &opcao);
        getchar();
        switch(opcao){
        case 'a':
            system("clear");
            ler_arquivo(historia);
            break;
        case 'b':
            system("clear");
            arquivo_invertido(historia);
            break;
        }
    }while (opcao != 'e');
    
    return 0;
}