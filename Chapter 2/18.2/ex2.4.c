void squeeze(char s1[],const char s2[]){
    /*since string 2 is read only, we use const here.
    it is not a necessity, but it avoids bugs*/
    int i,j,k;
    int found;
    for(i=j=0; s1[i] != '\0'; i++){
        found =0;
        for(k=0; s2[k] != '\0'; k++){
            if(s1[i] == s2[k]){
                found = 1;
                break;
            }
        }
        if(!found)  s1[j++] = s1[i];
    }
    s1[j] = '\0';
}
main(){
    char *s1, *s2;
    printf("Enter string 1:");
    scanf("%s",&s1[0]);
    printf("Enter string 2:");
    scanf("%s",&0[s2]);
    squeeze(s1,s2);
    printf("After Squeeze: %s\n",s1);
    return 0;
}