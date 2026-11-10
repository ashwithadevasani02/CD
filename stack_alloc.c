    #include<stdio.h>
    #include<stdlib.h>
    int *stack=NULL;
    int size,top=-1;
    void allocate(){
        int value;
        int *temp;
        printf("Enter the memory to be allocated: ");
        scanf("%d",&value);
        if(top==size-1){
            printf("Enter no enough memory, removing the top element : %d",stack[top]);
            top--;
            if(top==-1){
                free(stack);
                stack=NULL;
            }
            else{
                temp=realloc(stack,(top+1)*sizeof(int));
                if(temp!=NULL){
                    stack=temp;
                }
            }
        }
            temp=realloc(stack,(top+2)*sizeof(int));
            if(temp==NULL){
                printf("Memory allocation failed ");
                return ;
            }
            stack=temp;
            stack[++top]=value;
    }
        void deallocate(){
            int *temp;
            if(top==-1){
                printf("No elements ");
                return;
            }
            printf("Removing %d of memory",stack[top]);
            top--;
            if(top==-1){
                free(stack);
                stack=NULL;
            }
            else{
                temp=realloc(stack,(top+1)*sizeof(int));
                if(temp!=NULL){
                    stack=temp;
                }
            }
        }
        void display(){
             if(top==-1){
                printf("No elements ");
                return;
            }
            printf("Elements of the stack are :");
            for(int i=top;i>=0;i--){
                printf("%d\n",stack[i]);
            }
        }
        void main(){
            int choice;
            printf("Enter the size of the stack:");
            scanf("%d",&size);
            if(size==0){
                printf("Invalid size");
                return;
            }
            while(1){
            
                printf("1.Allocate\n");
                printf("2.Deallocate\n");
                printf("3.Display\n");
                printf("4.Exit");
                printf("Enter choice to choose any operation: ");
                scanf("%d",&choice);
                switch(choice){
                    case 1: allocate();
                            break;
                    case 2: deallocate();
                            break;
                    case 3: display();
                            break;
                    case 4: free(stack);
                            stack=NULL;
                            printf("Exiting ...releasing memory....");  
                            return 0;
                    default: printf("Invalid choice");
                }
            }
            return;
        }
