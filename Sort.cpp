//
//  Sort.cpp
//  MySort
//
//  Created by 苏亮 on 14/12/15.
//  Copyright (c) 2014年 苏亮. All rights reserved.
//  实现多种经典排序的模板类

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

#define LeftChild(i) (2*(i) + 1)

using namespace std;

template <class numtype>
class MySort{
public:
    const int cutoff  = 3;//
    void InsertionSort(numtype a[],int n); //插入排序
    void Shellsort(numtype a[],int n);     //希尔排序
    void Msort(numtype a[],numtype tmparray[],int Left,int Right);//分治
    void Merge(numtype a[],numtype tmparray[],int Lpos,int Rpos,int RightEnd);//合并
    void Mergesort(numtype a[],int n);     //归并排序
    void Qsort(numtype a[],int Left,int Right);//快速排序
    void Qselect(numtype a[],int k,int Left,int Right);//快速选择
    void Heapsort(numtype a[],int n); //堆排
    void PercDown(numtype a[],int i,int n); //
    numtype Median3(numtype a[],int Left,int Right);//中位数
};
// 插入排序
template <class numtype>
void MySort<numtype>::InsertionSort(numtype a[],int n){
    int j,p;
    numtype tmp;
    for(p = 0; p < n;p++){
        tmp = a[p];
        for(j = p;j>0 && a[j-1]>tmp;j--) //保证0 - p有序
            a[j] = a[j-1];
        a[j] = tmp;
    }
}
//希尔排序
template <class numtype>
void MySort<numtype>::Shellsort(numtype a[],int n){
    int i,j,Increment;
    numtype tmp;
    
    for( Increment = n/2; Increment > 0;Increment /= 2){
        for( i = Increment ;i < n ;i++){
            tmp = a[i];
            for( j = i ;j >= Increment;j -= Increment){
                if( tmp < a[j - Increment])
                    a[j] = a[j - Increment];
                else
                    break;
            }
            a[j] = tmp;
        }
    }
}

//归并排序
template <class numtype>
//分治
void MySort<numtype>::Msort(numtype a[], numtype tmparray[],int Left, int Right){
    if(Left < Right){
        int mid = (Left + Right)/2;
        MySort<numtype>::Msort(a,tmparray,Left,mid);//左区间
        MySort<numtype>::Msort(a,tmparray,mid+1,Right);//右区间
        MySort<numtype>::Merge(a,tmparray,Left,mid+1,Right);//合并
    }
}

template<class numtype>
//合并
void MySort<numtype>::Merge(numtype a[],numtype tmparray[],int Lpos,int Rpos,int RightEnd){
    int LeftEnd = Rpos - 1;
    int TmpPos = Lpos;
    int NumElements = RightEnd - Lpos + 1;
    while(Lpos <= LeftEnd && Rpos <= RightEnd){
        if(a[Lpos] <= a[Rpos])
            tmparray[TmpPos++] = a[Lpos++];
        else
            tmparray[TmpPos++] = a[Rpos++];
    }
    while(Lpos <= LeftEnd)
        tmparray[TmpPos++] = a[Lpos++];
    while(Rpos <= RightEnd)
        tmparray[TmpPos++] = a[Rpos++];
    
    for(int i = 0 ; i < NumElements  ;i++,RightEnd--)
        a[RightEnd] = tmparray[RightEnd];
}

template <class numtype>
void MySort<numtype>::Mergesort(numtype a[],int n){
    numtype *tmparray;
    tmparray = (numtype*)malloc( n * sizeof(numtype));
    if(tmparray != NULL){
        MySort<numtype>::Msort(a,tmparray,0,n-1);  //0 - n-1 有效
        free(tmparray);
    }
    else
        puts("No space for tmp array!!!");
}

//快速排序
template <class numtype>
numtype MySort<numtype>::Median3(numtype a[],int Left,int Right){
    int mid = (Left + Right)/2;
    if(a[Left] > a[mid])   swap(a[Left],a[mid]);
    if(a[Left] > a[Right]) swap(a[Left],a[Right]);
    if(a[mid]  > a[Right]) swap(a[mid] ,a[Right]);//3个元素有序化
    
    swap(a[mid],a[Right-1]);
    
    return a[Right - 1];
}
template <class numtype>
void MySort<numtype>::Qsort(numtype a[],int Left,int Right){
    if(Left + cutoff <= Right){
        numtype Pivot = MySort<numtype>::Median3(a,Left,Right);
        int i = Left;
        int j = Right -1;
        for(;;){
            while(a[++i] < Pivot);
            while(a[--j] > Pivot);
            if(i < j)
                swap(a[i],a[j]);
            else
                break;
        }
        swap(a[i],a[Right-1]);
        MySort<numtype>::Qsort(a,Left,i-1);
        MySort<numtype>::Qsort(a,i+1,Right);
    }
    else
        MySort<numtype>::InsertionSort(a,Right - Left + 1);
}
template <class numtype>
void MySort<numtype>::Qselect(numtype a[],int k,int Left,int Right){
    if(Left + cutoff <= Right){
        int i,j;
        int Pivot = MySort<numtype>::Median3(a,Left,Right);
        for(;;){
            while(a[++i] > Pivot);
            while(a[--j] < Pivot);
            if(i < j)
                swap(a[i],a[j]);
            else
                break;
        }
        swap(a[i],a[Right - 1]);
        if(k <= i){
            MySort<numtype>::Qselect(a,k,Left,i-1);
        }else if(k > i+1){
            MySort<numtype>::Qselect(a,k,i+1,Right);
        }
    }
    else{
        MySort<numtype>::InsertionSort(a,Right - Left + 1);
    }
}
//堆排
template <class numtype>
void MySort<numtype>::PercDown(numtype a[],int i,int n){
    int Child;
    numtype tmp;
    
    for( tmp = a[i];LeftChild(i) < n; i = Child){
        Child = LeftChild(i);
        if(Child != n - 1 && a[Child + 1] > a[Child])
            Child++;
        if(tmp < a[Child])
            a[i] = a[Child];
        else
            break;
    }
    a[i] = tmp;
}
template <class numtype>
void MySort<numtype>::Heapsort(numtype a[],int n){
    int i;
    
    for( i = n/2 ;i >= 0; i--)  // BuildHeap
        PercDown(a,i,n);
    for( i = n - 1;i > 0; i--){
        swap(a[0],a[i]) ;  //DeleteMax
        PercDown(a,0,i);
    }
}
int main(){
    
    MySort<int> p;
    int a[10] = {5,4,3,1,3,0,0};
    p.Heapsort(a,5);
    for(int i = 0;i < 5;i++)
        cout << a[i]<<endl;
     
    return 0;
}