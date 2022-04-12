#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int c_n, m_n;
char opcao2;
char opcao_arq;
time_t tIni, tFim;

typedef struct{
    char nome[17];
    char rg[9];
} Pessoa;

typedef struct
{
    int fim;
    int ini;
    int tam;
    int tam_fila;
    Pessoa *vetor;
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

Fila* criar_fila(int tamanho){
    Fila* f = (Fila *)malloc(sizeof(Fila));
    f->fim = 0;
    f->ini = 0;
    f->tam = tamanho;
    f->tam_fila = 0;
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

void imprimir_pessoa(Pessoa p){
    printf("\nNome: %s\nRg: %s\n", p.nome, p.rg);
}

void informacoes(Pessoa pessoa, int cn, int mn){
    c_n = 0; m_n = 0;
    imprimir_pessoa(pessoa);
    cn_mn(cn, mn); 
}

void inserir_inicio(Fila *f){// I
    Pessoa pessoa, aux, ant;
    int i = f->ini;
    nome_e_rg(&pessoa);
    tIni = time(NULL);
    if(i < f->tam){
        aux = f->vetor[i];
        f->vetor[i] = pessoa;
        i++;
        ant = f->vetor[i];
        f->vetor[i] = aux;
        i++;
        f->fim++;
        m_n+= 4;
        while(i <= f->fim){
            aux = ant;
            ant = f->vetor[i];
            f->vetor[i] = aux;
            i++;
            c_n++;
            m_n+= 3;
        }
        f->tam_fila++;
    }
    //ignore this
    tFim = time(NULL);
    informacoes(pessoa, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void inserir_fim(Fila *f){// II
    Pessoa pessoa;

    nome_e_rg(&pessoa);
    tIni = time(NULL);
    if(f->fim < f->tam){
        f->vetor[f->fim] = pessoa;
        f->fim++;
        f->tam_fila++;
        c_n++;
        m_n++;
    }
    else
        printf("\nFila cheia!\n");
    //ignore this
    tFim = time(NULL);
    informacoes(pessoa, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void inserir_posicao_n(Fila *f){// III
    Pessoa pessoa, aux, prox;
    int i = f->ini, n;
    nome_e_rg(&pessoa);
    printf("\nQual posicao deseja inserir? \n");
    scanf("%d", &n);
    tIni = time(NULL);
    n += f->ini;

    if(f->fim < f->tam){       
        aux = f->vetor[n - 1];
        f->vetor[n - 1] = pessoa;
        f->fim++;
        prox = f->vetor[n];
        f->vetor[n] = aux;
        i = n +1;
        m_n+= 4;
        while(i < f->fim){
            aux = prox;
            prox = f->vetor[i];
            f->vetor[i] = aux;
            i++;
            c_n++;
            m_n+= 3;
        }
        f->tam_fila++;
    }
    else
        printf("\nFila cheia!\n");
    //ignore this
    tFim = time(NULL);
    informacoes(pessoa, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void retirar_inicio(Fila *f){//IV
    Pessoa removido;
    tIni = time(NULL);
    int i = f->ini;

    if(i < f->fim){
        removido = f->vetor[i];
        f->ini++;
        f->tam_fila--;
        m_n++;
    }else
        printf("\nFila vazia!\n");
    //ignore this
    tFim = time(NULL);
    printf("\n----ELEMENTO REMOVIDO----\n");
    informacoes(removido, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void retirar_fim(Fila *f){//V
    Pessoa removido;
    tIni = time(NULL);
    if(f->ini < f->fim){
        removido = f->vetor[f->fim -1];
        f->fim--;
        f->tam_fila--;
        m_n++;
    }
    else
        printf("\nErro ao retirar do fim, fila vazia!\n");
    tFim = time(NULL);
    printf("\n----ELEMENTO REMOVIDO----\n");
    informacoes(removido, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void retirar_posicao_n(Fila *f){//VI
    Pessoa removido, aux, prox;
    int i = f->ini, n;

    printf("\nQual posicao deseja retirar? \n");
    scanf("%d", &n);
    n += f->ini;

    tIni = time(NULL);
    if(f->ini < f->fim){
        removido = f->vetor[n - 1];
        aux = f->vetor[n + 1];
        prox = f->vetor[n];
        f->vetor[n - 1] = prox;
        i = n;
        f->fim--;
        m_n+= 5;
        while(i < f->fim){
            f->vetor[i] = aux;
            i++;
            aux = f->vetor[i + 1];
            c_n++;
            m_n+= 2;
        }
        f->tam_fila--;
    }
    else
        printf("\nErro ao retirar, Fila vazia!\n");
    tFim = time(NULL);
    printf("\n----ELEMENTO REMOVIDO----\n");
    informacoes(removido, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void procurar_rg(Fila *f){//XII
    int rg_int, i;
    char rg[8];

    i = f->ini;

    getchar();
    printf("\nDigite o RG que esta procurando: ");
    scanf("%d", &rg_int);
    tIni = time(NULL);
    sprintf(rg, "%d", rg_int);

    while(i < f->fim){
        c_n++;
        if(strcmp(f->vetor[i].rg, rg) == 0){
        printf("\nPessoa encontrada na %d posicao!\n", i + 1);
        printf("Nome: %s\n\n", f->vetor[i].nome);
        break;
        }
        i++;
    }
    tFim = time(NULL);
    cn_mn(c_n, m_n);
    tempo_exe(tFim, tIni);
}

void imprimir_fila(Fila *f){ //XIII
    printf("\n-------FILA TAM: %d------\n", f->tam_fila);
    int i = f->ini;
    tIni = time(NULL);
    while(i < f->fim){
        printf("\nNome: %s\nRG: %s\n", f->vetor[i].nome, f->vetor[i].rg);
        i++;
    }
    printf("\n-----FIM FILA TAM: %d-----\n", f->tam_fila);
    tFim = time(NULL);

    tempo_exe(tFim, tIni);
}

void salvar_lista_em_arquivo(char nome_lista[], Fila *f){//IX
    FILE *arquivo = fopen(nome_lista, "w");
    int i = f->ini;

    if(arquivo){
        if(i < f->fim){
            while(i < f->fim){
                fprintf(arquivo,"%s,%s\n", f->vetor[i].nome, f->vetor[i].rg);
                i++;
            }
        }
        else
            printf("\nFila vazia, erro ao salvar na lista!\n");
    fclose(arquivo);
    }
    else
        printf("\nErro ao abrir o arquivo!\n");
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
                (f->tam_fila)++;
            }
            else
                printf("\nFila cheia!\n");
        }
        printf("\nLista lida com sucesso!\n");
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

int tam_arquivo(){

    printf("\nQual arquivo voce vai utilizar?\na) NomeRG10.txt\nb) NomeRG50.txt\nc) NomeRG100.txt\nd) NomeRG1K.txt\ne) NomeRG10K.txt\nf) NomeRG1M.txt\ng) NomeRG100M.txt\n\n");
    scanf(" %c", &opcao_arq);

    switch(opcao_arq){
    case 'a':
        return 30;
    break;
    case 'b':
        return 80;
    break;

    case 'c':
        return 130;
    break;

    case 'd':
        return 1030;
    break;

    case 'e':
        return 10030;
    break;

    case 'f':
        return 1000030;
    break;

    case 'g':
        return 13000030;
    break;

    default:
        if(opcao_arq < 'a' || opcao_arq > 103)
            printf("Opcao invalida!");
    break;
    }
}


int main(){

    
    int tamanho = tam_arquivo();
    Fila *fila = criar_fila(tamanho);
    char file_name[50] = {};
    char nome_lista[50] = {};
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
                retirar_fim(fila);
                break;    
            case 6:
                retirar_posicao_n(fila);
                break;
            case 7:
                procurar_rg(fila);
                break;
            case 8:
                imprimir_fila(fila);  
                break;
            case 9:
                printf("\nQual nome seu arquivo recebera?\n");
                getchar();
                scanf("%50[^\n]", nome_lista);
                salvar_lista_em_arquivo(nome_lista, fila);
                break;
            case 10:
                opcao_arquivo(file_name);
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
