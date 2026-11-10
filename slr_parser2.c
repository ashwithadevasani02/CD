#include<stdio.h>
#include<string.h>
int state[1000];
char symbol[1000];
int top=-1;
int action[6][3]={
   {3,-3,-3},
   {0,0,999},
   {0,5,-5},
   {0,-2,-2},
   {0,0,-1},
   {0,0,-4}
};
int goTo[6][3]={
    {1,2,-1},
    {-1,-1,-1},
    {-1,-1,4},
    {-1,-1,-1},
    {-1,-1,-1},
    {-1,-1,-1}
};
int getcol(char *input){
    if(strcmp(input,"a")==0) return 0;
     if(strcmp(input,"b")==0) return 1;
      if(strcmp(input,"$")==0) return 2;
   return -1;
}
int goToCol(char ch){
    if(ch=='S') return 0;
    if(ch=='A') return 1;
    if(ch=='B') return 2;
    return -1;

}
void push(char ch, int st){
    top++;
    symbol[top]=ch;
    state[top]=st;
}
void pop(int n){
    top-=n;
}
void printStack(){
    for(int i=0;i<=top;i++){
        printf("%c%d ", symbol[i], state[i]);
    }
}
int main(){
    char input[1000][10];
    int n,i,j;
    printf("Enter the number of tokens: ");
    scanf("%d",&n);
    printf("Enter the tokens one by one : ");
    for(i=0;i<n;i++){
        scanf("%s", input[i]);
    }
    strcpy(input[n],"$");
    push('$',0);
    i=0;
    printf("%-25s%-40s%s\n","Stack","Input","Action");
    while(1){
        int st= state[top];
        int c=getcol(input[i]);
        if(c==-1){
            printf("Invalid token");
            return 0;
        }
        int act=action[st][c];
        printStack();
        printf("\t\t\t\t");
        for(j=i;j<=n;j++){
            printf("%s",input[j]);
        }
        printf("\t\t\t\t\t\t");
        if(act==999){
            printf("String accepted ");
            return 0;
        }
        else if(act==0){
            printf("String Rejected");
            return 0;
        }
        else if(act >0){
            printf("Shift %d", act);
            push(input[i][0], act);
            i++;
        }
        else {
            int prod=-act;
            char LHS;
            int len,gc,next;
            switch(prod){
                case 1:
                    LHS='S';
                    len=2;
                    printf("Reduce S->AB");
                    break;
                 case 2:
                    LHS='A';
                    len=1;
                    printf("Reduce A->a");
                    break;
                 case 3:
                    LHS='A';
                    len=0;
                    printf("Reduce A->epsilon");
                    break;
                 case 4:
                    LHS='B';
                    len=1;
                    printf("Reduce B->b");
                    break;
                 case 5:
                    LHS='B';
                    len=0;
                    printf("Reduce B->epsilon");
                    break;
                default: 
                    printf("Invalid reduction");
                    return 0;
            }

            pop(len);
            gc = goToCol(LHS);
            next=goTo[state[top]][gc];
            if(next==-1){
                printf("String Rejected");
                return 0;
            }
            push(LHS,next);
            
        }
        printf("\n");

    }
    return 0;
}