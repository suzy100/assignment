// 2017029752_백승수_12525

#include <iostream>
using namespace std;

void sort(int* arr, int left, int right);
void merge(int* arr, int left, int mid, int right);

int main(){
        int num;
        cin >> num;
        if(num<1 || num>100000) return -1;
        int* arr = new int[num];
	    for(int i=0; i<num; i++) cin >> arr[i];
	    int left = 0, right = num-1;
        sort(arr, left, right);
        for(int i=0; i<num; i++) cout << arr[i] << endl;
        
        return 0;
}

void sort(int* arr, int left, int right){
	if(left<right){
        int mid = (left+right)/2;
		sort(arr, left, mid);
		sort(arr, mid+1, right);
		merge(arr, left, mid, right);
    }
    else return;
}

void merge(int* arr, int left, int mid, int right){
    //값 담아둘 임시배열 생성
    int* temp = new int[right-left+1];
    //left, right, 임시배열 시작점 설정
    int left_s = left, right_s = mid+1, temp_s = left;
    //left, right 비교 후 임시배열에 담기
    while(left<=mid && right_s<=right){
            if(arr[left_s]>=arr[right_s]){
                temp[temp_s] = arr[left_s];
                left_s++;
            }
            else{
                temp[temp_s] = arr[right_s];
                right_s++;
            }
            temp_s++;
    }
    //남은 right 부분 처리
    if(left_s>mid){
        for(int i=right_s; i<=right; i++){
            temp[temp_s] = arr[i];
            temp_s++;
        }
    }
    //남은 left 부분 처리
    else{
        for(int i=left_s; i<=mid; i++){
                temp[temp_s] = arr[i];
                temp_s++;
        }
    }
    //결과값 반환
    for(int i=left; i<=right; i++){
        arr[i] = temp[i];
    }
}


