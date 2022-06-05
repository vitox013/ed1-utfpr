#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int tam = 0;

typedef struct {
    char palavra[40];
}P;

void guardar_palavra(P palavras[], int i, char word[]){
    word[i] = '\0';
    strcpy(palavras[tam].palavra,word);
    tam++;
}

void ler_arquivo(char historia[]){
    FILE* file = fopen("historia.txt", "r");
    int i = 0;
    char letra;

    if(file){
        while (!feof(file) && !ferror(file)){
            letra = fgetc(file);
            historia[i] = tolower(letra);
            if (letra == EOF){
                historia[i - 1] = '\0';
                break;
            }
            i++;
        }
        printf("\nArquivo lido com sucesso\n");
    }
    else
        printf("Erro ao abrir o arquivo");
    fclose(file);
}

void formar_palavras(char historia[], P palavras[], int indices[]){
    int j = 0, i;
    char word[20];
    int indice, char_apos_pt = 0;
    char letra;
    
    while(historia[j] != '\0'){
        i = 0;
        indice = j;
        if(!char_apos_pt)
            letra = historia[j];
        while((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122) || ((letra == '-') && (historia[j + 1] >= 97 && historia[j + 1] <= 122))){ //vericando se é uma letra ou uma palavra com hifen
            word[i] = letra;
            j++;
            letra = historia[j];    
            i++;
        }
        if(letra == ' '){  //verificando se apos a letra é um espaco e inserindo esse espaco junto com a palavra
            word[i] = ' ';
            i++;
            indices[tam] = indice;
            guardar_palavra(palavras, i, word);
            char_apos_pt = 0;
            j++;
        }
        else{
            if(historia[j - 1] != ' ') //verificando se antes da pontuacao há um espaco
                indices[tam] = indice;
                guardar_palavra(palavras, i, word);
            i = 0;
            while ((letra < 65 || letra > 90) && (letra < 97 || letra > 122)){ //enquanto nao for uma letra
                indice = j;
                word[i] = letra;
                j++;
                letra = historia[j]; 
                i++;
                if(letra == '\0'){ //verificando se nao é o fim da string historia
                    break;
                }
                if((letra != ' ') && ((letra < 65 || letra > 90) && (letra < 97 || letra > 122))){ //verificando se o prox char é diferente de espaco e nao é uma letra
                    indices[tam] = indice;
                    guardar_palavra(palavras, i, word);
                    i = 0;  
                }else if((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122)){    //caso apos o ' ' seja um char a flag char_apos_pt = 1 para n ir pra prox letra
                    char_apos_pt = 1;
                }
            }
            indices[tam] = indice;
            guardar_palavra(palavras, i, word);
        }
    }
}

void criar_arquivo_invertido(P palavras[], int indices[]){//j
    FILE *arquivo = fopen("arquivo_invertido.txt", "w");
    int i = 0;

    if(arquivo){
        for(i; i < tam; i++){
            fprintf(arquivo,"%s %d\n", palavras[i].palavra, indices[i]);
        }   
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir o arquivo!\n");  
}
    


void menu_opcoes(){
    printf("\na - Ler um arquivo texto\nb - Apresentar o arquivo invertido\nc - Procurar uma palavra.\n\n");
}

int main(){
    char* historia;
    historia = (char*) malloc(6000 * sizeof(char));
    char opcao;
    P palavras[1500];
    int indices[1500];
    int k = 0;
    do
    {
        menu_opcoes();
        scanf("%c", &opcao);
        getchar();
        switch(opcao){
        case 'a':
            system("clear");
            ler_arquivo(historia);
            formar_palavras(historia, palavras, indices);
            break;
        case 'b':
            system("clear");
            criar_arquivo_invertido(palavras, indices);
            break;
        }
    }while (opcao != 'e');
    
    free(historia);
    return 0;
};
    
    
