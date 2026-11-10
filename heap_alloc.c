#include<stdio.h>
#include<stdlib.h>
struct Block{
    int size,free;
    struct Block *next;
};
int main(){
    int n,p,choice,found;
    struct Block *head=NULL,*temp,*prev,*best;
    printf("Enter the number of blocks: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        temp=(struct Block*)malloc(sizeof(struct Block));
        printf("Enter the size of block %d: ",i+1);
        scanf("%d",&temp->size);
        temp->free=1;
        temp->next=NULL;
        if(head==NULL) head=temp;
        else{
            prev->next=temp;
        }
        prev=temp;
    }
    printf("Enter the choice: ");
    scanf("%d",&choice);
    printf("Enter the number of processes: ");
    scanf("%d",&p);
    for(int i=0;i<p;i++){
        int size;
        printf("Enter the size of the process %d: ",i+1);
        scanf("%d",&size);
        best=NULL;
        temp=head;
        found=0;
        while(temp!=NULL){
            if(temp->free && temp->size>=size){
                if(choice==1){
                    best=temp;
                    break;
                }
                else if(choice ==2 && (best==NULL || temp->size <best->size)){
                    best=temp;
                }
                 else if(choice ==3 && (best==NULL || temp->size >best->size)){
                    best=temp;
                }
            }
            temp=temp->next;
        }
        if(best!=NULL){
            best->free=0;
            found=1;
            printf("Process %d is allocated block of size %d\n",i+1,best->size);
        }
        if(!found){
            printf("Process %d is not allocated any block\n",i+1);
        }
    }
    temp=head;
    int i=0;
    printf("Final Heap Allocation: \n");
    printf("%-25s%-20s%10s\n","Block","Size","Status");
    while(temp!=NULL){
        printf(" %d\t%d\t%s",i++,temp->size,temp->free==1?"Not allocated": "Allocated");
        printf("\n");
        temp=temp->next;
    }
    while(head!=NULL){
        temp=head;
        head=head->next;
        free(temp);
    }
    return 0;
}