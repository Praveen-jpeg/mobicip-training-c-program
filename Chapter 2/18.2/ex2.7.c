unsigned invert(unsigned x,int p, int n){
    /*invert: return x with n bits starting 
    at position p inverted*/
    unsigned mask;
    mask = ((1U <<n) -1)<< (p+1-n);
    return x ^mask;
}
main(){
    printf("invert: %u\n",invert(170,5,3));
}