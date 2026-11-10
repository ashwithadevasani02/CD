#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
char ip[1000];
int pos=0;
void error(void);
void S(void);
void L(void);
void LPrime(void);

void error(void){
    printf("Error at %d position", pos);
    exit(1);
}
void S(void){
    if(ip[pos]=='('){
        pos++;
        L();
        if(ip[pos]==')'){
            pos++;
        }
        else {
            error();
        }
    }
    else if(ip[pos]=='a'){
        pos++;
    }
    else{
        error();
    }
}
void L(void){
    S();
    LPrime();
}

void LPrime(void){
    if(ip[pos]==','){
        pos++;
        S();
        LPrime();
    }
}
int main(){
    printf("Enter the input: ");
    scanf("%s",ip);
    if(ip[0]=='\0'){
        printf("Empty String");
        return 0;
    }
    pos=0;
    S();
    if(ip[pos]=='\0'){
        printf("String Accepted");
    }
    else{
        printf("String Rejected");
    }
    return 0;
}