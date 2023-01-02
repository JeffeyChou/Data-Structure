// ---
// title: 农夫过河 栈 DFS
// date: 2022-10-01 20:36:45
// excerpt:
// tags: Data_Structure Stack DFS HW
// rating: ⭐
// status: inprogress
// share: false
// ---

/*
 * 约定：用四位二进制数分别顺序表示农夫、狼、白菜和羊的状态（在河的东岸或西岸）
 * 即: {dddd} <=> {Farmer, Wolf, Cabbage, Goat} 其中：d={0,1}
 * int visited[16]，数组十进制下标与二进制状态一一对应，数据域表示前驱状态
 *  说明：0表示在东岸 1表示在西岸，初始状态为0000，终止状态为1111
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{ //链表的节点结构
    int data;
    struct Node *pNext;
} NODE, *PNODE;

typedef struct Stack
{ //链表的头节点，储存栈底和栈顶指针
    PNODE pTop;
    PNODE pBottom;
} STACK, *PSTACK;

void init(PSTACK pS);
bool push(PSTACK, int);
bool is_empty(PSTACK);
void traverse(PSTACK);
bool pop(PSTACK, int *);
int is_safe(int state);

bool pop(PSTACK pS, int *pVal) //出栈，出栈元素通过指针返回
{
    if (is_empty(pS))
        return false;

    *pVal = pS->pTop->data;

    PNODE q = pS->pTop;
    pS->pTop = q->pNext;
    free(q);

    return true;
}

void traverse(PSTACK pS) //遍历，把所有元素打印出来，最左元素为栈顶
{
    PNODE p = pS->pTop;
    if (is_empty(pS))
    {
        printf("stack is empty.\n");
        return;
    }

    while (p->pNext != NULL)
    {
        printf("%d ", p->data);
        p = p->pNext;
    }
    printf("\n");
}

bool is_empty(PSTACK pS) //判断链栈是否为空
{
    if (pS->pTop == pS->pBottom)
        return true;
    return false;
}

bool push(PSTACK pS, int val) //入栈
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if (NULL == pNew)
    {
        printf("内存分配失败");
        return false;
    }
    pNew->data = val;
    pNew->pNext = pS->pTop;

    pS->pTop = pNew;

    return true;
}

void init(PSTACK pS) //初始化栈
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if (NULL == pNew)
    {
        printf("内存分配失败");
        exit(-1);
    }
    pNew->pNext = NULL;

    pS->pTop = pS->pBottom = pNew;
}

int is_safe(int state) //判断过河后是否安全
{
    if ((((state & 0x01) != 0) == ((state & 0x02) != 0)) &&
        ((((state & 0x01) != 0) != ((state & 0x08) != 0))))
        // 羊菜同岸且农夫不在场
        return (0);
    if ((((state & 0x01) != 0) == ((state & 0x04) != 0)) &&
        (((state & 0x01) != 0) != ((state & 0x08) != 0)))
        // 狼羊同岸且农夫不在场
        return (0);
    return (1);
}

int main(void)
{
    int routes[16];        // 记录已经考虑过的状态
    int state;             // 记录当前时刻的状态（状态编号的二进制形式即状态本身）
    int aftercross;        // 记录渔夫当前的选择（渡河对象）会导致的结果状态
    int passenger;         // 临时变量，用于表达农夫的选择（对应二进制位为1表示选中该乘客）
    int results[16] = {0}; // 输出结果
    int counter, i;

    STACK S;
    init(&S);
    push(&S, 0x00);
    routes[0] = 0;
    state = 0;
    for (int i = 0; i < 16; i++)
    {
        routes[i] = -1;
    }
    while (!(is_empty(&S)) && (routes[15] == -1))
    {

        for (passenger = 1; passenger <= 8; passenger <<= 1)
        {
            // 由于农夫总是在过河，随农夫过河的也只能是与农夫同侧的东西
            if (((state & 0x08) != 0) == ((state & passenger) != 0))
            {
                // 如果农夫与当前乘客在河岸的同一侧
                aftercross = state ^ (0x08 | passenger); // 渡河后的情况
                if (is_safe(aftercross) && (routes[aftercross] == -1))
                {
                    // 如果渡河后状态安全，则将其状态入队
                    routes[aftercross] = state; // 将当前状态的索引记录到路径数组中（下标索引为后续状态值）
                    push(&S, aftercross);
                }
            }
        }
        pop(&S, &state);
    }
    if (routes[15] != -1)
    {
        // printf("The reverse path is:\n");
        counter = 0;
        for (state = 15; state != 0; state = routes[state])
        {
            // printf("The state is: %d \n",state);
            results[counter] = state;
            counter++;
            // if(state == 0) return;
        }

        for (i = 0; i < counter; i++)
        {
            state = results[i];
            aftercross = results[i + 1];
            if (state & 0x08)
            {
                printf("农夫从东岸到西岸:");
            }
            else
            {
                printf("农夫从西岸到东岸:");
            }
            switch (state ^ aftercross)
            {
            case 12:
                printf("把狼带过河\n");
                break;
            case 10:
                printf("把菜带过河\n");
                break;
            case 9:
                printf("把羊带过河\n");
                break;
            default:
                printf("什么也不带\n");
                break;
            }
        }
    }
    else
    {
        printf("No solution for this problem.\n");
    }
    return 0;
}
