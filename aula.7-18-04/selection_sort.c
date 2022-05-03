void selection_sort(Pessoa vet[]){
    int i = 0, j, menor, k;
    Pessoa troca;

    if(i < fim){
        while( i < fim - 1){
            menor = i; 

            for(j = i + 1; j < fim; j++){
                if(vet[j].rg < vet[menor].rg){
                   menor = j;
                }
            }
            troca = vet[i];
            vet[i] = vet[menor];
            vet[menor] = troca;
            i++;
        }
    }
    else
        printf("\nLista vazia!");
}