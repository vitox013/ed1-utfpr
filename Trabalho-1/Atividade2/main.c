#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[20];
    char rg[8];
}Pessoa;

typedef struct no
{
    Pessoa p;
    struct no *proximo;
}No;

void ler_arquivo_e_inserir_na_fila_sequencial(char file[],No **fila){ //1) a. Lista sequencial(fila)

    char copia_linha[50];
    char linhaCompleta[50];
    Pessoa pessoa;
    char *rg;
    FILE *arquivo = fopen(file, "r");

    if(arquivo){
        while(fgets(linhaCompleta, 50, arquivo)){
            strcpy(copia_linha, linhaCompleta);
            strcpy(pessoa.nome, strtok(linhaCompleta, ",") );

            rg = strtok(copia_linha, ",");
            while(rg){
                strcpy(pessoa.rg, rg);
                rg = strtok(NULL, ",");
            }

            No *aux, *novo = malloc(sizeof(No));

            if(novo){
                novo->p = pessoa;
                novo->proximo = NULL;
                if(*fila == NULL)
                    *fila = novo;
                else{
                    aux = *fila;
                    while(aux->proximo)
                        aux = aux->proximo;
                    aux->proximo = novo;
                }
            }
            else
                printf("\nErro ao alocar memoria\n");
        }
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir arquivo!\n");    
}

void ler_arquivo_e_inserir_na_lista_encadeada(char file[], No **lista){ //1) b. Lista encadeada(lista)

    char copia_linha[50];
    char linha_completa[50];
    Pessoa pessoa;
    char *rg;
    FILE *arquivo = fopen(file, "r");

    if(arquivo){
        while(fgets(linha_completa, 50, arquivo)){
            strcpy(copia_linha, linha_completa);
            strcpy(pessoa.nome,strtok(linha_completa, ","));

            rg = strtok(copia_linha, ",");
            while(rg){
                strcpy(pessoa.rg, rg);
                rg = strtok(NULL, ",");
            }
            No *aux, *novo = malloc(sizeof(No));

            if(novo){
                novo->p = pessoa;
                novo->proximo = NULL;
                if(*lista == NULL)
                    *lista = novo;
                else{
                    aux = *lista;
                    while(aux->proximo)
                        aux = aux->proximo;
                    aux->proximo = novo;
                }
            }
            else
                printf("\nERRO AO ALOCAR MEMORIA!\n");
        }
        fclose(arquivo);
    }
    else
        printf("\nERRO AO ABRIR O ARQUIVO!\n");


}

No* remover_do_inicio_fila_sequencial(No **fila){ //IV fila
    No *remover = NULL;

    if(*fila){
        remover = *fila;
        *fila = remover->proximo;
    }
    else
        printf("\nFILA VAZIA!\n");
    return remover;
}

No* remover_do_inicio_lista_encadeada(No **lista){ //IV lista
    No *remover = NULL;

    if(*lista){
        remover = *lista;
        *lista = remover->proximo;
    }
    else
        printf("\nLISTA VAZIA!\n");
    return remover;
}

void imprimir_fila_sequencial(No *fila){ //XIII fila
    printf("\n-----------FILA------------\n");
    while(fila){
        printf("Nome: %s\nRg: %s\n\n", fila->p.nome, fila->p.rg);
        fila = fila->proximo;
    }
    printf("\n-----------FIM FILA-----------\n");
}

void imprimir_lista_encadeada(No *lista){ //XIII lista
    printf("\n-----------LISTA------------\n");
    while(lista){
        printf("Nome: %s\nRg: %s\n\n", lista->p.nome, lista->p.rg);
        lista = lista->proximo;
    }
    printf("\n-----------FIM LISTA-----------\n");
}


int main(){

    No *fila = NULL;
    No *lista = NULL;
    char file_name[15] = {"NomeRG10.txt"};
    int opcao;
    char opcao_letra;
    do
    {
        printf("\n0 - Sair\n1 - Ler dados(nome e rg) de um arquivo e armazenar em uma LISTA SEQUENCIAL(fila) e LISTA ENCADEADA!\n");
        printf("8 - Mostrar listas na tela\n\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            if(lista == NULL && fila == NULL){
            ler_arquivo_e_inserir_na_fila_sequencial(file_name, &fila);
            ler_arquivo_e_inserir_na_lista_encadeada(file_name, &lista);

            if(fila)
                printf("\nFILA PREENCHIDA COM SUCESSO!\n\n");
            if(lista)
                printf("\nLISTA PREENCHIDA COM SUCESSO!\n\n");
            }
            else
                printf("\n\n FILA E LISTAS JA ESTAO PREENCHIDAS!\n\n");
            break;
        case 8:
            do{
                printf("\nDeseja imprimir qual lista?\n");
                printf("a) Fila\nb) Lista encadeada\n\n");
                scanf(" %c", &opcao_letra);
                if(opcao_letra == 'a' || opcao_letra == 'A')
                    imprimir_fila_sequencial(fila);
                else if(opcao_letra == 'b' || opcao_letra == 'B')
                    imprimir_lista_encadeada(lista);
                else
                    printf("\nOpcao invalida!");
            }while(opcao_letra != 'a' && opcao != 'b' && opcao_letra != 'A' && opcao_letra != 'B');
        default:
            break;
        }
    } while (opcao != 0);
    

    

    return 0;
}