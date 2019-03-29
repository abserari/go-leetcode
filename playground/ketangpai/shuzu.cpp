#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>

using namespace std;

int* getmaxmin(int a, int b){
    int* m = new int[2];
    if(a < b){
        m[0] = a;
        m[1] = b;
    }else{
        m[0] = b;
        m[1] = a;
    }
    return m;
}

int* maxmin(int a[], int n1, int n2){
    if((n2 - n1 + 1)== 1){
        int* m = new int[2];
        m[0] = -1;
        m[1] = a[n2];
        return getmaxmin(a[n2], a[n2]);
    }else if((n2 - n1 + 1) == 2){
        return getmaxmin(a[n1], a[n2]);
    }else{
        int k = n1 + (n2 - n1) / 2;
        int* lm = maxmin(a, n1, k);
        int* rm = maxmin(a, k+1, n2);

       
        int* result = new int[2];
        if(lm[0] < rm[0]){
            result[0] = lm[0];
        }else{
            result[0] = rm[0];
        }
        if(lm[1] < rm[1]){
            result[1] = rm[1];
        }else{
            result[1] = lm[1];
        }
        return result;
    }
}

int main(){
    int a[8] = {6,10,32,8,19,20,2,14};
    int* result = maxmin(a, 0, 7);
    printf("最大值为：%d，最小值为：%d", result[1], result[0]);
}