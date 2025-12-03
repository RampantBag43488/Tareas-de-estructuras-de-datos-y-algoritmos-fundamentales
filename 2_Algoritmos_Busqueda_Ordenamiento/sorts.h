#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
using namespace std;

template <class T>
class Sorts {
    private:
        void mergeSplit(vector<T>&, int, int);
        void merge(vector<T>&, int, int, int);
    public:
        void ordenaSeleccion(vector<T>&);
        void ordenaBurbuja(vector<T>&);
        void ordenaMerge(vector<T>&);
        int busqSecuencial(vector<T>, int);
        int busqBinaria(vector<T>&, int);
};

template <class T>
void Sorts<T>::ordenaSeleccion(vector<T>& v) {
    T temp;
    int s = v.size();
    for (int i = 0; i < s - 1; i++) {
        int min = i;
        for(int j = i; j < s; j++) {
            if(v[j] < v[min]) {
                min = j;
            }
        }
        temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<T>& v) {
    int s = v.size();
    T temp;
    for(int i = s - 1; i > 0; i--) {
        for(int j = 0; j < i; j++) {
            if(v[j] > v[j+1]) {
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

template <class T>
void Sorts<T>::mergeSplit(vector<T>& v, int low, int high) {
    if(low >= high) {
        return;
    }
    int mid = (low + high)/2;
    mergeSplit(v, low, mid);
    mergeSplit(v, mid + 1, high);
    merge(v, low, mid, high);
}

template <class T>
void Sorts<T>::merge(vector<T>& v, int low, int mid, int high) {
    vector<T> aux(high + 1 - low);
    int i = low;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= high){
        if(v[i] <= v[j]) {
            aux[k] = v[i];
            i++;
        }
        else {
            aux[k] = v[j];
            j++;
        }
        k++;
    }

    while(i <= mid){
        aux[k] = v[i];
        i++;
        k++;
    }
    while(j <= high){
        aux[k] = v[j];
        j++;
        k++;
    }

    int a = aux.size();
    for (int t = 0; t < a; t++) {
        v[low + t] = aux[t];
    }
}

template <class T>
void Sorts<T>::ordenaMerge(vector<T>& v) {
    if(v.size() > 1) {
        mergeSplit(v, 0, v.size() - 1);
    }
}

template <class T>
int Sorts<T>::busqSecuencial(vector<T> v, int n){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == n) {
            return i;
        }
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(vector<T>& v, int n) {
    int low = 0;
    int high = v.size() - 1;

    while(low <= high) {
        int mid = (low + high)/2;
        if(n == v[mid]) {
            return mid;
        }
        else if(n < v[mid]){
            high = mid - 1;
        }
        else if(n > v[mid]){
            low = mid + 1;
        }
    }
    return -1;
}

#endif