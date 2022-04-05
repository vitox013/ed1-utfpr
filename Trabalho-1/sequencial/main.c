#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char opcao2;

typedef struct{
    char nome[17];
    char rg[9];
} Pessoa;

typedef struct
{
    int fim;
    int ini;
    int tam;
    Pessoa *vetor;
}Fila;

void verificar_enter_rg(Pessoa *rg){
    int i;
    
    for(i = 0; i < 9;i++){
        if((*rg).rg[i] == '\n')
            (*rg).rg[i] = '\0';
    }
}

Fila* criar_fila(int tamanho){
    Fila* f = (Fila *)malloc(sizeof(Fila));
    f->fim = 0;
    f->ini = 0;
    f->tam = tamanho;
    f->vetor = (Pessoa *)malloc(tamanho * sizeof(Pessoa));
    return f;
}

void destruir_fila(Fila *f){
    free(f->vetor);
    free(f);
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

void imprimir_pessoa_removida(Pessoa *removido){
    printf("\n----ELEMENTO REMOVIDO----\n");
    printf("Nome: %s\nRg: %s\n", removido->nome, removido->rg);
}

void inserir_inicio(Fila *f){// I
    Pessoa pessoa, aux, ant;
    int i = f->ini;
    nome_e_rg(&pessoa);
    if(i < f->tam){
        aux = f->vetor[i];
        f->vetor[i] = pessoa;
        i++;
        ant = f->vetor[i];
        f->vetor[i] = aux;
        i++;
        f->fim++;
        while(i <= f->fim){
            aux = ant;
            ant = f->vetor[i];
            f->vetor[i] = aux;
            i++;
        }
    }
}

void inserir_fim(Fila *f){// II
    Pessoa pessoa;

    nome_e_rg(&pessoa);

    if(f->fim < f->tam){
        f->vetor[f->fim] = pessoa;
        f->fim++;
    }
    else
        printf("\nFila cheia!\n");
}

void inserir_posicao_n(Fila *f){// III
    Pessoa pessoa, aux, prox;
    int i = f->ini, n;
    nome_e_rg(&pessoa);
    printf("\nQual posicao deseja inserir? \n");
    scanf("%d", &n);
    n += f->ini;
    if(f->fim < f->tam){
        
        aux = f->vetor[n - 1];
        f->vetor[n - 1] = pessoa;
        f->fim++;
        prox = f->vetor[n];
        f->vetor[n] = aux;
        i = n +1;
        while(i < f->fim){
            aux = prox;
            prox = f->vetor[i];
            f->vetor[i] = aux;
            i++;
        }
    }
    else
        printf("\nFila cheia!\n");
}

void retirar_inicio(Fila *f){//IV
    Pessoa removido;
    int i = f->ini;

    if(i < f->fim){
        removido = f->vetor[i];
        imprimir_pessoa_removida(&removido);
        f->ini++;
    }else
        printf("\nFila vazia!\n");
}

void imprimir_fila(Fila *f){ //XIII
    printf("\n-------FILA------\n");
    int i = f->ini;
    while(i < f->fim){
        printf("\nNome: %s\nRG: %s\n", f->vetor[i].nome, f->vetor[i].rg);
        i++;
    }
    printf("\n-----FIM FILA-----\n");
}

void ler_arquivo_e_inserir(char file[], Fila *f){ //X
    
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

            if(f->fim < f->tam){
                f->vetor[f->fim] = pessoa;
                (f->fim)++;
            }
            else
                printf("\nFila cheia!\n");
        }
        fclose(arquivo);
    }
    else
        printf("\nERRO AO ABRIR O ARQUIVO!\n");
}



void menu_opcoes(){
    
        printf("\n\n1 - Inserir no INICIO\n");
        printf("2 - Inserir um no no FINAL\n");
        printf("3 - Inserir um no na POSICAO N\n");
        printf("4 - Retirar um no do INICIO\n");
        //printf("5 - Retirar um no do FIM\n");
       // printf("6 - Retirar um no na POSICAO N\n");
        //printf("7 - Procurar no por RG\n");
        printf("8 - Mostrar lista na tela\n");
       // printf("9 - Salvar a lista em um arquivo\n");
        printf("10 - Ler a lista de um arquivo\n");
        printf("\n11 - Sair\n\n");
}

void mostrar_menu(){
    printf("\n\nMostrar menu de opcoes? S para sim - N para nao(encerrar): ");
    scanf(" %c", &opcao2);
}

int main(){

    
    int tamanho = 30;
    Fila *fila = criar_fila(tamanho);
    char file_name[50] = {"/home/vitor/filesED1/NomeRG10.txt"};
    int opcao;
    

    if(fila){
        do
        {        
            menu_opcoes();
            scanf("%d", &opcao);
            system("clear");
            switch (opcao)
            {
            case 1:
                inserir_inicio(fila);
                break;
            case 2:
                inserir_fim(fila); 
                break;
            case 3:
                inserir_posicao_n(fila);
                break;
            case 4:
                retirar_inicio(fila);
                break;
            case 5:
                //remover_do_fim(fila);
                break;    
            case 6:
            // remover_posicao_n(fila);
                break;
            case 7:
                //procurar_no(fila);
                break;
            case 8:
                imprimir_fila(fila);  
                break;
            case 9:
                //printf("\nQual nome seu arquivo recebera?\n");
                //getchar();
                //scanf("%50[^\n]", nome_lista);
                //salvar_lista_em_arquivo(nome_lista, &fila);
                break;
            case 10:
                ler_arquivo_e_inserir(file_name, fila);
                break;
            case 11:
                exit(0);
            default:
                printf("\nOpcao invalida! Digite novamente!\n");
                break;
            }
            mostrar_menu();
            system("clear");
        } while (opcao2 != 'n' && opcao2 != 'N');
    }
    else
        printf("\nErro ao alocar memoria!\n");
    destruir_fila(fila);

    return 0;
}
