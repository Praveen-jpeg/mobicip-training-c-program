unsigned setbits(unsigned x,int p,int n, unsigned y){
    /*setbits: return x with n bits starting at 
    position p set to the rightmost n bits of y*/
    unsigned mask;
    mask = ((1U <<n) -1)<< (p+1-n);
    return (x & ~mask) | ((y & ((1U <<n)-1))<<(p+1 -n));
}
int main(){
    printf("setbits: %u\n",setbits(170,5,3,7));
}