#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char str[30];
    int i, flag ;
    printf("Enter the word: ");
    scanf("%s", str);
    char *keywords[]={
        "if","else","switch","case",
        "default","for","do", "while",
        "break","continue","goto","return"
    };
    int n=sizeof(keywords)/sizeof(keywords[0]);
    for(i=0;i<n;i++){
        if(strcmp(keywords[i],str)==0){
            flag=1;
            break;
        }
    }
    if(flag==1){
        printf("The word is a keyword");
    }
    else if(isalpha(str[0]) && str[0]=='_'){
            for(i=1; str[i]!='\0';i++){
                if(!isalnum(str[i]) && str[i]!='_'){
                    flag=2;
                    break;
                }
            }
        if(flag==2){
            printf("%s is not a valid identifer", str);
        }
        else{
            printf("%s is a valid identifer", str);
        }
    }
    else{
        printf("%s is not a valid identifier", str);
    }
    return 0;
}