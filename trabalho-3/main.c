#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tam = 0;

typedef struct {
    char palavra[40];
}P;

void guardar_palavra(P historia[], int i, char vet[]){
    vet[i] = '\0';
    strcpy(historia[tam].palavra,vet);
    tam++;
}

void ler_arquivo(P historia[]){
    FILE* file = fopen("historia.txt", "r");
    char vet[40];
    int char_apos_pt = 0;
    
    char tmp;
    if(file){
        while (!feof(file) && !ferror(file)){
            if(!char_apos_pt)
                tmp = fgetc(file);
            int i = 0;
            while ((tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122)){ //enquanto for uma letra maiuscula ou minuscula
                vet[i] = tmp;
                tmp = fgetc(file);
                if (tmp == EOF){    //verificao se é a ultima letra do texto
                    break;
                }
                i++;
            }
            if(tmp == ' '){     //verificando se apos a letra é um espaço, para guardar o espaco junto com a palavra
                vet[i] = ' ';
                i++;
                guardar_palavra(historia, i, vet);
                char_apos_pt = 0;
            }
            else{
                guardar_palavra(historia, i, vet);
                int i = 0;
                while ((tmp < 65 || tmp > 90) && (tmp < 97 || tmp > 122)){ //enquanto nao for uma letra
                    vet[i] = tmp;
                    tmp = fgetc(file);
                    i++;
                    if (tmp == EOF){    //verificao se é a ultima letra do texto
                        break;
                    }
                    if((tmp != ' ') && ((tmp < 65 || tmp > 90) && (tmp < 97 || tmp > 122))){ //verificando se o prox char é diferente de espaco e nao é uma letra
                        guardar_palavra(historia, i, vet);
                        i = 0;
                    }else if((tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122)){    //caso apos o ' ' seja um char a flag char_apos_pt = 1 para n ir pra prox letra
                        char_apos_pt = 1;
                    }
                }
                guardar_palavra(historia, i, vet);
            }
        }
        printf("\nArquivo lido com sucesso\n");
    }
    else
        printf("Erro ao abrir o arquivo");
    fclose(file);
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
            printar_texto(historia);
        }
    }while (opcao != 'e');
    
    return 0;
}