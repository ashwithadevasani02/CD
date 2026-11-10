
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char ip[1000];
int pos=0;

void error(void);
void E(void);
void EPrime(void);
void T(void);
void TPrime(void);
void F(void);

void error(void){
    printf("Error at %d position",pos);
    exit(1);
}

// E -> T E'
void E(void){
    T();
    EPrime();
}

// E' -> + T E' | epsilon
void EPrime(void){
    if(ip[pos]=='+'){
        pos++;
        T();
        EPrime();
    }
}

// T -> F T'
void T(void){
    F();
    TPrime();
}

// T' -> * F T' | epsilon
void TPrime(void){
    if(ip[pos]=='*'){
        pos++;
        F();
        TPrime();
    }
}

// F -> (E) | id
void F(void){
    if(ip[pos]=='('){
        pos++;
        E();

        if(ip[pos]==')'){
            pos++;
        }
        else{
            error();
        }
    }
    else if(isalpha((unsigned char)ip[pos])){
        while(isalnum((unsigned char)ip[pos]) ||
              ip[pos]=='_'){
            pos++;
        }
    }
    else{
        error();
    }
}

int main(){
    printf("Enter the input: ");
    scanf("%999s",ip);

    if(ip[0]=='\0'){
        printf("Empty String");
        return 0;
    }

    pos=0;
    E();

    if(ip[pos]=='\0'){
        printf("String Accepted");
    }
    else{
        printf("String Rejected");
    }

    return 0;
}
