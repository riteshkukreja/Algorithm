//g++  4.9.3

/** 
 *  File Name: rotated-sorted-array-search.cpp
 *  Blog URL: https://riteshkukreja.wordpress.com/2016/10/05/rotated-sorted-array-search/
 *  Author: RITESH
 */

#include <iostream>
#include <vector>

using namespace std;

int search(vector<int> &A, int B) {
    int low = 0,  high = A.size()-1;
    
    int pivot = 0;
    
    while(low <= high) {
        int mid = low + (high-low)/2;
        
        if(A[mid] > A[pivot]) {
            low = mid+1;
        } else if(A[mid] < A[pivot]) {
            pivot = mid;
            high = mid;
        } else {
            low = mid+1;
        }
    }
    
    if(pivot == 0) {
        // no rotation
        low = 0;
        high = A.size()-1;
    } else {
        if(B < A[0]) {
            low = pivot;
            high = A.size()-1;
        } else {
            low = 0;
            high = pivot-1;
        }
    }
    
    while(low <= high) {
        int mid = low + (high-low)/2;
        
        if(A[mid] > B) {
            high = mid-1;
        } else if(A[mid] < B) {
            low = mid+1;
        } else {
            return mid;
        }
    }
    
    return -1;
}


int main()
{
    int N, K;
    cin >> N;
    vector<int> A(N);
    
    for(int i = 0; i < N; i++)
        cin >> A[i];
    
    cin >> K;
    
    cout << search(A, K) << endl;
    
    return 0;
}
