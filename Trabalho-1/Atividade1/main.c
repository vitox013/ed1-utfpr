#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    char nome[25];
    char rg[8];
}Pessoa;

typedef struct no{
    Pessoa p;
    struct no *proximo;

}No;

typedef struct{
    No *prim;
    No *fim;
}Fila;

void criar_fila(Fila *fila);

void preencher_e_inserir_sequencial(char f[], Fila *fila);

void ler_arquivo_e_inserir_encadeada(char fname[], No **lista);

void opcao_arquivo(char *nome);


int main(){

    No *lista = NULL;
    Fila fila;
    int opcao;
    char nome[15] = {};
    time_t tIni, tFim;
    float tSequencial, tEncadeada;


    do
    {
        printf("\n\n0 - Sair\n1 - Inserir na lista sequencial\n2 - Inserir na lista encadeada\n3 - mostrar a diferenca de tempo de execucao\n\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            criar_fila(&fila);
            opcao_arquivo(nome);
            tIni = time(NULL);
            preencher_e_inserir_sequencial(nome, &fila);
            tFim = time(NULL);
            tSequencial = difftime(tFim, tIni);
            break;
        case 2:
            tIni = time(NULL);
            ler_arquivo_e_inserir_encadeada(nome, &lista);
            tFim = time(NULL);
            tEncadeada = difftime(tFim, tIni);
            break;
        case 3:
            printf("\nTempo execucao sequencial : %.2f\nTempo execucao encadeada: %.2f\n\n", tSequencial, tEncadeada);
            break;
        default:
            if(opcao != 0)
                printf("\nOpcao invalida!");
            break;
        }
    } while (opcao != 0);

    
    
    return 0;
}

void criar_fila(Fila *fila){
    fila->prim = NULL;
    fila->fim = NULL;
}

void preencher_e_inserir_sequencial(char f[], Fila *fila){

    char copia_linha[17];
    char linhaCompleta[17];
    Pessoa pessoa;
    char *rg;
    FILE *arquivo = fopen(f, "r");

    if(arquivo){
        while(fgets(linhaCompleta, 50, arquivo)){
            strcpy(copia_linha, linhaCompleta);
            strcpy(pessoa.nome, strtok(linhaCompleta, ",") );

            rg = strtok(copia_linha, ",");
            while(rg){
                strcpy(pessoa.rg, rg);
                rg = strtok(NULL, ",");
            }

            No *novo = malloc(sizeof(No));

            if(novo){
                novo->p = pessoa;
                novo->proximo = NULL;
                if(fila->prim == NULL){
                    fila->prim = novo;
                    fila->fim = novo;
                }
                else{
                    fila->fim->proximo = novo;
                    fila->fim = novo;
                }
            }
            else
                printf("\nNao foi possivel alocar memoria!\n");
        }
        fclose(arquivo);
    }
    else
        printf("\nERRO ao abrir o arquivo!");
}

void ler_arquivo_e_inserir_encadeada(char fname[], No **lista){
    FILE *arquivo = fopen(fname, "r");
    Pessoa pessoa;
    char copia_linha[17];
    char linhaCompleta[17];
    char *rg;

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
                printf("Erro ao alocar memoria!");
        }
    }
    else
        printf("\nERRO AO ABRIR O ARQUIVO!");

    fclose(arquivo);

}

void opcao_arquivo(char *nome){

    char opcao_arq;

    printf("\nQual arquivo?\na) NomeRG10.txt\nb) NomeRG50.txt\nc) NomeRG100.txt\nd) NomeRG1K.txt\ne) NomeRG10K.txt\nf) NomeRG1M.txt\ng) NomeRG100M.txt\n\n");
    scanf(" %c", &opcao_arq);

    switch(opcao_arq){
    case 'a':
        strcpy(nome, "NomeRG10.txt");
    break;

    case 'b':
        strcpy(nome, "NomeRG50.txt");
    break;

    case 'c':
        strcpy(nome, "NomeRG100.txt");
    break;

    case 'd':
        strcpy(nome, "NomeRG1K.txt");
    break;

    case 'e':
        strcpy(nome, "NomeRG10K.txt");
    break;

    case 'f':
        strcpy(nome, "NomeRG1M.txt");
    break;

    case 'g':
        strcpy(nome, "NomeRG100M.txt");
    break;

    default:
        if(opcao_arq < 'a' || opcao_arq > 103)
            printf("Opcao invalida!");
    break;
    }
}

