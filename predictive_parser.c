#include<stdio.h>
#include<string.h>
char stack[1000];
char input[1000];
int top=-1, ip=0;
void push(char ch){
    stack[++top]=ch;
}
int pop(){
    return stack[top--];
}
int peek(){
    return stack[top];
}
int row(char ch){
    switch(ch){
        case 'E': return 0;
        case 'Q': return 1;
        case 'T': return 2;
        case 'R': return 3;
        case 'F': return 4;
        default : return -1;
    }
}
int col(char ch){
    switch(ch){
        case '+': return 0;
        case '*': return 1;
        case '(': return 2;
        case ')': return 3;
        case 'i': return 4;
        case '$': return 5;
        default : return -1;
    }
}

char *table[5][6]={
    {"", "", "TQ","","TQ", ""},
    {"+TQ","","","e","","e"},
    {"","","FR","","FR",""},
    {"e","*FR","","e","","e"},
    {"","","(E)","","i",""}
};

void displayParsingTable(){
    printf("\n\tPREDICTIVE PARSING TABLE\n\n");

printf("+------+-------+-------+-------+-------+-------+-------+\n");
printf("| NT/T |  id   |   +   |   *   |   (   |   )   |   $   |\n");
printf("+------+-------+-------+-------+-------+-------+-------+\n");

char nonterminals[] = {'E', 'Q', 'T', 'R', 'F'};

for (i = 0; i < 5; i++)
{
    printf("|  %c   ", nonterminals[i]);

    for (j = 0; j < 6; j++)
    {
        if (table[i][j][0] == '\0')
            printf("|       ");
        else
            printf("| %-5s ", table[i][j]);
    }

    printf("|\n");
  
}
}

int main(){
    printf("Enter the string ending with $ : ");
    scanf("%s",input);
    if(strlen(input)==0 || input[strlen(input)-1]!='$'){
        printf("Invalid string");
        return 0;
    }
    push('$');
    push('E');
    while(top>=0){
        char x=peek();
        char a=input[ip];
        if(x=='$' && a=='$'){
            pop();
            ip++;
            printf("Valid string");
            return 0;
        }
        if(x==a){
            pop();
            ip++;
        }
        else if(row(x)!=-1){
            int r=row(x);
            int c=col(a);
            if(c==-1 || table[r][c][0]=='\0'){
                printf("Invalid String");
                return 0;
            }
            pop();
            if(!strcmp(table[r][c], "e")==0){
                int n=strlen(table[r][c]);
                for(int j=n-1;j>=0;j--){
                    push(table[r][c][j]);
                }
            }
        }
        else{
            printf("Invalid String");
            return 0;
        }
    }
    printf("Invalid String");
    return 0;
}