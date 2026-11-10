#include<stdio.h>
#include<ctype.h>
char a[50][50];
char first[26][50];
int count[26]={0};
int n=0;
int present(int index,char ch){
    for(int i=0;i<count[index];i++){
        if(first[index][i]==ch) return 1;
    }
    return 0;
}
int add(int index,char ch){
    if(!present(index,ch)){
        first[index][count[index]++]=ch;
        return 1;
    }
    return 0;
}
void findfirst(){
    int changed=1;
    while(changed){
        changed=0;
        for(int i=0;i<n;i++){
            int index=a[i][0]-'A';
            int nullable=1;
            for(int j=2;a[i][j]!='\0';j++){
                char ch=a[i][j];
                if(ch=='e'){
                    changed |=add(index,'e');
                    nullable=1;
                    break;
                }
                if(!isupper((unsigned char)ch)){
                    changed |=add(index,ch);
                    nullable=0;
                    break;
                }
                char k=ch-'A';
                int hasEpsilon=0;
                for(int x=0;x<count[k];x++){
                    if(first[k][x]=='e') {
                        hasEpsilon=1;
                    }
                    else{
                        changed |=add(index,first[k][x]);
                    }
                }
                if(!hasEpsilon){
                    nullable=0;
                    break;
                }
            }
            if(nullable){
                changed |=add(index,'e');
            }
        }
    }
}

void display(char ch){
    printf("First(%c) : {",ch);
    for(int i=0;i<count[ch-'A'];i++){
        printf("%c ",first[ch-'A'][i]);
    }
    printf("}\n");
}
void displayAll(){
    int visited[26]={0};
    for(int i=0;i<n;i++){
        int index=a[i][0]-'A';
        if(!visited[index]){
            display(a[i][0]);
            visited[index]=1;
        }
    }
}
int main(){
    
    printf("Enter the number of productions: ");
    scanf("%d",&n);
    printf("Enter the productions: ");
    for(int i=0;i<n;i++){
        scanf("%s",a[i]);
    }
    findfirst();
    displayAll();
    return 0;

}