// ---
// title: 编程实现快速排序和折半查找算法
// date: 2022-10-28 15:18:45
// excerpt:
// tags: Data_Structure Linkedlist quick_sort binary_search
// rating: ⭐
// status: Complete
// share: false
// ---

// 实验内容：编程实现快速排序和折半查找算法，要求如下：
// 1. 用C语言实现从终端或文件中读入数据序列
// 2. 用C语言实现快速排序算法,并对输入的序列排序后输出；
// 3. 用C语言实现折半查找算法，并在步骤(2)排序后得到的
// 序列上进行任意地元素查找，并输出查询结果。


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define SIZE 7

// 数据域结构
typedef struct info
{
    int id;
    char name[10];
    int age;
} ElemType;

//验证数据1
// 12 18 Beijing 37 23 Shanghai 27 16 Chengdu 16 18 Hangzhou 22 25 Wuxi 89 22 Foshan 35 24 Tianjin

// 单链表结构
typedef struct node
{
    ElemType data;     // 数据域
    struct node *next; // 指针域
} ListNode, *ListNodePtr;

// 以带头节点的方式随机创建一个单链表
ListNodePtr LinkedListInit()
{
    ListNode *Head, *L, *LNew;
    int id;
    char name[10];
    int age;
    // 申请节点空间
    Head = (ListNode *)malloc(sizeof(ListNode));
    // 判断是否有足够内存空间
    if (Head == NULL)
    {
        printf("申请空间失败\n");
        exit(-1);
    }
    L = Head;
    L->next = NULL;
    //  srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        // id = rand() % 1100;
        // age = rand() % 20 + 18;
        // 分配第一个节点
        LNew = (ListNode *)malloc(sizeof(ListNode));
        // 判断是否有足够内存空间
        if (LNew == NULL)
        {
            printf("申请空间失败\n");
            exit(-1);
        }
        scanf("%d", &id);
        LNew->data.id = id;
        scanf("%d", &age);
        LNew->data.age = age;
        // 注意字符串数组的名字就是首地址，不需要"&"
        scanf("%s", name);
        // 字符复制，用strcpy来复制
        //    get_random_str(name, 8);
        strcpy(LNew->data.name, name);
        L->next = LNew;
        LNew->next = NULL;
        L = LNew;
    }

    return Head;
}

// 遍历节点并输出
void ListTraversing(ListNodePtr start)
{
    printf("\n");
    for (ListNodePtr listNode = start->next; listNode; listNode = listNode->next)
    {
        printf("-|ID:%d , Name:%s , Age:%d|-", listNode->data.id, listNode->data.name, listNode->data.age);
    }
}

//产生长度为random_len的随机字符串
int get_random_str(char *random_str, const int random_len)
{
    int i, random_num, seed_str_len;
    struct timeval tv;
    unsigned int seed_num;
    char seed_str[] = "abcdefghijklmnopqrstuvwxyz"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; //随机字符串的随机字符集

    seed_str_len = strlen(seed_str);

    gettimeofday(&tv, NULL);
    seed_num = (unsigned int)(tv.tv_sec + tv.tv_usec); //超了unsigned int的范围也无所谓，我们要的只是不同的种子数字
    srand(seed_num);

    for (i = 0; i < random_len; i++)
    {
        random_num = rand() % seed_str_len;
        random_str[i] = seed_str[random_num];
    }

    return 0;
}

// 快速排序
void LinkedListQuickSort(ListNodePtr left, ListNodePtr right)
{
    if (left->next == right)
    {
        return;
    }
    ListNode *key = left->next,
             *i = key,
             *j = key->next;
    while (j != right)
    {
        if (j->data.id <= key->data.id)
        {
            i = i->next;
            // 交换
            ElemType temp = i->data;
            i->data = j->data;
            j->data = temp;
        }
        j = j->next;
    }
    ElemType temp = key->data;
    key->data = i->data;
    i->data = temp;
    LinkedListQuickSort(left, i);
    LinkedListQuickSort(i, right);
}

// 获取链表长度
int GetLength(ListNodePtr phead)
{
    if (!phead)
    {
        printf("invaild phead when checking its length.");
        exit(0);
    }
    ListNodePtr temp;
    temp = phead->next;
    int len = 0;
    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }
    return len;
}

// 查找介于start节点和end节点的中间值
ListNode* MiddleNode(ListNode* start, ListNode* end)
{
    if (start == NULL)
    {
        return NULL;
    }
    // slow 定义为第一个含数据的节点
    ListNode *slow = start;
    ListNode *fast = start->next;
    while (fast != end)
    {
        fast = fast->next;
        if (fast != end)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}

// 折半查找
ListNode* BinarySearch(ListNodePtr list, int key, int print)
{
    ListNode *start = list->next;
    ListNode *last = NULL;
    do
    {
        ListNode *mid = MiddleNode(start, last);
        if (mid ==NULL)
        {
            return NULL;
        }
        if (mid->data.id == key)
        {
            if (print)
            {
                printf("\nfind the value:");
                printf("-|ID:%d , Name:%s , Age:%d|-", mid->data.id, mid->data.name, mid->data.age);
            }
            return mid;
        }
        else if (mid->data.id < key)
        {
            start = mid->next;
        }
        else
        {
            last = mid;
        }
    } while (last == NULL || last != start);
    printf("\nno such value");
    return NULL;
}

int main()
{
    // 初始化
    printf("\ninput your value capacity is %d:", SIZE);
    ListNodePtr LinkedList = LinkedListInit();
    printf("\ninit:");
    ListTraversing(LinkedList);
    // 单链表快速排序
    printf("\nafter sort:");
    LinkedListQuickSort(LinkedList, NULL);
    ListTraversing(LinkedList);
    // 单链表折半查找
    printf("\nbinary search[input your key value]:");
    int key;
    scanf("%d", &key);
    ListNode *value = BinarySearch(LinkedList, key, 1);
    return 0;
}
