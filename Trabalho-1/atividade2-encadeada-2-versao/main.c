#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//variaveis globais
int c_n, m_n;
char opcao2;
//variaveis globais

typedef struct{
    char nome[20];
    char rg[9];
}Pessoa;

typedef struct no
{
    Pessoa p;
    struct no *proximo;
}No;

void cn_mn(int cn, int mn);
void tempo_exe(int tFim, int tIni);
void verificar_enter_rg(Pessoa *rg);
void nome_e_rg(Pessoa *p);
void imprimir_pessoa_removida(No *remover);
void imprimir_pessoa(Pessoa p);
void informacoes(Pessoa pessoa, int cn, int mn);
void inserir_inicio(No **lista);//I
void inserir_fim(No **lista);//II
void inserir_posicao_n(No **lista);//III
void remover_do_inicio(No **lista);//IV
void remover_do_fim(No **lista);//V
void remover_posicao_n(No **lista); //VI
void procurar_no(No **lista);//VII
void imprimir_lista(No *lista);//XIII lista
void salvar_lista_em_arquivo(char nome_lista[],No **lista);//IX
void ler_arquivo_e_inserir(char file[], No **lista); //X
void menu_opcoes();
void mostrar_menu();
void opcao_arquivo(char *nome);

int main(){ //MAIN MAIN MAIN

    No *lista = NULL;
    char file_name[50] = {}, nome_lista[50] = {};
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
        case 9:
            printf("\nQual nome seu arquivo recebera?\n");
            getchar();
            scanf("%50[^\n]", nome_lista);
            salvar_lista_em_arquivo(nome_lista,&lista);
            break;
        case 10:
            opcao_arquivo(file_name);
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

void imprimir_pessoa_removida(No *remover){
    printf("\n----ELEMENTO REMOVIDO----\n");
    printf("Nome: %s\nRg: %s\n", remover->p.nome, remover->p.rg);
}

void imprimir_pessoa(Pessoa p){
    printf("\nNome: %s\nRg: %s\n", p.nome, p.rg);
}

void informacoes(Pessoa pessoa, int cn, int mn){
    c_n = 0; m_n = 0;
    imprimir_pessoa(pessoa);
    cn_mn(cn, mn); 
}

void inserir_inicio(No **lista){//I
    time_t tIni, tFim; //medir tempo exec da funcao
    No *novo = malloc(sizeof(No));
    Pessoa pessoa;
    
    nome_e_rg(&pessoa);
    tIni = time(NULL);
    if (novo){
        c_n++;
        novo->p = pessoa;
        novo->proximo = *lista;
        *lista = novo;
    
    }
    else
        printf("\nErro ao alocar memoria!\n");

    //ignore this
    m_n+= 3;
    informacoes(pessoa, c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void inserir_fim(No **lista){//II
    time_t tIni, tFim; //medir tempo exec da funcao
    No *novo = malloc(sizeof(No)), *aux;
    Pessoa pessoa;

    nome_e_rg(&pessoa);
    tIni = time(NULL);
    if(novo){
        novo->p = pessoa;
        novo->proximo = NULL;
        if(*lista == NULL){
            *lista = novo;
            c_n++;
            m_n++;
        }
        else{
            aux = *lista;
            while(aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;     
            m_n+= 3;
        }
    }
    else
        printf("\nErro ao alocar memoria!\n");
    //ignore this
    m_n+= 2;
    informacoes(pessoa, c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void inserir_posicao_n(No **lista){//III
    time_t tIni, tFim; //medir tempo exec da funcao
    No *aux, *novo = malloc(sizeof(No));
    Pessoa pessoa;
    int i, n;

    nome_e_rg(&pessoa);   
    printf("\nEm qual posicao deseja inserir?\n");
    scanf("%d", &n);

    tIni = time(NULL);

    if(novo){
        novo->p = pessoa;
        if(n == 1){
            novo->p = pessoa;
            novo->proximo = *lista;
            *lista = novo;
            m_n+= 3;
            c_n++;
        }
        else if(*lista == NULL){
            novo->proximo = NULL;
            *lista = novo;
            c_n++;
            m_n+= 2;
        }
        else{
            aux = *lista;
            for(i = 0; i < n - 2; i++)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo = novo;
            m_n+= 4;
        } 
    }
    else
        printf("\nErro ao alocar memoria!\n");
    
    //ignore this
    printf("\nElemento inserido na %d° posicao!", n);
    informacoes(pessoa, c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void remover_do_inicio(No **lista){ //IV lista
    time_t tIni, tFim; //medir tempo exec da funcao
    No *remover = NULL;
    tIni = time(NULL);
    if(*lista){
        remover = *lista;
        *lista = remover->proximo;
        imprimir_pessoa_removida(remover);
        c_n++;
        m_n+= 2;
    }
    else
        printf("\nLISTA VAZIA!\n");
    //ignore this
    cn_mn(c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void remover_do_fim(No **lista){//V
    time_t tIni, tFim; //medir tempo exec da funcao
    No *aux, *ant, *elem_removido;
    tIni = time(NULL);
    if(*lista){
        aux = *lista;
        while(aux->proximo){
            ant = aux;
            aux = aux->proximo;
            m_n += 2;
            c_n++;
        }
        elem_removido = aux;
        ant->proximo = NULL;
        imprimir_pessoa_removida(elem_removido);
        m_n+= 3;
    }
    else
        printf("\nLista vazia!\n");
    //ignore this
    cn_mn(c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void remover_posicao_n(No **lista){ //VI
    time_t tIni, tFim; //medir tempo exec da funcao
    No *aux, *elem_removido, *ant, *prox_no;
    int i, n = 0;

    printf("\nQual posicao deseja remover? \n");
    scanf("%d", &n);
    tIni = time(NULL);

    if((*lista)){
        if(n == 1){
            elem_removido = *lista;
            (*lista) = (*lista)->proximo;
            c_n++;
            m_n+= 2;
        }
        else{
            aux = *lista;
            for(i = 1; i < n;i++){
                ant = aux;
                aux = aux->proximo;
                c_n++;
                m_n+= 2;
            }
            elem_removido = aux;
            prox_no = aux->proximo;
            ant->proximo = prox_no;
            m_n+= 4;
        }
        imprimir_pessoa_removida(elem_removido);
    }
    else
        printf("\nLista vazia!\n");
    
    //ignore this
    cn_mn(c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void procurar_no(No **lista){//VII
    time_t tIni, tFim; //medir tempo exec da funcao
    No *aux;
    int rg_int;
    char rg[8];

    getchar();
    printf("\nDigite o RG(8 digitos) que esta procurando: ");
    scanf("%d", &rg_int);
    sprintf(rg, "%d", rg_int);

    tIni = time(NULL);

    aux = *lista;
    m_n++;
    while(aux->proximo){
        c_n++;
        if(strcmp(aux->p.rg, rg) == 0){
            printf("\nPessoa encontrada!");
            printf("Nome: %s\n\n", aux->p.nome);
            break;
        }
        aux = aux->proximo;
        m_n++;
    }
    if(strcmp(aux->p.rg, rg) != 0)
        printf("\nRG nao encontrado!");

    //ignore this
    cn_mn(c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void imprimir_lista(No *lista){ //XIII lista
    time_t tIni, tFim; //medir tempo exec da funcao
    tIni = time(NULL);

    printf("\n-----------LISTA------------\n");
    while(lista){
        printf("Nome: %s\nRg: %s\n\n", lista->p.nome, lista->p.rg);
        lista = lista->proximo;
    }
    printf("\n-----------FIM LISTA-----------\n");
}

void salvar_lista_em_arquivo(char nome_lista[],No **lista){//IX
    time_t tIni, tFim; //medir tempo exec da funcao
    tIni = time(NULL);
    FILE *arquivo = fopen(nome_lista, "w");
    No *aux;

    if(arquivo){
        aux = *lista;
        while(aux){
            fprintf(arquivo, "%s,%s\n", aux->p.nome, aux->p.rg);
            aux = aux->proximo;
        }
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir o arquivo!\n");
}

void ler_arquivo_e_inserir(char file[], No **lista){ //X
    time_t tIni, tFim; //medir tempo exec da funcao
    tIni = time(NULL);
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
        printf("9 - Salvar a lista em um arquivo\n");
        printf("10 - Ler a lista de um arquivo\n");
        printf("\n11 - Sair\n\n");
}

void mostrar_menu(){
    printf("\n\nMostrar menu de opcoes? S para sim - N para nao(encerrar): ");
    scanf(" %c", &opcao2);
}

void opcao_arquivo(char *nome){

    char opcao_arq;

    printf("\nQual arquivo?\na) NomeRG10.txt\nb) NomeRG50.txt\nc) NomeRG100.txt\nd) NomeRG1K.txt\ne) NomeRG10K.txt\nf) NomeRG1M.txt\ng) NomeRG100M.txt\n\n");
    scanf(" %c", &opcao_arq);

    switch(opcao_arq){
    case 'a':
        strcpy(nome, "/home/vitor/filesED1/NomeRG10.txt");
    break;

    case 'b':
        strcpy(nome, "/home/vitor/filesED1/NomeRG50.txt");
    break;

    case 'c':
        strcpy(nome, "/home/vitor/filesED1/NomeRG100.txt");
    break;

    case 'd':
        strcpy(nome, "/home/vitor/filesED1/NomeRG1K.txt");
    break;

    case 'e':
        strcpy(nome, "/home/vitor/filesED1/NomeRG10K.txt");
    break;

    case 'f':
        strcpy(nome, "/home/vitor/filesED1/NomeRG1M.txt");
    break;

    case 'g':
        strcpy(nome, "/home/vitor/filesED1/NomeRG100M.txt");
    break;

    default:
        if(opcao_arq < 'a' || opcao_arq > 103)
            printf("Opcao invalida!");
    break;
    }
}