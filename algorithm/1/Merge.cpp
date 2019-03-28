// 2017029752_백승수_12525

#include <iostream>

using std::cin;
using std::cout;
void merge_sort(int a[], int l, int r);
void merge(int a[], int l, int m, int r);

#define MAX_N 100000

int a[MAX_N], b[MAX_N];

int main() {

    int num;
    cin >> num;

    for (int i = 0; i < num; i++) {
        cin >> a[i];
    }

    merge_sort(a, 0, num - 1);

    for (int i = 0; i < num; i++) {
        cout << a[i] << '\n';
    }
    return 0;

}

 

void merge_sort(int a[], int l, int r) {

    if (l < r) {

        int m = (l + r) / 2;

        merge_sort(a, l, m);

        merge_sort(a, m + 1, r);

       

        merge(a, l, m, r);

    }

}

 

void merge(int arr[], int l, int m, int r) {

    int i = l, j = m + 1, k = 0;

   

    while (i <= m && j <= r) {

        if (a[i] >= a[j]) {

            b[k++] = a[i++];

        } else {

            b[k++] = a[j++];

        }

    }

    while (i <= m) {

        b[k++] = a[i++];

    }

    while (j <= r) {

        b[k++] = a[j++];

    }

    --k;

    while (k >= 0) {

        a[l + k] = b[k];

        --k;

    }

}
