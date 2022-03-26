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

void criar_fila(Fila *fila){
    fila->prim = NULL;
    fila->fim = NULL;
    fila->tam = 0;
}

void ler_lista(char f[], Pessoa *p){
    FILE *arquivo = fopen(f, "r");
    char copia_linha[50];
    char linhaCompleta[50];
    char *rg;
    int i = 0;

    if(arquivo){
        while(fgets(linhaCompleta, 50, arquivo)){
            strcpy(copia_linha, linhaCompleta);
            strcpy(p[i].nome, strtok(linhaCompleta, ",") );

            rg = strtok(copia_linha, ",");
            while(rg){
                strcpy(p[i].rg, rg);
                rg = strtok(NULL, ",");
            }
        i++;
        }
        printf("\n----LISTA LIDA COM SUCESSO!----\n");
        fclose(arquivo);
    }
    else
        printf("\nERRO ao abrir o arquivo!");

}

void inserir_na_lista(Fila *fila, Pessoa *p){

    int i;

    for(i = 0; i < 10; i++){
        No *novo = malloc(sizeof(No));
        if(novo){
            novo->p = p[i];
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
    printf("\nLISTA PREENCHIDA COM SUCESSO!\n");
}

No* remover_da_fila(Fila *fila){
    No *remover = NULL;

    if(fila->prim){
        remover = fila->prim;
        fila->prim = remover->proximo;
        fila->tam--;
    }
    else
        printf("\tFila vazia!");
    return remover;
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
    printf("\n-------------------Fim Fila-----------\n");

}

int main(){
    No *remover;
    Pessoa p[10];
    Fila fila;
    int opcao;
    char nome[] = {"NomeRG10.txt"};

    criar_fila(&fila);

    do{
        printf("\n0 - Sair\n1 - Ler lista de um arquivo\n2 - Colocar na lista sequencial\n3 - Imprimir lista preenchida\n4 - Remover elemento da lista\n\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
        case 1:
            ler_lista(nome, p);
            break;
        case 2:
            inserir_na_lista(&fila, p);
            break;
        case 3:
            imprimir_fila(&fila);
            break;
        case 4:
            remover = remover_da_fila(&fila);
            if(remover){
                printf("\nElemento removido com sucesso!\n");
                imprimir_pessoa(remover->p);

                free(remover);
            }
            else{}

            break;

        default:
            if(opcao != 0)
                printf("\nOpcao invalida!");
        }
    }while(opcao != 0);



    return 0;
}