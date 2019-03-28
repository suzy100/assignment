// 2017029752_백승수_12525

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void selec_sort(int* arr, int N, int M);

int main(){
        int N, M;
        scanf("%d %d", &N, &M);
        
        if (N<1 || M>30000) return -1;
        
        int* arr = new int[N];
        
        for (int i=0; i<N; i++) {
                scanf("%d", &arr[i]);
        }
        
        selec_sort(arr, N, M);

        for (int i=0; i<N; i++) {
                printf("%d\n", arr[i]);
        }
        
        delete[] arr;
        return 0;
}
        
        
void selec_sort(int* arr, int N, int M){

        int i, j = 0;
        while (j<M){

            int k = j;

            for (i=j+1; i<N; i++) {
                if (arr[k]>arr[i]) {
                    k = i;
                }
            }

            if (k!=j) {
               int temp = arr[j];
               arr[j] = arr[k];
               arr[k] = temp;
            }

            j++;
        }

}
