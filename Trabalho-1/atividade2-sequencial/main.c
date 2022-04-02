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

void nome_e_rg(Pessoa *p){

    printf("\nDigite o nome: ");
    getchar();
    scanf("%20[^\n]",p->nome);
    getchar();
    printf("\nDigite o RG: ");
    scanf("%8[^n]",p->rg);
}

void ler_arquivo_e_inserir(char file[],Fila *fila){ //1) a. Lista sequencial(fila)

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
                printf("\nErro ao alocar memoria\n");
        }
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir arquivo!\n");    
}

void inserir_inicio(Fila *fila){ //I
    No *aux, *novo = malloc(sizeof(No));
    Pessoa pessoa;
    nome_e_rg(&pessoa);

    novo->p = pessoa;
    novo->proximo = NULL;
    aux = fila->prim;
    fila->prim = novo; 
    fila->prim->proximo = aux;
    fila->tam++;
}

void inserir_fim(Fila *fila){ // II
    No *novo = malloc(sizeof(No));
    Pessoa pessoa;

    nome_e_rg(&pessoa);

    novo->p = pessoa;
    novo->proximo = NULL;
    fila->fim->proximo = novo;
    fila->fim = novo;
}

void inserir_posicao_n(Fila *fila){ //III
    No *novo = malloc(sizeof(No)), *aux = NULL;
    Pessoa pessoa;
    int i, n;
    
    nome_e_rg(&pessoa);
    printf("\nQual posicao deseja inserir?\n");
    scanf("%d", &n);

    aux = fila->prim;
    novo->p = pessoa;
    novo->proximo = NULL;
    for(i = 2; i < n; i++)
        aux = aux->proximo;
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    fila->tam++;
    
    printf("\nNo inserido com sucesso na %d° posicao!\n\n", n);
}

void remover_do_inicio(Fila *fila){ //IV 
    No *remover = NULL;

    if(fila->prim){
        remover = fila->prim;
        printf("\n----ELEMENTO REMOVIDO DO INICIO----\n");
        printf("\tNome: %s\n\tRg: %s\n", remover->p.nome, remover->p.rg);
        fila->prim = remover->proximo;
        fila->tam--;
    }
    else
        printf("\nFILA VAZIA!\n");
}

void remover_do_fim(Fila *fila){ //V 
    No *remover = NULL, *aux = NULL;
    int tam = fila->tam -1;
    int i;

    
    aux = fila->prim;
    remover = fila->fim;
    for(i = 1; i < tam; i++)
        aux = aux->proximo;
    aux->proximo = NULL;
    fila->fim = aux;
    fila->tam--;
        
    printf("\n----ELEMENTO REMOVIDO DO FIM----\n");
    printf("\tNome: %s\n\tRg: %s\n", remover->p.nome, remover->p.rg);
    
}

void remover_posicao_n(Fila *fila){ // VI
    No *novo = malloc(sizeof(No)), *aux = NULL, *remover = NULL, *proximo_no = NULL;
    int i, n;
    
    printf("\nQual posicao deseja remover?\n");
    scanf("%d", &n);

    if(n == 1){
        remover_do_inicio(fila);
    }
    else{
        novo->proximo = NULL;
        aux = fila->prim;
        for(i = 2; i < n; i++)
            aux = aux->proximo;
        remover = aux->proximo;
        proximo_no = aux->proximo->proximo;
        aux->proximo = novo->proximo;
        aux->proximo = proximo_no;
        fila->tam--;
    
    printf("\n----ELEMENTO REMOVIDO DA %d POSICAO----\n", n);
    printf("\tNome: %s\n\tRg: %s\n", remover->p.nome, remover->p.rg);
    }
}

void procurar_no(Fila *fila){
    No *aux = NULL;

    int rg_int;
    char rg[8];

    getchar();
    printf("\nDigite o RG que esta procurando: ");
    scanf("%d", &rg_int);

    sprintf(rg, "%d", rg_int);
    
    aux = fila->prim;
    if(strcmp(aux->p.rg, rg) == 0){
        printf("\nPessoa encontrada!\n");
        printf("Nome: %s\n", aux->p.nome);
    }
    else{

        while(aux->proximo){
            aux = aux->proximo;
            if(strcmp(aux->p.rg, rg) == 0){
                printf("\nPessoa encontrada!\n");
                printf("Nome: %s\n\n", aux->p.nome);
                break;
            }
        } 
    }
}

void imprimir_fila(Fila *fila){ //XIII 
    No *aux = fila->prim;
    printf("\n-----------FILA TAM:%d------------\n", fila->tam);
    while(aux){
        printf("Nome: %s\nRg: %s\n\n", aux->p.nome, aux->p.rg);
        aux = aux->proximo;
    }
    printf("\n-----------FIM FILA TAM:%d-----------\n", fila->tam);
}




int main(){

    Fila fila;
    
    char file_name[15] = {"NomeRG10.txt"};
    int opcao;

    criar_fila(&fila);

    ler_arquivo_e_inserir(file_name, &fila);
            
    if(fila.prim)
        printf("\nFila preenchida do arquivo %s com sucesso!\n\n", file_name);
    else
        printf("\nErro ao preencher lista!");
           

    do
    {
        
        printf("1 - Inserir um no no INICIO\n");
        printf("2 - Inserir um no no FINAL\n");
        printf("3 - Inserir um no na POSICAO N\n");
        printf("4 - Retirar um no do INICIO\n");
        printf("5 - Retirar um no do FIM\n");
        printf("6 - Retirar um no na POSICAO N\n");
        printf("7 - Procurar no por RG\n");
        printf("8 - Mostrar lista na tela\n");
        printf("\n11 - Sair\n\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            inserir_inicio(&fila);
            break;
        case 2:
            inserir_fim(&fila);
            break;
        case 3:
            inserir_posicao_n(&fila);
            break;
        case 4:
            remover_do_inicio(&fila); 
            break;
        case 5:
            remover_do_fim(&fila);
            break;    
        case 6:
            remover_posicao_n(&fila);
            break;
        case 7:
            procurar_no(&fila);
            break;
        case 8:
            imprimir_fila(&fila);    
           break;
        default:
            break;
        }
    } while (opcao != 0);
    

    

    return 0;
}
