// 2017029752_백승수_12525


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX_ELEMENTS 100000

typedef struct {
        int key;
}element;
element heap[MAX_ELEMENTS];
int n = 0;

void Max_Heapify(int i, int s);
void key_modify(int i, element item);
void Insert_heap(element item, int *n);
void Extract_Max(int* extracted, int *cnt, int *n);

int main() {

          int f, command, k1, k2;
          element item;

          int extracted[MAX_ELEMENTS]; 

          f = 1;
          int cnt = 0;

          while(f) {
                  scanf("%d", &command);
                  
                  if (command == 0) {
                          if(cnt >= 1) {
                                  for (int i = 0; i<cnt; i++) {
                                          printf("%d ", extracted[i]);
                                  }
                                  printf("\n");
                          }
                          for (int i = 1; i <= n; i++) {
                                printf("%d ", heap[i].key);
                          }
                          f = 0;
                          return 0;
                  }

                  if (command == 1) {
                          scanf("%d", &k1);
                          item.key = k1;
                          Insert_heap(item, &n);
                  }

                  if (command == 2) {
                          Extract_Max(extracted, &cnt, &n);
                  }

                  if (command == 3) {
                          scanf("%d %d", &k1, &k2);
                          item.key = k2;
                          key_modify(k1, item);
                  }
          }

          return 0;

}

void Extract_Max(int* extracted, int *cnt, int *n) {
        if (*n < 1) return;
        extracted[*cnt] = heap[1].key;
        *cnt += 1;
        heap[1] = heap[*n];
        *n -= 1;
        Max_Heapify(1, *n);
}
 

void Max_Heapify(int i, int s) {

          int l = (i * 2);
          int r = (i * 2) + 1;
          int largest = i;
          element temp;

          if (l <= s && heap[l].key > heap[largest].key) {
                  if(r <= s && heap[l].key == heap[r].key) {
                    largest = r;
                  }
                  else largest = l;
          }

          if (r <= s && heap[r].key > heap[largest].key) {
                    largest = r;
          }

          if (largest != i) {
                    temp = heap[i];
                    heap[i] = heap[largest];
                    heap[largest] = temp;

                    Max_Heapify(largest, s);
          }

}

void key_modify(int i, element item) {
        element temp;
        temp.key = heap[i].key;
        heap[i].key = item.key;
        if(item.key > temp.key) {
                while (i>1 && heap[i/2].key < heap[i].key){
                    temp = heap[i/2];
                    heap[i/2] = heap[i];
                    heap[i] = heap[i/2];
                    i = i/2;
                }
        }
        if(item.key < heap[i].key) {
                Max_Heapify(i, n);
        }

}

void Insert_heap(element item, int *n) {
        *n += 1;
        key_modify(*n, item);
}
