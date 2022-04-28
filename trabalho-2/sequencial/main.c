#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int c_n, m_n;
char opcao_arq;
char opcao;
int fim = 0;


time_t tIni, tFim;

typedef struct{
    char nome[17];
    int rg;
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

void nome_e_rg(Pessoa *p){

    printf("\nDigite o nome: ");
    getchar();
    scanf("%20[^\n]",p->nome);
    getchar();
    printf("\nDigite o RG (8 digitos): ");
    scanf("%d",&p->rg);
}

void imprimir_pessoa(Pessoa p){
    printf("\nNome: %s\nRg: %d\n", p.nome, p.rg);
}

void informacoes(Pessoa pessoa, int cn, int mn){
    c_n = 0; m_n = 0;
    imprimir_pessoa(pessoa);
    cn_mn(cn, mn); 
}

void inserir_inicio(Pessoa vet[]){// a
    Pessoa pessoa, aux, aux2;
    int i = 0;
    nome_e_rg(&pessoa);
    tIni = time(NULL);

    if(i < fim){
        fim++;
        aux = vet[i];
        while(i <= fim){ 
            aux2 = vet[i + 1];
            vet[i + 1] = aux;
            aux = aux2;
            i++;
            c_n++;
            m_n += 3;
        }
        vet[0] = pessoa;
    }
    else{
        vet[i] = pessoa;
        fim++;
    }
    m_n++;
    //ignore this
    tFim = time(NULL);
    informacoes(pessoa, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void inserir_fim(Pessoa vet[], int tam){// b
    Pessoa pessoa;

    nome_e_rg(&pessoa);
    tIni = time(NULL);
    if(fim < tam){
        vet[fim] = pessoa;
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

void inserir_posicao_n(Pessoa vet[], int tam){// c
    Pessoa pessoa, aux, aux2;
    int n, i, j = 0;
    
    if(j < fim){
        nome_e_rg(&pessoa);
        printf("\nQual posicao deseja inserir? \n");
        scanf("%d", &n);
        i = n;
        tIni = time(NULL);
        if(fim < tam){   
            fim++;    
            aux = vet[i - 1];
            while(i < fim){
                aux2 = vet[i];
                vet[i] = aux;
                aux = aux2;
                i++;
                c_n++;
                m_n+= 3;
            }
            vet[n - 1] = pessoa;
            m_n+= 2;
            //ignore this
            tFim = time(NULL);
            informacoes(pessoa, c_n, m_n);
            tempo_exe(tFim, tIni);
        }
        else
            printf("\nFila cheia!\n");
    }
    else
        printf("\nLista vazia");
}

void retirar_inicio(Pessoa vet[]){//d
    tIni = time(NULL);
    Pessoa removido;
    int i = 0;

    if(i < fim){
        removido = vet[i];
        while( i < fim){
            vet[i] = vet[i + 1];
            c_n++;
            m_n++;
            i++;
        }
        fim--;

    //ignore this
    tFim = time(NULL);
    printf("\n----ELEMENTO REMOVIDO----\n");
    informacoes(removido, c_n, m_n);
    tempo_exe(tFim, tIni);
    
    }
    else
        printf("\nFila vazia!\n");
}

void retirar_fim(Pessoa vet[]){//e
    Pessoa removido;
    tIni = time(NULL);
    int i = 0;
    if(i < fim){
        removido = vet[fim -1];
        fim--;
    }
    else
        printf("\nErro ao retirar do fim, fila vazia!\n");
    tFim = time(NULL);
    printf("\n----ELEMENTO REMOVIDO----\n");
    informacoes(removido, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void retirar_posicao_n(Pessoa vet[]){//f
    Pessoa removido;
    int n;

    printf("\nQual posicao deseja retirar? \n");
    scanf("%d", &n);
    
    tIni = time(NULL);
    if(n < fim){
        removido = vet[n - 1];
        while(n < fim){
            vet[n - 1] = vet[n];
            n++;
            c_n++;
            m_n++;
        }
        fim--;
    }
    else
        printf("\nErro ao retirar, Fila vazia!\n");
    tFim = time(NULL);
    printf("\n----ELEMENTO REMOVIDO----\n");
    informacoes(removido, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void procurar_rg(Pessoa vet[]){//g
    int rg, i = 0;

    printf("\nDigite o RG que esta procurando: ");
    scanf("%d", &rg);
    tIni = time(NULL);

    while(i < fim){
        c_n++;
        if(vet[i].rg == rg){
        printf("\nPessoa encontrada na %d posicao!\n", i + 1);
        printf("Nome: %s\n\n", vet[i].nome);
        break;
        }
        i++;
    }
    tFim = time(NULL);
    cn_mn(c_n, m_n);
    tempo_exe(tFim, tIni);
}

void menu_ordenar(){
    printf("\nQual forma de ordenar? \n1 - Selection Sort\n2 - Insertion-Sort\n3 - Bubble-Sort\n4 - Shell-Sort\n5 - Quick-Sort\n6 - Merge Sort\n\n");
}

void selection_sort(Pessoa vet[]){ //h) I. //git checkout 5776755  -- menos eficiente
    tIni = time(NULL);
    int i = 0, j, menor, k;
    Pessoa troca;

    if(i < fim){
        while( i < fim - 1){
            menor = i; 
            c_n++; m_n++;
            for(j = i + 1; j < fim; j++){
                c_n++;
                if(vet[j].rg < vet[menor].rg){
                   menor = j;
                   c_n++; m_n++;
                }
            }
            troca = vet[i];
            vet[i] = vet[menor];
            vet[menor] = troca;
            c_n++; m_n+= 3;  

            //mostrar movimentacao
            for(k = 0; k < fim; k++){
                printf("%s\t", vet[k].nome);
            }
            printf("\n");
            i++;
        }
        printf("\nLista ordenada com sucesso!\n");
        cn_mn(c_n, m_n);
        tFim = time(NULL);
        tempo_exe(tFim, tIni);
    }
    else
        printf("\nLista vazia!");
}

void insertion_sort(Pessoa vet[]){ //h) II.
    tIni = time(NULL);
    Pessoa copia;
    int j, i = 0, k;

    if(i < fim){
        for(i = 1; i < fim; i++){
            copia = vet[i];
            c_n++; m_n++;
            for(j = i; (j > 0) && (vet[j - 1].rg > copia.rg); j--){
                vet[j] = vet[j - 1];
                c_n++; m_n++; 
            }
            vet[j] = copia;
            m_n++;
            for(k = 0; k < fim; k++){
                printf("%s\t", vet[k].nome);
            }
            printf("\n");
        }
        //ignore this
        printf("\nLista ordenada com sucesso!\n\n");
        cn_mn(c_n, m_n);
        tFim = time(NULL);
        tempo_exe(tFim, tIni);
    }
    else
        printf("\nNao eh possivel ordenar uma fila vazia!");
}

void bubble_sort(Pessoa vet[]){ //h) III.
    tIni = time(NULL);
    Pessoa troca;
    int i = 0, j;

    if(i < fim){
        for(i = 0; i < fim - 1; i++){ c_n++;
            for(j = 0; j < fim - 1; j++){ c_n++;
                if(vet[j].rg > vet[j+1].rg){ c_n++; m_n++;
                    troca = vet[j+1];
                    vet[j+1] = vet[j];
                    vet[j] = troca;
                }
            }
        }
        printf("\nLista ordenada com sucesso!\n");
        tFim = time(NULL);
        cn_mn(c_n, m_n);
        tempo_exe(tFim, tIni);
    }
    else
        printf("\nImpossivel ordenar lista vazia!\n");
}

void shell_sort(Pessoa vet[]){ //h) IV.
    tIni = time(NULL);
    int h, i = 0, j;
    Pessoa aux;
    h = (fim - 1) / 2;
    if(i < fim){
        while(h > 0){ c_n++;
            for(i = h; i < fim; i++){ c_n++; m_n+=2;
                aux = vet[i];
                j = i;
                while(j >= h && aux.rg < vet[j - h].rg){ c_n++; m_n+=2;
                    vet[j] = vet[j - h];
                    j = j - h;
                }
                if(vet[j].rg != aux.rg){ c_n++; m_n++;
                    vet[j] = aux;
                }
            }
            h /= 2;
        }
        cn_mn(c_n, m_n);
        tFim = time(NULL);
        tempo_exe(tFim, tIni);
    }
}

void merge(Pessoa vet[], int inicio, int meio, int fim){ //h) VI.
    int l, r, tam, i, j, k;
    int fimL = 1, fimR = 1;
    Pessoa *temp;
    l = inicio; 
    r = meio+1;
    tam = fim - inicio + 1;
    temp = (Pessoa*) malloc(tam * sizeof(Pessoa));

    if(temp){
        c_n++;
        for(i = 0; i < tam;i++){ 
            c_n++; m_n++;
            if(fimL && fimR){
                c_n++;
                if(vet[l].rg < vet[r].rg){    //combinando e ordenando
                    temp[i] = vet[l++];
                    c_n++; m_n++;
                }
                else{
                    temp[i] = vet[r++];
                    c_n++; m_n++;
                }
                if(l > meio){                  //verificando flag que indica se o l ou r chegou ao fim do vet
                    fimL = 0;
                    c_n++; m_n++;
                }
                if(r > fim){
                    fimR = 0;
                    c_n++; m_n++;
                }
            }
            else{
                c_n++;
                if(fimL){                       //copiando o que sobrou 
                    temp[i] = vet[l++];
                    c_n++; m_n++;
                }
                else{
                    temp[i] = vet[r++];
                    c_n++; m_n++;
                }
            }
        }
        for(j = 0, k = inicio; j < tam; j++, k++){  //copiando do vet auxiliar para o original
            vet[k] = temp[j];
            c_n++; m_n++;
        }
        free(temp);
    }
}

void merge_sort(Pessoa vet[], int inicio, int fim){ //h) VI.
    int meio;
    if(inicio < fim){
        meio = (inicio + fim) / 2;
        merge_sort(vet, inicio, meio);
        merge_sort(vet, meio + 1, fim);
        merge(vet, inicio, meio, fim);
    }
}

void imprimir_fila(Pessoa vet[]){ //i
    printf("\n-------FILA TAM: %d------\n", fim);
    int i = 0;
    tIni = time(NULL);
    while(i < fim){
        printf("\nNome: %s\nRG: %d\n", vet[i].nome, vet[i].rg);
        i++;
    }
    printf("\n-----FIM FILA TAM: %d-----\n", fim);
    tFim = time(NULL);

    tempo_exe(tFim, tIni);
}

void salvar_lista_em_arquivo(char nome_lista[], Pessoa vet[]){//j
    FILE *arquivo = fopen(nome_lista, "w");
    int i = 0;

    if(arquivo){
        if(i < fim){
            while(i < fim){
                fprintf(arquivo,"%s,%d\n", vet[i].nome, vet[i].rg);
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

void ler_arquivo_e_inserir(char file[], Pessoa vet[], int tam){ //k
    
    char copia_linha[50];
    char linha_completa[50];
    Pessoa pessoa;
    char *rg;
    char rg2[9];
    FILE *arquivo = fopen(file, "r");

    if(arquivo){
        while(fgets(linha_completa, 50, arquivo)){
            strcpy(copia_linha, linha_completa);
            strcpy(pessoa.nome,strtok(linha_completa, ","));

            rg = strtok(copia_linha, ",");

            while(rg){
                strcpy(rg2, rg);
                rg = strtok(NULL, ",");
            }

            pessoa.rg = strtol(rg2, NULL, 10);

            if(fim < tam){
                vet[fim] = pessoa;
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
    
    printf("\n\na) - Inserir no INICIO\nb) - Inserir um no no FINAL\nc) - Inserir um no na POSICAO N\nd) - Retirar um no do INICIO\ne) - Retirar um no do FIM\nf) - Retirar um no na POSICAO N\ng) - Procurar no por RG\nh) - Ordenar\ni) - Mostrar lista na tela\nj) - Salvar a lista em um arquivo\nk) - Ler a lista de um arquivo\n\nz - Sair\n\n");
}

void mostrar_menu(){
    printf("\n\nMostrar menu de opcoes? S para sim - N para nao(encerrar): ");
    scanf(" %c", &opcao);
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

    while(opcao_arq < 'a' || opcao_arq > 103){
        printf("\nQual arquivo voce vai utilizar?\na) NomeRG10.txt\nb) NomeRG50.txt\nc) NomeRG100.txt\nd) NomeRG1K.txt\ne) NomeRG10K.txt\nf) NomeRG1M.txt\ng) NomeRG100M.txt\n\n");
        scanf(" %c", &opcao_arq);

        switch(opcao_arq){
        case 'a':
            return 30;
        case 'b':
            return 80;
        case 'c':
            return 130;
        case 'd':
            return 1030;
        case 'e':
            return 10030;
        case 'f':
            return 1000030;
        case 'g':
            return 13000030;
        default:
            if(opcao_arq < 'a' || opcao_arq > 103){
                system("clear");
                printf("Opcao invalida!\n");
            }
        break;
        }
    }
}

int main(){

    int tam = tam_arquivo();
    Pessoa *vet = (Pessoa *)malloc(tam * sizeof(Pessoa));
    char file_name[50] = {};
    char nome_lista[50] = {};
    int opcao_ord;
    
        do{       
            system("clear");
            menu_opcoes();
            scanf(" %c", &opcao);
            getchar();
            system("clear");
            switch (opcao)
            {
            case 'a':
                inserir_inicio(vet);
                break;

            case 'b':
                inserir_fim(vet, tam); 
                break;  

            case 'c':
                inserir_posicao_n(vet, tam);
                break;   

            case 'd':
                retirar_inicio(vet);
                break;
            
            case 'e':
                retirar_fim(vet);
                break;
            
            case 'f':
                retirar_posicao_n(vet);
                break;
            
            case 'g':
                procurar_rg(vet);
                break;

            case 'h':
                menu_ordenar();
                scanf("%d", &opcao_ord);
                system("clear");
                switch (opcao_ord){
                case 1:
                    selection_sort(vet);
                    break;

                case 2:
                    insertion_sort(vet);
                    break;
                
                case 3:
                    bubble_sort(vet);
                    break;
                case 4:
                    shell_sort(vet);
                    break;
                case 6:
                    tIni = time(NULL);
                    merge_sort(vet, 0, fim-1);
                    tFim = time(NULL);
                    cn_mn(c_n, m_n);
                    tempo_exe(tFim, tIni);
                    printf("\n\nLista ordenada com sucesso!");
                    break;

                default:
                    printf("\nOpcao invalida!");
                    break;
                }
                break;

            case 'i':
                imprimir_fila(vet);  
                break;
            
            case 'j':
                printf("\nQual nome seu arquivo recebera?\n");
                scanf("%50[^\n]", nome_lista);
                getchar();
                salvar_lista_em_arquivo(nome_lista, vet);
                break;
                
            case 'k':
                opcao_arquivo(file_name);
                ler_arquivo_e_inserir(file_name, vet, tam);
                break;
            case 'z':
                break;
            default:
                printf("\nOpcao invalida! Digite novamente!\n");
                break;
            }
            if(opcao != 'z' && opcao != 'n' && opcao != 'N')
                mostrar_menu(opcao);
            system("clear");
        } while (opcao != 'z' && opcao != 'n' && opcao != 'N');
    free(vet);
    return 0;
}
