#include "additional_functions.h"


int findSmallestElement(const int arr[], int n){
    /**
       * @brief This function finds the smallest element
       * in the array and returns its index
       *
       * @param arr
       * int array of the elements
       * @param n
       * size of the array
    */
    int temp = arr[0];
    int res = 0;
    for(int i=0; i<n; i++) {
        if(temp>arr[i]) {
            temp=arr[i];
            res = i;
        }
    }
    return res;
}


int findElementIndex(const int arr[], int n, int el){
    /**
       * @brief This function finds the given element
       * in the array and returns its index
       *
       * @param arr
       * int array of the elements
       * @param n
       * size of the array
       * @param el
       * int element that should be found
    */
    int res = -1;
    for(int i=0; i<n; i++) {
        if(arr[i] == el) {
            res = i;
            break;
        }
    }
    return res;
}


int binaryToDecimal(char* n, int len) {
    /**
       * @brief This function converts the number in binary
       * representation in int
       *
       * @param n
       * number in binary representation
       * @param len
       * size of the array n
    */
    char* num = n;
    int dec_value = 0;
    int base = 1;

    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

