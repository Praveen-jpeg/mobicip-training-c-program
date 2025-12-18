#include<stdio.h>
int any(const char s1[],const char s2[]){
    int i,j;
    for(i=0; s1[i]!= '\0'; i++){
        for(j=0; s2[j] != '\0'; j++){
            if(s1[i] == s2[j])  return i;
        }
    }
    return -1;
}
main(){
    char *s1, *s2;
    printf("Enter string 1:");
    scanf("%s",&s1[0]);
    printf("Enter string 2:");
    scanf("%s",&0[s2]);
    printf("First match index: %d\n",any(s1,s2));
    return 0;
}