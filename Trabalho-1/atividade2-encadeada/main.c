#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int c_n, m_n;

char opcao2;

typedef struct{
    char nome[20];
    char rg[9];
}Pessoa;

typedef struct no
{
    Pessoa p;
    struct no *proximo;
}No;

void verificar_enter_rg(Pessoa *rg){
    int i;
    
    for(i = 0; i < 9;i++){
        if((*rg).rg[i] == '\n')
            (*rg).rg[i] = '\0';
    }
}

void nome_e_rg(Pessoa *p){

    printf("\nDigite o nome: ");
    getchar();
    scanf("%20[^\n]",p->nome);
    getchar();
    printf("\nDigite o RG (8 digitos): ");
    scanf("%8[^\n]",p->rg);
    getchar();
}

void imprimir_pessoa_removida(No *remover){
    printf("\n----ELEMENTO REMOVIDO----\n");
    printf("Nome: %s\nRg: %s\n", remover->p.nome, remover->p.rg);
}

void inserir_inicio(No **lista){//I
    No *novo = malloc(sizeof(No));
    Pessoa pessoa;
    
    nome_e_rg(&pessoa);

    if (novo){
        novo->p = pessoa;
        novo->proximo = *lista;
        *lista = novo;
    
    }
    else
        printf("\nErro ao alocar memoria!\n");
}

void inserir_fim(No **lista){//II
    No *novo = malloc(sizeof(No)), *aux;
    Pessoa pessoa;

    nome_e_rg(&pessoa);

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
        printf("\nErro ao alocar memoria!\n");
}

void inserir_posicao_n(No **lista){//III
    No *aux, *novo = malloc(sizeof(No));
    Pessoa pessoa;
    int i, n;

    nome_e_rg(&pessoa);
    printf("\nEm qual posicao deseja inserir?\n");
    scanf("%d", &n);

    if(novo){
        novo->p = pessoa;
        if(n == 1){
            novo->p = pessoa;
            novo->proximo = *lista;
            *lista = novo;
        }
        else if(*lista == NULL){
            novo->proximo = NULL;
            *lista = novo;
        }
        else{
            aux = *lista;
            for(i = 0; i < n - 2; i++)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        } 
    }
    else
        printf("\nErro ao alocar memoria!\n");

}

void remover_do_inicio(No **lista){ //IV lista
    No *remover = NULL;

    if(*lista){
        remover = *lista;
        *lista = remover->proximo;
        imprimir_pessoa_removida(remover);
    }
    else
        printf("\nLISTA VAZIA!\n");
}

void remover_do_fim(No **lista){//V
    No *aux, *ant, *elem_removido;

    if(*lista){
        aux = *lista;
        while(aux->proximo){
            ant = aux;
            aux = aux->proximo;
        }
        elem_removido = aux;
        ant->proximo = NULL;
        imprimir_pessoa_removida(elem_removido);
    }
    else
        printf("\nLista vazia!\n");
}

void remover_posicao_n(No **lista){ //VI
    No *aux, *elem_removido, *ant, *prox_no;
    int i, n = 0;

    printf("\nQual posicao deseja remover? \n");
    scanf("%d", &n);
    if((*lista)){
        if(n == 1){
            elem_removido = *lista;
            (*lista) = (*lista)->proximo;
        }
        else{
            aux = *lista;
            for(i = 1; i < n;i++){
                ant = aux;
                aux = aux->proximo;
            }
            elem_removido = aux;
            prox_no = aux->proximo;
            ant->proximo = prox_no;
        }
        imprimir_pessoa_removida(elem_removido);
    }
    else
        printf("\nLista vazia!\n");
}

void procurar_no(No **lista){//VII
    No *aux;
    int rg_int;
    char rg[8];

    getchar();
    printf("\nDigite o RG(8 digitos) que esta procurando: ");
    scanf("%d", &rg_int);
    sprintf(rg, "%d", rg_int);

    aux = *lista;

    while(aux->proximo){
        if(strcmp(aux->p.rg, rg) == 0){
            printf("\nPessoa encontrada!\n");
            printf("Nome: %s\n\n", aux->p.nome);
            break;
        }
        aux = aux->proximo;
        m_n++;
    }
    if(strcmp(aux->p.rg, rg) != 0)
        printf("\nRG nao encontrado!\n");
}

void imprimir_lista(No *lista){ //XIII lista
    printf("\n-----------LISTA------------\n");
    while(lista){
        printf("Nome: %s\nRg: %s\n\n", lista->p.nome, lista->p.rg);
        lista = lista->proximo;
    }
    printf("\n-----------FIM LISTA-----------\n");
}

void ler_arquivo_e_inserir(char file[], No **lista){ //X
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

            verificar_enter_rg(&pessoa);

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
        printf("\nLista lida com sucesso!\n");
    }
    else
        printf("\nERRO AO ABRIR O ARQUIVO!\n");


}

void menu_opcoes(){
    
        printf("\n\n1 - Inserir um no no INICIO\n");
        printf("2 - Inserir um no no FINAL\n");
        printf("3 - Inserir um no na POSICAO N\n");
        printf("4 - Retirar um no do INICIO\n");
        printf("5 - Retirar um no do FIM\n");
        printf("6 - Retirar um no na POSICAO N\n");
        printf("7 - Procurar no por RG\n");
        printf("8 - Mostrar lista na tela\n");
        //printf("9 - Salvar a lista em um arquivo\n");
        printf("10 - Ler a lista de um arquivo\n");
        printf("\n11 - Sair\n\n");
}

void mostrar_menu(){
    printf("\n\nMostrar menu de opcoes? S para sim - N para nao(encerrar): ");
    scanf(" %c", &opcao2);
}

int main(){

    No *lista = NULL;
    char file_name[15] = {"NomeRG10.txt"};
    int opcao;

    do
    {
        menu_opcoes();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            inserir_inicio(&lista);
            break;
        case 2:
            inserir_fim(&lista);
            break;
        case 3:
            inserir_posicao_n(&lista);
            break;
        case 4:
            remover_do_inicio(&lista);
            break;
        case 5:
            remover_do_fim(&lista);
            break;
        case 6:
            remover_posicao_n(&lista);
            break;
        case 7:
            procurar_no(&lista);
            break;
        case 8:
            imprimir_lista(lista);
            break;
        case 10:
            ler_arquivo_e_inserir(file_name, &lista);
            break;
    
        default:
            printf("\nOpcao invalida! Digite novamente!\n");
            break;
        }
        mostrar_menu();
    } while (opcao != 11 && opcao2 != 'n' && opcao2 != 'N');
    


    return 0;
}