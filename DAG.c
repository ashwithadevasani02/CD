#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct node{
    char op,name[200],temp[200];
    struct node *l,*r;
};
struct node* nodes[100];
char s[100];
int p=0, countTemp=0, count=0;
struct node* create(char op,char *name,struct node *l,struct node *r){
    for(int i=0;i<count;i++){
        if(nodes[i]->op==op){
            if(!op && strcmp(nodes[i]->name,name)==0) return nodes[i];
            if(op && nodes[i]->l==l && nodes[i]->r==r) return nodes[i];
        }
    }
    struct node *n=calloc(1,sizeof(struct node));
    n->op=op;
    if(name) strcpy(n->name,name);
    n->l=l;
    n->r=r;
    nodes[count++]=n;
    return n;
}
struct node* expr();
struct node* factor(){   //unary,brackets and operands
    while(s[p]==' ') p++;
    if(s[p]=='-'){
        p++;
        return create('~',NULL,factor(),NULL);
    }
    if(s[p]=='('){
        p++;
        struct node* n=expr();
        p++;
        return n;
    }
    char a[10];
    int i=0;
    while(isalnum((unsigned char)s[p]) || s[p]=='_'){
        a[i++]=s[p++];
    }
    return create(0,a,NULL,NULL);
}
struct node* term(){ // multiplication and divison
    struct node *n=factor();
    while(s[p]=='*' ||s[p]=='/'){
        char op=s[p++];
        n=create(op,NULL,n,factor());
    }
    return n;
}
struct node* expr(){ // multiplication and divison
    struct node *n=term();
    while(s[p]=='+' ||s[p]=='-'){
        char op=s[p++];
        n=create(op,NULL,n,term());
    }
    return n;
}
char* generate(struct node *n){
    if(!n->op) return n->name;
    if(n->temp[0]) return n->temp;
    char a[100],b[100],t[100];
    strcpy(a,generate(n->l));
    if(n->op=='~'){
        sprintf(t,"t%d",++countTemp);
        printf("%s = -%s\n",t,a);
    }
    else{
        strcpy(b,generate(n->r));
        sprintf(t,"t%d",++countTemp);
        printf("%s = %s %c %s\n",t,a,n->op,b);
    }
    strcpy(n->temp,t);
    return n->temp;
}
int main(){
    printf("Enter the expression: ");
    scanf("%99[^\n]",s);
    struct node *root=expr();
    printf("Three Address Code :\n");
    printf("result = %s",generate(root));
    return 0;
}