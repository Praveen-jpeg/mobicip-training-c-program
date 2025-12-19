#include<stdio.h>
#include<stdlib.h>
int binsrch(int x, int* v, int n){
    int low=0, mid, high=n-1;
    /*Only 1 test inside loop*/
    while(low < high){
        mid = (low + high) /2;
        if(x <= mid[v]) high = mid;
        else low = mid +1;
    }
    /*Final test after loop*/
    if(low < n && low[v] ==x) return low;
    else return -1;
}
int main(){
    int n,x,pos;
    printf("Enter no.of Elements:");
    scanf("%d",&n);
    int v[n];
    printf("Enter %d sorted elements:",n);
    for(int i=0;i<n;i++)    scanf("%d",v+i);
    printf("Enter element to search:");
    scanf("%d",&x);
    pos = binsrch(x,v,n);
    if(pos != -1)
        printf("Found %d at index %d\n",x,pos);
    else 
        printf("Element not found\n");
    return 0;
}