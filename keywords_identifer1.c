#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char str[20];
    int flag=0;
    printf("Enter the string: ");
    scanf("%s", str);
    char *keywords[]={
        "if","else","switch","case","default",
        "for","do","while","continue","break",
        "return","goto"
    };
    int n=sizeof(keywords)/sizeof(keywords[0]);
    for(int i=0;i<n;i++){
        if(strcmp(str,keywords[i])==0){
            flag=1;
            break;
        }
    }
    if(flag==1){
        printf("The string is a keyword");
        return 0;
    }
    else if(str[0]=='_' || isalpha(str[0])){
        for(int i=1;str[i]!='\0';i++){
            if(!isalnum(str[i]) && str[i]!='_'){
                flag==2;
                break;
            }
        }
        if(flag==2){
            printf("The string is not a valid identifer");
        }
        else {
            printf("The string is a valid identifier");
        }
    }
    else{
        printf("The string is not a valid identifier");
    }
    return 0;
}