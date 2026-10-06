#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void gerarNumeros(int quantidade){

    FILE *arquivo = fopen("dados.txt","w");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo \n");
        return;
    }

    srand(time(NULL));

    for(int i =0; i<quantidade; i++){
        int numero = rand() % 1000000;
        fprintf(arquivo, "%d\n", numero);
    }

    printf("Arquivo gravado com [ %d ] numeros \n", quantidade);
    fclose(arquivo);


}

int *lerNumerosDoArquivo(int quantidade){

    FILE *arquivo = fopen("dados.txt","r");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo \n");
        return NULL;
    }

    int *vetor = (int*) malloc (quantidade*sizeof(int));

    if(vetor == NULL){
        printf("Erro ao alocar vetor \n");
        return NULL;
    }

    for(int i=0; i<quantidade;i++){
        fscanf(arquivo, "%d", &vetor[i]);
    }

    printf("Numeros lidos no arquivo: [ %d ]\n", quantidade);

    fclose(arquivo);
    return vetor;

}

void merge(int *vetor, int inicio, int meio, int fim){

    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *esquerda = (int*) malloc (n1*sizeof(int));
    int *direita = (int*) malloc (n2*sizeof(int));

    for(int i = 0; i< n1; i++){
        esquerda[i] = vetor[inicio + i];
    }

    for(int j = 0; j< n2; j++){
        direita[j] = vetor[meio + 1 + j];
    }

    int i = 0, j =0, k = inicio;

    while(i < n1 && j < n2){
    if(esquerda[i] <= direita[j]){
         vetor[k] = esquerda[i];
        i++;
    } else {
    vetor[k] = direita[j];
    j++;
    }
    k++;
}
     while(i < n1){
        vetor[k] = esquerda[i];
        i++;
        k++;
     }

     while(j < n2){
        vetor[k] = direita[j];
        j++;
        k++;
     }

     free(esquerda);
     free(direita);
}

void salvarNumerosNoArquivo(int *vetor, int quantidade){

    FILE *arquivo = fopen("dados_ordenados.txt", "w");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo \n");
        return;
    }

    for(int i = 0; i< quantidade; i++){
        fprintf(arquivo, "%d\n", vetor[i]);
    }

    printf("Numeros ordenados salvos no arquivo [ %d ]\n", quantidade);

    fclose(arquivo);
}

void mergeSortRecursivo(int *vetor, int inicio, int fim){

    if(inicio < fim){
        int meio = (inicio + fim)/2;

    mergeSortRecursivo(vetor, inicio, meio);
    mergeSortRecursivo(vetor, meio + 1, fim);

    merge(vetor, inicio, meio, fim);
    }

}

time_t mergeSort(int *vetor, int quantidade){

    time_t inicio = time(NULL);

    mergeSortRecursivo(vetor, 0, quantidade - 1);

    time_t fim = time(NULL);

    return fim - inicio;

}

int main(){

    const int quantidade =  1000000;

    system("color 1E");

    printf("Gerando numeros... \n");
    gerarNumeros(quantidade);

    printf("Lendo numeros do arquvo...\n");
    int *vetor = lerNumerosDoArquivo(quantidade);

    if(vetor == NULL){
        printf("Erro no vetor \n");
        return 1;
    }

    printf("Oredenação dos numeros...\n");
    time_t tempo = mergeSort(vetor, quantidade);

    printf("Salvando os numeros ordenados no arquivo...\n");
    salvarNumerosNoArquivo(vetor, quantidade);

    printf("Tempo de execucao: [ %ld ] segundos \n", tempo);

    free(vetor);

    system("pause");

    return 0;


    return 0;
}
