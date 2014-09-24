/* 
 * File:   bitIndexSort.c
 * Author: Oscar
 *
 * Created on 19 de septiembre de 2014, 10:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define NUM_ELEM 10
#define MAX 1000  //Poner un número mayor o igual al verdadero máximo del arreglo
#define Bit 32

void pprint(int arr[]) {
    int i;
    for (i=0; i<NUM_ELEM; i++)
        printf("%d ", arr[i]);
    printf("\n");   
}

void bitIndex_sort(int arr[]) {
    
    int maxBidx = MAX/Bit+1;
    unsigned int Bidx[maxBidx];
    int ind=0;
    int off=0;
    int i, j;
    
    for(i=0; i<maxBidx; i++)
       Bidx[i]=0;
    
    for (i=0; i<NUM_ELEM; i++){
        ind = arr[i]/Bit;
        off = arr[i]%Bit;
        Bidx[ind] = Bidx[ind] | (1<<off); 
    }
    
    i=0;
    for (j=0; j<=maxBidx-1; j++){
    //for (j=maxBidx-1; j>-1; j--){
        while (Bidx[j]>0){
            off=(__builtin_ctz(Bidx[j]));
            //off=(Bit-1)-(__builtin_clz(Bidx[j]));
            arr[i] = j*Bit+off;
            Bidx[j] -= (1<<off);
            i++;
        }
    }
    
    printf("Arreglo de índices:\n");
    pprint(Bidx);
}

int main(int argc, char** argv) {
    int arr[NUM_ELEM] = {9, 6, 0, 4, 3, 1, 8, 2, 7, 5};
    
    printf("Arreglo original:\n");
    pprint(arr);
    
    bitIndex_sort(arr);
    
    printf("Arreglo ordenado:\n");
    pprint(arr);
    return (EXIT_SUCCESS);
}
