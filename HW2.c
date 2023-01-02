// ---
// title: 🐈homework-2022-09-22
// date: 2022-09-22 00:05:03
// tags: DS
// rating: ⭐️
// excerpt:以单链表作为储存结构实现简单的选择排序。
// ---

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElemType;

typedef struct node
{
    ElemType data;
    struct node *next;
} TNode, *PList;

void printlist(PList L)
{
    PList pee = NULL;
    pee = L->next;
    while (pee)
    {
        printf("%d,", pee->data);
        pee = pee->next;
    }
    printf("\n");
}

PList list_create(int n)
{
    int i;
    PList phead, ptail, pnode;
    phead = (PList)malloc(sizeof(TNode));
    if (!phead)
    {
        printf("Error when creating list.");
        exit(0);
    }
    phead->next = NULL;
    ptail = phead;
    srand(time(NULL));
    for (i = 0; i < n; ++i)
    {
        pnode = (PList)malloc(sizeof(TNode));
        if (!pnode)
        {
            printf("Error when creating list.");
            exit(0);
        }
        pnode->data = rand() % 100 + 1;
        pnode->next = NULL;
        ptail->next = pnode;
        ptail = pnode;
    }
    ptail->next = NULL;
    return phead;
}

int length(PList phead)
{
    if (!phead)
    {
        printf("invaild phead when checking its length.");
        exit(0);
    }
    PList temp;
    temp = phead->next;
    int len = 0;
    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }
    return len;
}

PList FindPreNode(TNode *pnode, PList phead)
{
    if (!pnode || !phead)
    {
        printf("invaild linked-list in FindPreNode.");
        exit(0);
    }
    PList temp = phead->next;
    while ( temp->next != pnode)
    {
        temp = temp->next;
    }
    return temp;
}


PList select_sort1(PList L, int size){
    if (!L)
    {
        printf("invaild linked-list");
        exit(0);
    }
    else if (size < 2)
    {
        return L;
    }
    else
    {
        PList temphead, pointer, minpointer, pre_temphead, pre_min, next_min, swap_head;
        int swap;
        pre_temphead = L;
        for (temphead=L->next; temphead->next != NULL ; temphead = temphead->next)
        {
            minpointer = temphead;
            swap_head = temphead;
            for (pointer = temphead->next; pointer; pointer=pointer->next)
            {
                if (pointer->data < minpointer->data)
                {
                    minpointer = pointer;
                    pre_min = FindPreNode(minpointer, L);
                }
            }
            next_min = minpointer->next;
            printf("obtain the min val: %d \n", minpointer->data);
            printf("current temphead val: %d \n", temphead->data);
            if (minpointer != temphead)
            {
                pre_temphead->next = minpointer;
                minpointer->next = temphead;
                pre_min->next = next_min;
                printlist(L);
                temphead = minpointer;
                pre_temphead = minpointer;
            }
        }
    }
    return L;
}



PList select_sort2(PList L, int size)
{
    if (!L)
    {
        printf("invaild linked-list");
        exit(0);
    }
    else if (size < 2)
    {
        return L;
    }
    else
    {
        PList temphead, pointer, minpointer;
        int swap;
        for (temphead=L->next; temphead->next != NULL ; temphead = temphead->next)
        {
            minpointer = temphead;
            for (pointer = temphead->next; pointer; pointer=pointer->next)
            {
                if (pointer->data < minpointer->data)
                {
                    minpointer = pointer;
                }
            }
            printf("obtain the min val: %d \n", minpointer->data);
            //            SwapHeadAnother(temphead->next, min);
            if (minpointer != temphead)
            {
                swap = temphead->data;
                temphead->data = minpointer->data;
                minpointer->data = swap;
                printlist(L);

            }
        }
    }
    return L;
}

int main()
{
    PList L;
    int number, size;
    printf("enter the length of your linked-list:");
    scanf("%d", &number);
    L = list_create(number);
    size = length(L);
    printlist(L);
    select_sort1(L, number);
    printlist(L);
    return 0;
}
//定义了两个选择排序的实现方法;
// select_sort1是改变链表的指针域不改变数据域；
// select_sort2是改变链表的数据域不改变指针域;
