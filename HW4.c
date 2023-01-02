// ---
// title: 线性表合并
// date: 2022-10-24 20:36:45
// excerpt:
// tags: Data_Structure Linkedlist list_merge
// rating: ⭐
// status: Complete
// share: false
// ---

// 内容：实现带头结点的单向链表的创建、删除链表、插入结点等操作
// 可每个学生的学号互不相同，学号不同姓名相同则为不同的学生，
// 每个学生的学号在合并后的链表中不重复，
// 如果出现重复，则删除年龄较小结点。最后打印输出合并后的链表元素
// 本实验需要完成如下任务：
// * 设计学生信息结点的数据结构；
// * 用C语言实现创建升序链表的函数，每个结点的学号不同，按照学号升序排列；
// * 用C语言实现结点的插入的函数，插入后仍然为升序；
// * 编程实现两个单向链表合并，合并后仍然升序；
// * 编程实现合并后链表逆序排列的算法；
// * 打印输出合并后的链表元素

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
// 31544 18 xinhua 125054 23 kughya 135200 16 ahksx 315242 18 jlaikfen 315242 25 nsakfef 1253542 22 sefhkua 123502 24 sahfkuef
//验证数据2
// 123512 22 wuxing 153215 32 skliuhe 153214 12 hjfkus 135241 34 sleifjd 135421 22 sliefjs 135420 24 ksiuhef 135421 12 sklehfdf

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
        id = rand() % 1100;
        age = rand() % 20 + 18;
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
        printf("|ID:%d , Name:%s , Age:%d |", listNode->data.id, listNode->data.name, listNode->data.age);
    }
}

//指定位置和值插入节点
ListNodePtr LinkedListInsert(ListNodePtr list, int pos, int id, char *name, int age)
{
    int i = 0;
    while (i != pos && list->next)
    {
        i++;
        list = list->next;
    }

    // 输入超过值
    if (i != pos)
    {
        printf("\nerror,oversize!");
        return list;
    }

    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data.id = id;
    strcpy(p->data.name, name);
    p->data.age = age;
    p->next = list->next;
    list->next = p;
    return list;
}

// 删除(以输入链表的一个节点为0)指定位置的节点
ListNodePtr LinkedListDelete(ListNodePtr list, int pos)
{
    int i = 0;
    while (i != pos && list->next)
    {
        i++;
        list = list->next;
    }
    // 输入超过值
    if (i != pos || !list->next)
    {
        printf("\nerror,oversize!");
        return list;
    }
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p = list->next;
    list->next = p->next;
    free(p);
    return list;
}

// 指定位置修改值
ListNodePtr LinkedListUpdate(ListNodePtr list, int pos, int id, char *name, int age)
{
    ListNode *p = list->next;
    int count = 0;
    while (count != pos && p)
    {
        p = p->next;
        count++;
    }
    if (count != pos)
    {
        printf("\noverflow");
        return list;
    }
    p->data.id = id;
    strcpy(p->data.name, name);
    p->data.age = age;
    return list;
}

// 就地逆置 头插法
ListNodePtr LinkedListReverse(ListNodePtr list)
{
    ListNode *pre = list,
             *p = pre->next,
             *r = p->next;
    while (r)
    {
        p->next = r->next;
        r->next = pre->next;
        pre->next = r;
        r = p->next;
    }
    return list;
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

// 插入有序链表
ListNodePtr SortedLinkedListInsert(ListNodePtr list, int id, char *name, int age)
{
    ListNode *temp = list->next;
    if (id <= temp->data.id)
    {
        LinkedListInsert(list, 0, id, name, age);
        return list;
    }
    else
    {
        int pos = 0;
        while (id > temp->data.id && temp->next)
        {
            temp = temp->next;
            pos++;
        }
        LinkedListInsert(list, pos, id, name, age);
        return list;
    }
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

// 递增单链表合并为一个新的递增单链表
ListNodePtr LinkedListUnion(ListNodePtr starta, ListNodePtr startb)
{
    ListNode *r = starta,
             *la = starta->next,
             *lb = startb->next;
    while (la && lb)
    {
        if (la->data.id < lb->data.id)
        {
            r->next = la;
            r = la;
            la = la->next;
        }
        else
        {
            r->next = lb;
            r = lb;
            lb = lb->next;
        }
    }
    if (la)
    {
        r->next = la;
    }
    else
    {
        r->next = lb;
    }
    return starta;
}
//  去除有序链表中学号重复的节点，保留相同学号下年龄较大的节点
ListNodePtr LinkedListDeduplication(ListNodePtr list)
{
    ListNode *p=list->next; // 主节点，初始为第一个元素
    ListNode *pre=NULL;//保存被比较元素的前驱，便于删除
    ListNode *r=NULL; //用于遍历其他节点。
    ListNode *t=NULL; // 用于删除节点
    while(p!=NULL)
    {
        r = p->next;
        pre = p;
        while(r!=NULL)
        {
            if(r->data.id==p->data.id)//元素相同则直接让前驱指向r的后缀
            {
                pre->next = r->next;
                t = r; //注意回收
                r = r->next;//接着遍历其它节点
                free(t);
            }
            else//元素不相同让r向后继续遍历，主节点不变
            {
                pre = pre->next;
                r = r->next;//接着遍历其它节点
            }
        }
        p = p->next;//主节点比对完毕，更换为下一个
    }
    return list;
}

int main()
{
    // 初始化
    ListNodePtr LinkedList = LinkedListInit();
    printf("\ninit:");
    ListTraversing(LinkedList);
    // // 插入
    // LinkedListInsert(LinkedList, 3, 126842, "wuxiang", 18);
    // printf("\ninsert by pos:");
    // ListTraversing(LinkedList);
    // // 按位置删除
    // LinkedListDelete(LinkedList, 1);
    // printf("\ndelete by pos:");
    // ListTraversing(LinkedList);
    // // 按位置修改
    // LinkedListUpdate(LinkedList, 5, 223153, "tianhu", 23);
    // printf("\nupdate by pos:");
    // ListTraversing(LinkedList);
    // 就地逆置
    LinkedListReverse(LinkedList);
    printf("\nreverse the init list:");
    ListTraversing(LinkedList);
    // 单链表快速排序
    printf("\nafter sort:");
    LinkedListQuickSort(LinkedList, NULL);
    ListTraversing(LinkedList);
    // 插入有序链表
    SortedLinkedListInsert(LinkedList, 324299, "wuxang", 18);
    printf("\ninsert value to sorted list :");
    ListTraversing(LinkedList);
    //去重
    printf("\nDeduplication :");
    LinkedListDeduplication(LinkedList);
    ListTraversing(LinkedList);
    // 创建一个新的链表并递增排序
    ListNodePtr LinkedListSort = LinkedListInit();
    printf("\nbefore sort:");
    ListTraversing(LinkedListSort);
    LinkedListQuickSort(LinkedListSort, NULL);
    printf("\nafter sort:");
    ListTraversing(LinkedListSort);
    // 将两个递增有序单链表合并为一个新的有序链表
    ListNodePtr unionLinkedList = LinkedListUnion(LinkedListSort, LinkedList);
    printf("\nunion:");
    ListTraversing(unionLinkedList);
    //去重
    printf("\nDeduplication :");
    LinkedListDeduplication(unionLinkedList);
    ListTraversing(unionLinkedList);
    return 0;
}
