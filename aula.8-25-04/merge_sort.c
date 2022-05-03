void merge(Pessoa vet[], int inicio, int meio, int fim){ //h) VI.
    int l, r, tam, i, j, k;
    int fimL = 1, fimR = 1;
    Pessoa *temp;
    l = inicio; 
    r = meio+1;
    tam = fim - inicio + 1;
    temp = (Pessoa*) malloc(tam * sizeof(Pessoa));

    if(temp){
        for(i = 0; i < tam;i++){ 
            if(fimL && fimR){
                if(vet[l].rg < vet[r].rg)    //combinando e ordenando
                    temp[i] = vet[l++];
                else
                    temp[i] = vet[r++];
                if(l > meio)                  //verificando flag que indica se o l ou r chegou ao fim do vet
                    fimL = 0;
                if(r > fim)
                    fimR = 0;
            }
            else{ 
                if(fimL)                      //copiando o que sobrou 
                    temp[i] = vet[l++];
                else
                    temp[i] = vet[r++];
            }
        }
        for(j = 0, k = inicio; j < tam; j++, k++){  //copiando do vet auxiliar para o original
            vet[k] = temp[j];
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