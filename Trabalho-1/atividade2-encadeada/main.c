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

void ler_arquivo_e_inserir(char file[], No **lista){ //1) b. Lista encadeada(lista)

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

void remover_do_inicio(No **lista){ //IV lista
    No *remover = NULL;

    if(*lista){
        remover = *lista;
        printf("Nome: %s\nRg: %s\n", remover->p.nome, remover->p.rg);
        *lista = remover->proximo;
    }
    else
        printf("\nLISTA VAZIA!\n");
}

void imprimir_lista(No *lista){ //XIII lista
    printf("\n-----------LISTA------------\n");
    while(lista){
        printf("Nome: %s\nRg: %s\n\n", lista->p.nome, lista->p.rg);
        lista = lista->proximo;
    }
    printf("\n-----------FIM LISTA-----------\n");
}

int main(){

    No *lista = NULL;
    char file_name[15] = {"NomeRG10.txt"};
    int opcao;

    do
    {
        printf("\n0 - Sair\n")
        switch (opcao)
        {
        case 1:
            /* code */
            break;
        
        default:
            break;
        }
    } while (opcao != 0);
    


    return 0;
}