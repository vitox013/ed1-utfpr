void insertion_sort(Pessoa vet[]){ //h) II.
    Pessoa copia;
    int j, i = 0, k;

    if(i < fim){
        for(i = 1; i < fim; i++){
            copia = vet[i];
            for(j = i; (j > 0) && (vet[j - 1].rg > copia.rg); j--)
                vet[j] = vet[j - 1];
            vet[j] = copia;
        }
    }
    else
        printf("\nNao eh possivel ordenar uma fila vazia!");
}