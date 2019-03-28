// 2017029752_백승수_12525

#include <iostream>
using namespace std;

void sort(int num, int* arr);

int main(){
        int num;
        cin >> num;
        if(num<1 || num>30000) return -1;
        int* arr = new int[num];
        sort(num, arr);
        cout << "\n";
        delete[] arr;
        return 0;
}

void sort(int num, int* arr){
        for(int i=0; i<num; i++) cin >> arr[i];
        int key, j;
        for(int i=1; i<num; i++){
                key = arr[i];
                j = i-1;
                while(j>=0 && arr[j]<key){
                        arr[j+1] = arr[j];
                        j = j-1;
                }
                arr[j+1] = key;
        }
        for(int i=0; i<num; i++) cout << arr[i] << "\n";
}
