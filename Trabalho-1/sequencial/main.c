#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int c_n, m_n;
char opcao2;
char opcao_arq;
int fim = 0;

time_t tIni, tFim;

typedef struct{
    char nome[17];
    char rg[9];
} Pessoa;

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

void imprimir_pessoa(Pessoa p){
    printf("\nNome: %s\nRg: %s\n", p.nome, p.rg);
}

void informacoes(Pessoa pessoa, int cn, int mn){
    c_n = 0; m_n = 0;
    imprimir_pessoa(pessoa);
    cn_mn(cn, mn); 
}

void inserir_inicio(Pessoa vetor[], int tam){// I
    Pessoa pessoa, aux, aux2;
    int i = 0;
    nome_e_rg(&pessoa);
    tIni = time(NULL);

    if(i < tam){
        fim++;
        aux = vetor[i];
        while(i <= fim){ 
            aux2 = vetor[i + 1];
            vetor[i + 1] = aux;
            aux = aux2;
            i++;
            c_n++;
            m_n += 3;
        }
        vetor[0] = pessoa;
    }
    m_n++;
    //ignore this
    tFim = time(NULL);
    informacoes(pessoa, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void inserir_fim(Pessoa vetor[], int tam){// II
    Pessoa pessoa;

    nome_e_rg(&pessoa);
    tIni = time(NULL);
    if(fim < tam){
        vetor[fim] = pessoa;
        fim++;
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

void inserir_posicao_n(Pessoa vetor[], int tam){// III
    Pessoa pessoa, aux, aux2;
    int n, i;
    nome_e_rg(&pessoa);
    printf("\nQual posicao deseja inserir? \n");
    scanf("%d", &n);
    tIni = time(NULL);
    i = n;
    if(fim < tam){   
        fim++;    
        aux = vetor[i - 1];
        while(i < fim){
            aux2 = vetor[i];
            vetor[i] = aux;
            aux = aux2;
            i++;
            c_n++;
            m_n+= 3;
        }
        vetor[n - 1] = pessoa;
        m_n+= 2;
    }
    else
        printf("\nFila cheia!\n");
    //ignore this
    tFim = time(NULL);
    informacoes(pessoa, c_n, m_n);
    tempo_exe(tFim, tIni);
}
/*
void retirar_inicio(Fila *f){//IV
    Pessoa removido;
    tIni = time(NULL);
    int i = ini;

    if(i < fim){
        removido = vetor[i];
        ini++;
        tam_fila--;
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
    if(ini < fim){
        removido = vetor[fim -1];
        fim--;
        tam_fila--;
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
    int i = ini, n;

    printf("\nQual posicao deseja retirar? \n");
    scanf("%d", &n);
    n += ini;

    tIni = time(NULL);
    if(ini < fim){
        removido = vetor[n - 1];
        aux = vetor[n + 1];
        prox = vetor[n];
        vetor[n - 1] = prox;
        i = n;
        fim--;
        m_n+= 5;
        while(i < fim){
            vetor[i] = aux;
            i++;
            aux = vetor[i + 1];
            c_n++;
            m_n+= 2;
        }
        tam_fila--;
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

    i = ini;

    getchar();
    printf("\nDigite o RG que esta procurando: ");
    scanf("%d", &rg_int);
    tIni = time(NULL);
    sprintf(rg, "%d", rg_int);

    while(i < fim){
        c_n++;
        if(strcmp(vetor[i].rg, rg) == 0){
        printf("\nPessoa encontrada na %d posicao!\n", i + 1);
        printf("Nome: %s\n\n", vetor[i].nome);
        break;
        }
        i++;
    }
    tFim = time(NULL);
    cn_mn(c_n, m_n);
    tempo_exe(tFim, tIni);
}
*/
void imprimir_fila(Pessoa vetor[]){ //XIII
    printf("\n-------FILA TAM: %d------\n", fim);
    int i = 0;
    tIni = time(NULL);
    while(i < fim){
        printf("\nNome: %s\nRG: %s\n", vetor[i].nome, vetor[i].rg);
        i++;
    }
    printf("\n-----FIM FILA TAM: %d-----\n", fim);
    tFim = time(NULL);

    tempo_exe(tFim, tIni);
}
/*
void salvar_lista_em_arquivo(char nome_lista[], Fila *f){//IX
    FILE *arquivo = fopen(nome_lista, "w");
    int i = ini;

    if(arquivo){
        if(i < fim){
            while(i < fim){
                fprintf(arquivo,"%s,%s\n", vetor[i].nome, vetor[i].rg);
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
*/
void ler_arquivo_e_inserir(char file[], Pessoa vetor[], int tam){ //X
    
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

            if(fim < tam){
                vetor[fim] = pessoa;
                fim++;
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

    
    int tam = tam_arquivo();
    Pessoa vetor[tam];
    char file_name[50] = {};
    char nome_lista[50] = {};
    int opcao;
    

        do
        {        
            menu_opcoes();
            scanf("%d", &opcao);
            system("clear");
            switch (opcao)
            {
            case 1:
                inserir_inicio(vetor, tam);
                break;
            case 2:
                inserir_fim(vetor, tam); 
                break;
            
            case 3:
                inserir_posicao_n(vetor, tam);
                break;
            /*
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
            */
            case 8:
                imprimir_fila(vetor);  
                break;
            /*
            case 9:
                printf("\nQual nome seu arquivo recebera?\n");
                getchar();
                scanf("%50[^\n]", nome_lista);
                salvar_lista_em_arquivo(nome_lista, fila);
                break;
                */
            case 10:
                opcao_arquivo(file_name);
                ler_arquivo_e_inserir(file_name, vetor, tam);
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

    return 0;
}
