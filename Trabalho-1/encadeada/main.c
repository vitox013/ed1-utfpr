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
}Lista;

void cn_mn(int cn, int mn);
void tempo_exe(int tFim, int tIni);
void verificar_enter_rg(Pessoa *rg);
void nome_e_rg(Pessoa *p);
void imprimir_pessoa_removida(No *remover);
void criar_Lista(Lista *lista);
void imprimir_pessoa(Pessoa p);
void informacoes(Pessoa pessoa, int cn, int mn);
void inserir_inicio(Lista *lista);
void inserir_fim(Lista *lista);
void inserir_posicao_n(Lista *lista);
void remover_do_inicio(Lista *lista);
void remover_do_fim(Lista *lista);
void remover_posicao_n(Lista *lista);
void procurar_no(Lista *lista);
void imprimir_Lista(Lista *lista);
void salvar_lista_em_arquivo(char nome_lista[], Lista *lista);
void ler_arquivo_e_inserir(char file[],Lista *lista);
void opcao_arquivo(char *nome);
void menu_opcoes();
void mostrar_menu();

int main(){

    Lista lista; 
    char file_name[50] = {}, nome_lista[50] = {};
    int opcao;

    criar_Lista(&lista);
           
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
            imprimir_Lista(&lista);    
            break;
        case 9:
            printf("\nQual nome seu arquivo recebera?\n");
            getchar();
            scanf("%50[^\n]", nome_lista);
            salvar_lista_em_arquivo(nome_lista, &lista);
            break;
        case 10:
            opcao_arquivo(file_name);
            ler_arquivo_e_inserir(file_name, &lista);
            break;
        case 11:
            break;
        default:
            printf("\nOpcao invalida! Digite novamente!\n");
            break;
        }
        if(opcao != 11){
        mostrar_menu();
        system("clear");
        }
        else
            break;
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
    printf("\nNome: %s\nRg: %s\n", remover->p.nome, remover->p.rg);
}

void criar_Lista(Lista *lista){
    lista->prim = NULL;
    lista->fim = NULL;
    lista->tam = 0;
}

void imprimir_pessoa(Pessoa p){
    printf("\n\n\n\nNome: %s\nRg: %s\n", p.nome, p.rg);
}

void informacoes(Pessoa pessoa, int cn, int mn){
    c_n = 0; m_n = 0;
    imprimir_pessoa(pessoa);
    cn_mn(cn, mn); 
}

void inserir_inicio(Lista *lista){ //I
    time_t tIni, tFim; 
    No *aux, *novo = malloc(sizeof(No));
    Pessoa pessoa;
   
    nome_e_rg(&pessoa);
    tIni = time(NULL);

    novo->p = pessoa;
    novo->proximo = NULL;

    if(novo){
        if(lista->prim == NULL){
            c_n++;
            lista->prim = novo;
            lista->fim = novo;
            m_n += 2;
        }
        else{
            aux = lista->prim;
            lista->prim = novo; 
            lista->prim->proximo = aux;
            m_n += 3;
        }
        lista->tam++;
        m_n+= 2;
        informacoes(pessoa,c_n, m_n);
        tFim = time(NULL);
        tempo_exe(tFim, tIni);
        printf("\n\n1° posicao na lista\n");
    }
    else
        printf("\nErro ao alocar memoria!\n");
}

void inserir_fim(Lista *lista){ // II
    time_t tIni, tFim;
    No *novo = malloc(sizeof(No));
    Pessoa pessoa;

    if(novo){
        nome_e_rg(&pessoa);
        tIni = time(NULL);

        novo->p = pessoa;
        novo->proximo = NULL;
        lista->fim->proximo = novo;
        lista->fim = novo;
        lista->tam++;
        m_n += 4;
        
        informacoes(pessoa,c_n, m_n);
        tFim = time(NULL);
        tempo_exe(tFim, tIni);
        printf("\n%d° posicao na lista!", lista->tam);
    }
    else
        printf("\nErro ao alocar memoria!\n");
}

void inserir_posicao_n(Lista *lista){ //III
    time_t tIni, tFim;
    No *novo = malloc(sizeof(No)), *aux = NULL, *ant, *aux2;
    Pessoa pessoa;
    int i, n;
    
    nome_e_rg(&pessoa);
    printf("\nQual posicao deseja inserir?\n");
    scanf("%d", &n);

    if(novo){
        tIni = time(NULL);
        novo->p = pessoa;
        novo->proximo = NULL;
        if(n == 1){
            aux = lista->prim;
            lista->prim = novo;
            lista->prim->proximo = aux;
            m_n+= 3;
            c_n++;
        }
        else{
            aux = lista->prim;
            for(i = 1; i < n; i++){
                ant = aux;
                aux = aux->proximo;
                m_n+= 2;
                c_n++;
            }
            aux2 = aux;
            ant->proximo = novo;
            novo->proximo = aux2;
            m_n+= 4;
        }
        m_n += 2;
        lista->tam++;
    
    printf("\nNo inserido com sucesso na %d° posicao!\n\n", n);
    }
    else
        printf("\nErro ao alocar memoria!\n");

    informacoes(pessoa,c_n, m_n);
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
    printf("\n\n%d° posicao na lista!", n);
}

void remover_do_inicio(Lista *lista){ //IV 
    time_t tIni, tFim;
    tIni = time(NULL);

    No *remover;

    if(lista->prim){
        remover = lista->prim;
        lista->prim = remover->proximo;
        lista->tam--;
    }
    else
        printf("\nLista VAZIA!\n");

    m_n += 2;
    c_n++;
    imprimir_pessoa_removida(remover);
    cn_mn(c_n, m_n); 
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void remover_do_fim(Lista *lista){ //V 
    time_t tIni, tFim;
    tIni = time(NULL);
    No *remover, *aux = NULL, *ant;
    
    aux = lista->prim;
    remover = lista->fim;
    while(aux->proximo){
        ant = aux;
        aux = aux->proximo;
        m_n+= 2;
        c_n++;
    }
    ant->proximo = NULL;
    lista->fim = ant;
    
    m_n += 4;
    lista->tam--;
        
    imprimir_pessoa_removida(remover);
    
    cn_mn(c_n, m_n); 
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void remover_posicao_n(Lista *lista){ // VI
    time_t tIni, tFim;
    No  *aux = NULL, *remover, *proximo_no = NULL, *ant;
    int i, n;
    printf("\nQual posicao deseja remover?\n");
    scanf("%d", &n);

    tIni = time(NULL);
    
    
    if(lista->prim){
        if(n == 1){
            remover = lista->prim;
            lista->prim = lista->prim->proximo;
            m_n+= 2;
        }
        else{
            aux = lista->prim;
            for(i = 1; i < n; i++){
                ant = aux;
                aux = aux->proximo;
                m_n+= 2;
                c_n++;
            }
            remover = aux;
            proximo_no = aux->proximo;
            ant->proximo = proximo_no;
            m_n+= 4;
        }
        lista->tam--;
    
    imprimir_pessoa_removida(remover);
    }
    else
        printf("\nLista vazia!\n");

    cn_mn(c_n, m_n); 
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void procurar_no(Lista *lista){ //XII
    No *aux = NULL;
    time_t tIni, tFim;

    int rg_int;
    char rg[8];

    getchar();
    printf("\nDigite o RG que esta procurando: ");
    scanf("%d", &rg_int);
    sprintf(rg, "%d", rg_int);
    
    aux = lista->prim;
    m_n++;
    tIni = time(NULL);
    while(aux->proximo){
        c_n++;
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
    c_n++;
    cn_mn(c_n, m_n); 
    tFim = time(NULL);
    tempo_exe(tFim, tIni);
}

void imprimir_Lista(Lista *lista){ //XIII 

    No *aux = lista->prim;
    printf("\n-----------Lista TAM:%d------------\n", lista->tam);
    while(aux){
        printf("Nome: %s\nRg: %s\n\n", aux->p.nome, aux->p.rg);
        aux = aux->proximo;
    }
    printf("\n-----------FIM Lista TAM:%d-----------\n\n", lista->tam);
}

void salvar_lista_em_arquivo(char nome_lista[], Lista *lista){ //IX

    FILE *arquivo = fopen(nome_lista, "w");
    No *aux = lista->prim;

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

void ler_arquivo_e_inserir(char file[],Lista *lista){ // X
    char copia_linha[50];
    char linhaCompleta[50];
    Pessoa pessoa;
    char *rg;
    
    FILE *arquivo = fopen(file, "r");

    if(arquivo){
        while(fgets(linhaCompleta, 50, arquivo)){
            strcpy(copia_linha, linhaCompleta);
            strcpy(pessoa.nome, strtok(linhaCompleta, ","));

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
                if(lista->prim == NULL){
                    lista->prim = novo;
                    lista->fim = novo;
                }    
                else{
                    lista->fim->proximo = novo;
                    lista->fim = novo;
                }
                lista->tam++;
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
