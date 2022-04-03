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

typedef struct{
    No *prim;
    No *fim;
    int tam;
}Fila;

void cn_mn(int cn, int mn){
    c_n = 0, m_n = 0;
    printf("\nC(n): %d\n",cn);
    printf("\nM(n): %d\n",mn);
}

void tempo_exe(int tFim, int tIni){
    float tExecucao;

    tExecucao = difftime(tFim, tIni);

    printf("\nTempo de execucao da funcao: %.2f sec", tExecucao);
}

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

void criar_fila(Fila *fila){
    fila->prim = NULL;
    fila->fim = NULL;
    fila->tam = 0;
}

void imprimir_pessoa(Pessoa p){
    printf("\n\n\n\nNome: %s\nRg: %s\n", p.nome, p.rg);
}

void informacoes(Pessoa pessoa, int cn, int mn){
    c_n = 0; m_n = 0;
    imprimir_pessoa(pessoa);
    cn_mn(cn, mn); 
}

void inserir_inicio(Fila *fila){ //I
    time_t tIni, tFim; 
    No *aux, *novo = malloc(sizeof(No));
    Pessoa pessoa;
   
    nome_e_rg(&pessoa);
    tIni = time(NULL);

    novo->p = pessoa;
    novo->proximo = NULL;

    if(fila->prim == NULL){
        c_n++; //numero de if executados
        fila->prim = novo;
        fila->fim = novo;
        m_n += 2;
    }
    else{
        c_n++; //numero de if executados
        aux = fila->prim;
        fila->prim = novo; 
        fila->prim->proximo = aux;
        m_n += 3; //numero de copias realizadas
    }
    fila->tam++;
    informacoes(pessoa,c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
    printf("\n\n1° posicao na lista\n");
}

void inserir_fim(Fila *fila){ // II
    time_t tIni, tFim;
    No *novo = malloc(sizeof(No));
    Pessoa pessoa;

    nome_e_rg(&pessoa);
    tIni = time(NULL);
    novo->p = pessoa;
    novo->proximo = NULL;
    fila->fim->proximo = novo;
    fila->fim = novo;
    fila->tam++;
    m_n += 4;
    
    informacoes(pessoa,c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
    printf("\n%d° posicao na lista!", fila->tam);
}

void inserir_posicao_n(Fila *fila){ //III
    time_t tIni, tFim;
    No *novo = malloc(sizeof(No)), *aux = NULL;
    Pessoa pessoa;
    int i, n, c_n = 0, m_n = 0;
    
    nome_e_rg(&pessoa);
    printf("\nQual posicao deseja inserir?\n");
    scanf("%d", &n);

    tIni = time(NULL);
    aux = fila->prim;
    novo->p = pessoa;
    novo->proximo = NULL;
    m_n += 3;
    for(i = 2; i < n; i++){
        aux = aux->proximo;
        m_n += 1;
    }
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    m_n += 2;
    fila->tam++;
    
    printf("\nNo inserido com sucesso na %d° posicao!\n\n", n);

    informacoes(pessoa,c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
    printf("\n\n%d° posicao na lista!", n);
}

void remover_do_inicio(Fila *fila){ //IV 
    time_t tIni, tFim;
    tIni = time(NULL);

    No *remover = NULL;
    m_n++;

    if(fila->prim){
        c_n++;
        remover = fila->prim;
        printf("\n----ELEMENTO REMOVIDO DO INICIO----\n");
        printf("\tNome: %s\n\tRg: %s\n", remover->p.nome, remover->p.rg);
        fila->prim = remover->proximo;
        m_n += 2;
        fila->tam--;
    }
    else
        printf("\nFILA VAZIA!\n");

    cn_mn(c_n, m_n); 
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void remover_do_fim(Fila *fila){ //V 
    time_t tIni, tFim;
    tIni = time(NULL);
    No *remover = NULL, *aux = NULL, *ant;
    int tam = fila->tam -1;
    int i;
    
    aux = fila->prim;
    remover = fila->fim;
    while(aux->proximo){
        ant = aux;
        aux = aux->proximo;
        m_n+2;
    }
    ant->proximo = NULL;
    fila->fim = ant;
    
    m_n += 4;
    fila->tam--;
        
    printf("\n----ELEMENTO REMOVIDO DO FIM----\n");
    printf("\tNome: %s\n\tRg: %s\n", remover->p.nome, remover->p.rg);
    
    cn_mn(c_n, m_n); 
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void remover_posicao_n(Fila *fila){ // VI
    time_t tIni, tFim;
    No *novo = malloc(sizeof(No)), *aux = NULL, *remover = NULL, *proximo_no = NULL;
    int i, n;
    printf("\nQual posicao deseja remover?\n");
    scanf("%d", &n);

    tIni = time(NULL);
    if(n == 1){
        remover_do_inicio(fila);
        c_n++;
    }
    else{
        novo->proximo = NULL;
        aux = fila->prim;
        m_n += 2;
        for(i = 2; i < n; i++){
            aux = aux->proximo;
            m_n++;
        }
        remover = aux->proximo;
        m_n++;
        proximo_no = aux->proximo->proximo;
        m_n++;
        aux->proximo = novo->proximo;
        aux->proximo = proximo_no;
        m_n += 2;
        fila->tam--;
    
    printf("\n----ELEMENTO REMOVIDO DA %d POSICAO----\n", n);
    printf("\tNome: %s\n\tRg: %s\n", remover->p.nome, remover->p.rg);
    }

    cn_mn(c_n, m_n); 
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void procurar_no(Fila *fila){ //XII
    No *aux = NULL;
    int rg_int;
    char rg[8];

    getchar();
    printf("\nDigite o RG que esta procurando: ");
    scanf("%d", &rg_int);
    sprintf(rg, "%d", rg_int);
    
    aux = fila->prim;
    m_n++;
    if(strcmp(aux->p.rg, rg) == 0){
        c_n++;
        printf("\nPessoa encontrada!\n");
        printf("Nome: %s\n", aux->p.nome);
    }
    while(aux->proximo){
        c_n++;
        aux = aux->proximo;
        m_n++;
        if(strcmp(aux->p.rg, rg) == 0){
            printf("\nPessoa encontrada!\n");
            printf("Nome: %s\n\n", aux->p.nome);
            break;
        }
    }
    if(strcmp(aux->p.rg, rg) != 0)
        printf("\nRG nao encontrado!\n");
}

void imprimir_fila(Fila *fila){ //XIII 

    No *aux = fila->prim;
    printf("\n-----------FILA TAM:%d------------\n", fila->tam);
    while(aux){
        printf("Nome: %s\nRg: %s\n\n", aux->p.nome, aux->p.rg);
        aux = aux->proximo;
    }
    printf("\n-----------FIM FILA TAM:%d-----------\n\n", fila->tam);
}

void salvar_lista_em_arquivo(char nome_lista[], Fila *fila){ //IX

    FILE *arquivo = fopen(nome_lista, "w");
    No *aux = fila->prim;

    if(arquivo){
        while(aux){
            fprintf(arquivo,"%s,%s\n", aux->p.nome, aux->p.rg);
            aux = aux->proximo;
        }
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir o arquivo!\n\n");
}

void ler_arquivo_e_inserir(char file[],Fila *fila){ // X

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

            verificar_enter_rg(&pessoa);

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
        printf("\nLista lida com sucesso!\n");
    }
    else
        printf("\nErro ao abrir arquivo!\n");
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

void menu_opcoes(){
    
        printf("\n\n1 - Inserir um no no INICIO\n");
        printf("2 - Inserir um no no FINAL\n");
        printf("3 - Inserir um no na POSICAO N\n");
        printf("4 - Retirar um no do INICIO\n");
        printf("5 - Retirar um no do FIM\n");
        printf("6 - Retirar um no na POSICAO N\n");
        printf("7 - Procurar no por RG\n");
        printf("8 - Mostrar lista na tela\n");
        printf("9 - Salvar a lista em um arquivo\n");
        printf("10 - Ler a lista de um arquivo\n");
        printf("\n11 - Sair\n\n");
}

void mostrar_menu(){
    printf("\n\nMostrar menu de opcoes? S para sim - N para nao(encerrar): ");
    scanf(" %c", &opcao2);
}

int main(){

    Fila fila; 
    char file_name[15] = {}, nome_lista[50] = {};
    int opcao;

    criar_fila(&fila);
           
    do
    {        
        menu_opcoes();
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
        case 9:
            printf("\nQual nome seu arquivo recebera?\n");
            getchar();
            scanf("%50[^\n]", nome_lista);
            salvar_lista_em_arquivo(nome_lista, &fila);
            break;
        case 10:
            opcao_arquivo(file_name);
            ler_arquivo_e_inserir(file_name, &fila);
            break;
        default:
            printf("\nOpcao invalida! Digite novamente!\n");
            break;
        }
        mostrar_menu();
    } while (opcao != 11 && opcao2 != 'n' && opcao2 != 'N');

    return 0;
}
