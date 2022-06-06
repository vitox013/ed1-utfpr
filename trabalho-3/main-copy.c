#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int tam = 0;
int tam2 = 0;

typedef struct {
    char palavra[40];
    int ind;
    int ja_foi;
}P;

typedef struct {
    char p_unica[25];
    int pos_vet[30];
    int freq;
}Word;

void guardar_palavra(P palavras[], int i, char word[], int ind){
    word[i] = '\0';
    palavras[tam].ind = ind;
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

void formar_palavras(char historia[], P palavras[]){
    int j = 0, i;
    char word[20];
    int ind, char_apos_pt = 0;
    char letra;
    
    while(historia[j] != '\0'){
        i = 0;
        ind = j;
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
            guardar_palavra(palavras, i, word, ind);
            char_apos_pt = 0;
            j++;
        }
        else{
            if(historia[j - 1] != ' ') //verificando se antes da pontuacao há um espaco
                guardar_palavra(palavras, i, word, ind);
            i = 0;
            while ((letra < 65 || letra > 90) && (letra < 97 || letra > 122)){ //enquanto nao for uma letra
                ind = j;
                word[i] = letra;
                j++;
                letra = historia[j]; 
                i++;
                if(letra == '\0'){ //verificando se nao é o fim da string historia
                    break;
                }
                if((letra != ' ') && ((letra < 65 || letra > 90) && (letra < 97 || letra > 122))){ //verificando se o prox char é diferente de espaco e nao é uma letra
                    guardar_palavra(palavras, i, word, ind);
                    i = 0;  
                }else if((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122)){    //caso apos o ' ' seja um char a flag char_apos_pt = 1 para n ir pra prox letra
                    char_apos_pt = 1;
                }
            }
            guardar_palavra(palavras, i, word, ind);
        }
    }
}

void criar_arquivo_invertido(Word words_u[]){
    FILE *arquivo = fopen("arquivo_invertido.txt", "w");
    int i = 0;

    if(arquivo){
        for(i; i <= tam2; i++){
            fprintf(arquivo,"%s |%d\n", words_u[i].p_unica, words_u[i].freq);
        }   
    fclose(arquivo);
    }
    else
        printf("\nErro ao abrir o arquivo!\n");  
}
    
void menu_opcoes(){
    printf("\na - Ler um arquivo texto\nb - Apresentar o arquivo invertido\nc - Procurar uma palavra.\n\n");
}


void palavras_unicas(P palavras[], Word words_u[]){
    int  i = 0,j;
    int res = 0;
    
    while(i <= tam){
        j = i + 1;
        while(j <= tam){
            res = strcmp(palavras[i].palavra, palavras[j].palavra);
            if(res == 0 || res == -32 || res == 32){
                palavras[j].ja_foi = 1;
                break;
            }
            j++;
        }
        if(palavras[i].ja_foi == 0){
            strcpy(words_u[tam2].p_unica,palavras[i].palavra);
            tam2++;
        }
        i++;
    }
}
    
void frequencia_palavras(Word words_u[], P palavras[]){
    int i = 0, j;
    int res;
    while(i <= tam2){
        j = i;
        words_u[i].freq = 0;
        while (j <= tam){
            res = strcmp(words_u[i].p_unica, palavras[j].palavra);
            if(res == 0 || res == 32 || res == -32){
                words_u[i].freq++;
            }
            j++;
        }
        i++;
    }
}


int main(){
    char historia[6000], opcao;
    P palavras[1500];
    Word words_u[1000];
    do
    {
        menu_opcoes();
        scanf("%c", &opcao);
        getchar();
        switch(opcao){
        case 'a':
            system("clear");
            ler_arquivo(historia);
            formar_palavras(historia, palavras);
            palavras_unicas(palavras, words_u);
            break;
        case 'b':
            system("clear");
            frequencia_palavras(words_u, palavras);
            criar_arquivo_invertido(words_u);
            break;
        }
    }while (opcao != 'e');
    
    return 0;
};
    
    
