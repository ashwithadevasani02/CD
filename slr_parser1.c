
#include<stdio.h>
#include<string.h>

int state[1000];
char symbol[1000];
int top=-1;

/* ACTION table: id, +, *, (, ), $ */

int action[12][6]={
    {5,0,0,4,0,0},
    {0,6,0,0,0,999},
    {0,-2,7,0,-2,-2},
    {0,-4,-4,0,-4,-4},
    {5,0,0,4,0,0},
    {0,-6,-6,0,-6,-6},
    {5,0,0,4,0,0},
    {5,0,0,4,0,0},
    {0,6,0,0,11,0},
    {0,-1,7,0,-1,-1},
    {0,-3,-3,0,-3,-3},
    {0,-5,-5,0,-5,-5}
};

/* GOTO table: E, T, F */

int goTo[12][3]={
    {1,2,3},
    {-1,-1,-1},
    {-1,-1,-1},
    {-1,-1,-1},
    {8,2,3},
    {-1,-1,-1},
    {-1,9,3},
    {-1,-1,10},
    {-1,-1,-1},
    {-1,-1,-1},
    {-1,-1,-1},
    {-1,-1,-1}
};

int getcol(char *input){
    if(strcmp(input,"id")==0) return 0;
    if(strcmp(input,"+")==0) return 1;
    if(strcmp(input,"*")==0) return 2;
    if(strcmp(input,"(")==0) return 3;
    if(strcmp(input,")")==0) return 4;
    if(strcmp(input,"$")==0) return 5;
    return -1;
}

int goToCol(char ch){
    if(ch=='E') return 0;
    if(ch=='T') return 1;
    if(ch=='F') return 2;
    return -1;
}

void push(char ch,int st){
    top++;
    symbol[top]=ch;
    state[top]=st;
}

void pop(int n){
    top-=n;
}

void printStack(){
    for(int i=0;i<=top;i++){
        printf("%c%d ",symbol[i],state[i]);
    }
}

int main(){
    char input[1000][10];
    int n,i,j;

    printf("Enter the number of tokens: ");
    scanf("%d",&n);

    printf("Enter the tokens one by one:\n");
    printf("(Use id, +, *, (, ))\n");

    for(i=0;i<n;i++){
        scanf("%9s",input[i]);
    }

    strcpy(input[n],"$");

    push('$',0);
    i=0;

    printf("\n%-25s%-40s%s\n","Stack","Input","Action");

    while(1){
        int st=state[top];
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

        printf("\t\t\t\t\t");

        if(act==999){
            printf("String Accepted");
            return 0;
        }

        else if(act==0){
            printf("String Rejected");
            return 0;
        }

        else if(act>0){
            printf("Shift %d",act);

            if(strcmp(input[i],"id")==0)
                push('i',act);
            else
                push(input[i][0],act);

            i++;
        }

        else{
            int prod=-act;
            char LHS;
            int len,gc,next;

            switch(prod){
                case 1:
                    LHS='E';
                    len=3;
                    printf("Reduce E->E+T");
                    break;

                case 2:
                    LHS='E';
                    len=1;
                    printf("Reduce E->T");
                    break;

                case 3:
                    LHS='T';
                    len=3;
                    printf("Reduce T->T*F");
                    break;

                case 4:
                    LHS='T';
                    len=1;
                    printf("Reduce T->F");
                    break;

                case 5:
                    LHS='F';
                    len=3;
                    printf("Reduce F->(E)");
                    break;

                case 6:
                    LHS='F';
                    len=1;
                    printf("Reduce F->id");
                    break;

                default:
                    printf("Invalid reduction");
                    return 0;
            }

            pop(len);

            gc=goToCol(LHS);
            next=goTo[state[top]][gc];

            if(next==-1){
                printf("GOTO error");
                return 0;
            }

            push(LHS,next);
        }

        printf("\n");
    }

    return 0;
}
