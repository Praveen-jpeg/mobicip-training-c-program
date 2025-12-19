/*bitcount: count 1 bits in x (faster version)*/
int bitcount(unsigned x){
    int count;
    for(count = 0; x!=0;count++)
        x &= (x-1);/*delete rightmost 1-bit*/
    return count;
}
int main(){
    printf("Enter a unsigned integer:");
    unsigned num;
    scanf("%u",&num);
    printf("bitcount of %u: %d\n",num,bitcount(num));
}