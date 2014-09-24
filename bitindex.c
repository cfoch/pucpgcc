/* 
 * File:   bitIndexSort.c
 * Author: Oscar
 *
 * Created on 19 de septiembre de 2014, 10:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define NUM_ELEM 130
#define MAX 700  //Poner un número mayor o igual al verdadero máximo del arreglo
#define Bit 32
#include <time.h>
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
    //for (j=maxBidx-1; j>=0; j--){
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
    //int arr[NUM_ELEM] = {3, 6, 0, 4}; //3, 1, 8, 2, 9, 5};
    int arr[NUM_ELEM] = {338, 196, 174, 548, 297, 122, 291, 352, 218, 17, 468, 143, 556, 574, 412, 249, 422, 219, 5, 439, 347, 459, 397, 89, 203, 361, 389, 326, 118, 213, 15, 313, 564, 611, 512, 109, 253, 215, 327, 269, 33, 471, 608, 234, 424, 381, 454, 431, 171, 150, 239, 568, 241, 443, 280, 631, 193, 132, 62, 583, 46, 24, 446, 154, 277, 11, 482, 547, 43, 305, 71, 2, 538, 496, 382, 344, 276, 552, 493, 514, 85, 306, 100, 65, 425, 499, 260, 557, 562, 194, 604, 585, 640, 593, 110, 247, 182, 47, 136, 27, 430, 479, 331, 324, 168, 410, 476, 255, 475, 250, 105, 86, 156, 16, 281, 111, 603, 270, 220, 165, 273, 162, 318, 364, 545, 486, 376, 140, 49, 309}; 
    printf("Arreglo original:\n");
    pprint(arr);
    
    bitIndex_sort(arr);
    
    printf("Arreglo ordenado:\n");
    pprint(arr);

    return (EXIT_SUCCESS);
}
