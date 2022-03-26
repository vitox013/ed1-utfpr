#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[20];
    char rg[8];
}Pessoa;

typedef struct no{
    Pessoa p;
    struct no *proximo;
}No;

void ler_arquivo_e_inserir(char fname[], No **lista);

void imprimir(No *no);

void opcao_arquivo(char *nome);

int main(){

    char nome[20] = {"NomeRG10.txt"};
    No *lista = NULL;
    int opcao;

    do{
        printf("\n0 - Sair\n1 - Inserir na lista a partir do arquivo\n2 - Imprimir lista preenchida\n\n");
        scanf("%d", &opcao);


        switch(opcao){
        case 1:
            opcao_arquivo(nome);
            ler_arquivo_e_inserir(nome, &lista);
            printf("\nLista inserida com sucesso!");
        break;

        case 2:
            imprimir(lista);
        break;

        default:
            if(opcao != 0)
                printf("\nOpcao invalida!");
        }
    }while(opcao != 0);

    return 0;
}

void ler_arquivo_e_inserir(char fname[], No **lista){
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

void imprimir(No *no){
    printf("\n\tLista: ");
    while(no){
        printf("\nNome: %s\nRg: %s\n", no->p.nome, no->p.rg);
        no = no->proximo;
    }
    printf("\n\n");
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
