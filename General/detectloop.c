#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

int hasLoop(struct Node* list)
{
    struct Node *slow = list;
    struct Node *fast = list;
 
    while (slow && fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            return 1;
        }
    }
    return 0;
}

 int main()
{
    struct Node* one = (struct Node*)malloc(sizeof(struct Node));
    struct Node* two = (struct Node*)malloc(sizeof(struct Node));
    struct Node* three = (struct Node*)malloc(sizeof(struct Node));
    struct Node* four = (struct Node*)malloc(sizeof(struct Node));

    one->data = 1;
    two->data = 2;
    three->data = 3;
    four->data = 4;
    
    printf("1->2->3->4->2 \n");
    one->next = two;
    two->next = three;
    three->next = four;
    four->next = two;
    
    if (hasLoop(one))
        printf("Has a Loop \n\n");
    else
        printf("No Loop \n\n");
        
        
    printf("1->2->3->4->NULL \n"); 
    four->next = NULL;
    if (hasLoop(one))
        printf("Has a Loop \n\n");
    else
        printf("No Loop \n\n");
        
        
    printf("1->2->3->2 \n"); 
    three->next = two;
    if (hasLoop(one))
        printf("Has a Loop \n\n");
    else
        printf("No Loop \n\n");
        
    return 0;
}
