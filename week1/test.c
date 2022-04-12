#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *lowerString(char *str){
    //int l = strlen(str);
    for(int i=0; str[i]!='\0'; i++)
    {
        if(str[i]>='A' && str[i]<='Z')
        {
            str[i] = str[i] + 32;
        }
    }
    //str[l] = '\0';
    return str;
}
int main(){
    char str[10] = "conGa";
    printf("%s", lowerString(str));
    return 0;
}
