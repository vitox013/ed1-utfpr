#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int tam;
}Fila;

void criar_fila(Fila *fila);

void preencher_e_inserir(char f[], Fila *fila);

void imprimir_pessoa(Pessoa p);

void imprimir_fila(Fila *fila);

void opcao_arquivo(char *nome);



int main(){

    Fila fila;
    int opcao;
    char nome[15] = {};
    

    criar_fila(&fila);

    do{
        printf("\n0 - Sair\n1 - Inserir na lista a partir do arquivo\n2 - Imprimir lista preenchida\n\n");
        scanf("%d", &opcao);
        
        
        switch(opcao){
        case 1:
            if(fila.prim == NULL){
                opcao_arquivo(nome);
                preencher_e_inserir(nome, &fila);
                printf("\nLISTA PREENCHIDA COM SUCESSO!\n"); 
            }   
            else
                printf("\nERRO! LISTA JA FOI PREENCHIDA!");
        break;

        case 2:
            imprimir_fila(&fila);
        break;

        default:
            if(opcao != 0)
                printf("\nOpcao invalida!");
        }
    }while(opcao != 0);

    return 0;
}


void criar_fila(Fila *fila){
    fila->prim = NULL;
    fila->fim = NULL;
    fila->tam = 0;
}

void preencher_e_inserir(char f[], Fila *fila){

    char copia_linha[50];
    char linhaCompleta[50];
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
                fila->tam++;
            }
            else
                printf("\nNao foi possivel alocar memoria!");
        }
        fclose(arquivo);
    }
    else
        printf("\nERRO ao abrir o arquivo!");
}

void imprimir_pessoa(Pessoa p){
    printf("\nNome: %s\nRg: %s\n", p.nome, p.rg);
}

void imprimir_fila(Fila *fila){
    No *aux = fila->prim;
    printf("\n-------------------Fila-----------\n\t");
    while(aux){
        imprimir_pessoa(aux->p);
        aux = aux->proximo;
    }
    printf("\n\t-------------------Fim Fila-----------\n");

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
        if(opcao_arq < 'a' || opcao_arq > 103);
            printf("Opcao invalida!");
    break;
    }
}