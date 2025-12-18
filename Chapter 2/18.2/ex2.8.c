unsigned rightrot(unsigned x, int n){
    /*rightrot: rotate x tothe right by n positions*/
    int wordsize;
    wordsize = sizeof(unsigned) * 8;
    n %= wordsize;
    return (x >>n) | (x << (wordsize -n));
}
int main(){
    printf("rightrot: %u\n",rightrot(170,3));
    return 0;
}