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

void inserir_inicio(Pessoa vetor[]){// a
    Pessoa pessoa, aux, aux2;
    int i = 0;
    nome_e_rg(&pessoa);
    tIni = time(NULL);

    if(i < fim){
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
    else{
        vetor[i] = pessoa;
        fim++;
    }
    m_n++;
    //ignore this
    tFim = time(NULL);
    informacoes(pessoa, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void inserir_fim(Pessoa vetor[], int tam){// b
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

void inserir_posicao_n(Pessoa vetor[], int tam){// c
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

void retirar_inicio(Pessoa vetor[]){//d
    tIni = time(NULL);
    Pessoa removido;
    int i = 0;

    if(i < fim){
        removido = vetor[i];
        while( i < fim){
            vetor[i] = vetor[i + 1];
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

void retirar_fim(Pessoa vetor[]){//e
    Pessoa removido;
    tIni = time(NULL);
    int i = 0;
    if(i < fim){
        removido = vetor[fim -1];
        fim--;
    }
    else
        printf("\nErro ao retirar do fim, fila vazia!\n");
    tFim = time(NULL);
    printf("\n----ELEMENTO REMOVIDO----\n");
    informacoes(removido, c_n, m_n);
    tempo_exe(tFim, tIni);
}

void retirar_posicao_n(Pessoa vetor[]){//f
    Pessoa removido;
    int n;

    printf("\nQual posicao deseja retirar? \n");
    scanf("%d", &n);
    
    tIni = time(NULL);
    if(n < fim){
        removido = vetor[n - 1];
        while(n < fim){
            vetor[n - 1] = vetor[n];
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

void procurar_rg(Pessoa vetor[]){//g
    int rg, i = 0;

    printf("\nDigite o RG que esta procurando: ");
    scanf("%d", &rg);
    tIni = time(NULL);

    while(i < fim){
        c_n++;
        if(vetor[i].rg == rg){
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

void menu_ordenar(){

    printf("\nQual forma de ordenar? \n");
    printf("1 - Selection Sort\n");
    printf("2 - Insertion-Sort\n");
    printf("3 - Bubble-Sort\n");
    printf("4 - Shell-Sort\n");
    printf("5 - Quick-Sort\n");
    printf("6 - Merge Sort\n\n");
}

void preencher_vetor_ordem(int vet_ordem[]){
    int i = 0;
    for(i; i < fim; i++){
        vet_ordem[i] = i;
    }
} 

void imprimir_vetor_ordem(int vet_ordem[]){
    int j;
    for(j = 0; j < fim; j++){
        printf("%d ", vet_ordem[j]);
    }
    printf("\n");
}

void selection_sort(Pessoa vetor[]){ //h) I. //git checkout 5776755  -- menos eficiente
    tIni = time(NULL);
    int i = 0, j, menor, troca2, vet_ordem[fim];
    Pessoa troca;

    if(i < fim){
        preencher_vetor_ordem(vet_ordem);
        printf("\nOrdem do vetor:\ni= 0 | ");
        imprimir_vetor_ordem(vet_ordem);
        for(i; i < fim - 1; i++){
            menor = i; 
            c_n++; m_n++;
            for(j = i + 1; j < fim; j++){
                c_n++;
                if(vetor[j].rg < vetor[menor].rg){
                   menor = j;
                   c_n++; m_n++;
                }
            }
            if(i != menor){
                troca = vetor[i];
                vetor[i] = vetor[menor];
                vetor[menor] = troca;
                 c_n++; m_n+= 3;

                //vet_ordem 
                troca2 = vet_ordem[i];
                vet_ordem[i] = vet_ordem[menor];
                vet_ordem[menor] = troca2;
                printf("i= %d | ", i + 1); 
                imprimir_vetor_ordem(vet_ordem);
            }
        }
        printf("\nLista ordenada com sucesso!\n");
        cn_mn(c_n, m_n);
        tFim = time(NULL);
        tempo_exe(tFim, tIni);
    }
    else
        printf("\nLista vazia!");
}

void insertion_sort(Pessoa vetor[]){
    tIni = time(NULL);
    Pessoa copia;
    int j, i = 0, vet_ordem[fim];

    if(i < fim){
        preencher_vetor_ordem(vet_ordem);
        printf("\nOrdem do vetor:\ni= 1 |  ");
        imprimir_vetor_ordem(vet_ordem);
        for(i = 1; i < fim; i++){
            copia = vetor[i];
            c_n++; m_n++;
            for(j = i; (j > 0) && (vetor[j - 1].rg > copia.rg); j--){
                vetor[j] = vetor[j - 1];
                vet_ordem[j] = vet_ordem[j - 1];
                c_n++; m_n++; 
            }
            vetor[j] = copia;
            vet_ordem[j] = i;
            printf("i= %d |  ", i + 1);
            imprimir_vetor_ordem(vet_ordem);
            m_n++;
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

void merge(Pessoa vet[], int inicio, int meio, int fim){
    Pessoa *temp;
    int p1, p2, tamanho, i, j, k;
    int fim1 = 1, fim2 = 1;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (Pessoa *) malloc(tamanho * sizeof(Pessoa));

    if(temp){
        for(i = 0; i < tamanho; i++){
            if(fim1 && fim2){
                if(vet[p1].rg < vet[p2].rg)
                    temp[i] = vet[p1++];
                else
                    temp[i] = vet[p2++];
                
                if(p1 > meio) fim1 = 0;
                if(p2 > fim) fim2 = 0;
            }
            else{
                if(fim1)
                    temp[i] = vet[p1++];
                else
                    temp[i] = vet[p2++];
            }
        }
        for(j = 0, k = inicio; j < tamanho; j++, k++)
            vet[k] = temp[j];
    }
    free(temp);
}

void merge_sort(Pessoa vet[], int inicio, int fim){
    int meio;
    if(inicio < fim - 1){
        meio = (inicio + fim)/2;
        merge_sort(vet, inicio, meio);
        merge_sort(vet, meio+1, fim);
        merge(vet, inicio, meio, fim);
    }
}



void imprimir_fila(Pessoa vetor[]){ //i
    printf("\n-------FILA TAM: %d------\n", fim);
    int i = 0;
    tIni = time(NULL);
    while(i < fim){
        printf("\nNome: %s\nRG: %d\n", vetor[i].nome, vetor[i].rg);
        i++;
    }
    printf("\n-----FIM FILA TAM: %d-----\n", fim);
    tFim = time(NULL);

    tempo_exe(tFim, tIni);
}

void salvar_lista_em_arquivo(char nome_lista[], Pessoa vetor[]){//j
    FILE *arquivo = fopen(nome_lista, "w");
    int i = 0;

    if(arquivo){
        if(i < fim){
            while(i < fim){
                fprintf(arquivo,"%s,%d\n", vetor[i].nome, vetor[i].rg);
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

void ler_arquivo_e_inserir(char file[], Pessoa vetor[], int tam){ //k
    
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
    
    printf("\n\na) - Inserir no INICIO\n");
    printf("b) - Inserir um no no FINAL\n");
    printf("c) - Inserir um no na POSICAO N\n");
    printf("d) - Retirar um no do INICIO\n");
    printf("e) - Retirar um no do FIM\n");
    printf("f) - Retirar um no na POSICAO N\n");
    printf("g) - Procurar no por RG\n");
    printf("h) - Ordenar\n");
    printf("i) - Mostrar lista na tela\n");
    printf("j) - Salvar a lista em um arquivo\n");
    printf("k) - Ler a lista de um arquivo\n");
    printf("\nz - Sair\n\n");
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
        if(opcao_arq < 'a' || opcao_arq > 103)
            printf("Opcao invalida!");
    break;
    }
}

int main(){

    int tam = tam_arquivo();
    Pessoa *vetor = (Pessoa *)malloc(tam * sizeof(Pessoa));
    char file_name[50] = {};
    char nome_lista[50] = {};
    int opcao_ord;
    
        do
        {       
            system("clear");
            menu_opcoes();
            scanf(" %c", &opcao);
            getchar();
            system("clear");
            switch (opcao)
            {
            case 'a':
                inserir_inicio(vetor);
                break;
            case 'b':
                inserir_fim(vetor, tam); 
                break;
            
            case 'c':
                inserir_posicao_n(vetor, tam);
                break;
            
            case 'd':
                retirar_inicio(vetor);
                break;
            
            case 'e':
                retirar_fim(vetor);
                break;
            
            case 'f':
                retirar_posicao_n(vetor);
                break;
            
            case 'g':
                procurar_rg(vetor);
                break;

            case 'h':
                menu_ordenar();
                scanf("%d", &opcao_ord);
                system("clear");
                switch (opcao_ord){
                case 1:
                    selection_sort(vetor);
                    break;
                case 2:
                    insertion_sort(vetor);
                    break;
                case 6:
                    merge_sort(vetor, 0, fim-1);
                    break;
                default:
                    printf("\nOpcao invalida!");
                    break;
                }
                break;
            case 'i':
                imprimir_fila(vetor);  
                break;
            
            case 'j':
                printf("\nQual nome seu arquivo recebera?\n");
                getchar();
                scanf("%50[^\n]", nome_lista);
                salvar_lista_em_arquivo(nome_lista, vetor);
                break;
                
            case 'k':
                opcao_arquivo(file_name);
                ler_arquivo_e_inserir(file_name, vetor, tam);
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
    free(vetor);
    return 0;
}
