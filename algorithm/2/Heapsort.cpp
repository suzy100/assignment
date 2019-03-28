// 2017029752_백승수_12525


#define _CRT_SECURE_NO_WARNINGS

 

#include <stdio.h>

 

void Build_Max_Heap(int* arr, int N);

void Max_Heapify(int* arr, int i, int s);

void heapSort(int* arr, int N, int k);

 

int main() {

          int N, k;

 

          scanf("%d %d", &N, &k);

 

          if (N<1 || N>100000 || k<1 || k>30) return -1;

 

          int* arr = new int[N];

 

          for (int i = 0; i<N; i++) {

                    scanf("%d", &arr[i]);

          }

 

          heapSort(arr, N, k);

 

          for (int i = N-1; i > N - k; i--) {

                    printf("%d ", arr[i]);

          }

 

          printf("%d\n", arr[N - k]);

 

          for (int i = 0; i <= N - k - 1; i++) {

                    printf("%d ", arr[i]);

          }

 

          return 0;

 

}

 

void Max_Heapify(int* arr, int i, int s) {

 

          int l = (i * 2) + 1;

          int r = (i * 2) + 2;

          int largest = i;

          int temp;

 

          if (l < s && arr[l] > arr[i]) {

                    largest = l;

                   

          }

 

          if (r < s && arr[r] > arr[largest] && r > l) {

                    largest = r;

                   

          }

 

          if (largest != i) {

                    temp = arr[i];

                    arr[i] = arr[largest];

                    arr[largest] = temp;

                   

                    Max_Heapify(arr, largest, s);

          }

}

 

void Build_Max_Heap(int* arr, int N) {

 

          for (int i = ((N+1)/2)-1; i > -1; i--) {

                    Max_Heapify(arr, i, N);

          }

 

}

 

 

void heapSort(int* arr, int N, int k) {

 

          int temp;

          int H_size = N;

 

          Build_Max_Heap(arr, N);

 

          for (int i = N - 1; i > N - k - 1; i--) {

                    temp = arr[0];

                    arr[0] = arr[i];

                    arr[i] = temp;

                    H_size -= 1;

                    Max_Heapify(arr, 0, H_size);

          }

 

}
