// ---
// title: 🐈homework-2022-09-18
// date: 2022-09-18 00:05:03
// tags: DS
// rating: ⭐️
// excerpt:实现顺序表的合并，给定两个顺序表LA和LB，要求将LB中的元素合并到LA中，并确保合并后LA的元素不重复
// ---

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;


typedef struct {
    ElemType *data;
    int length;
    int capacity;
} TList;


//initialize linear list
TList * list_init (int num) {
    TList *p = (TList *) malloc(sizeof(TList));
    if( !p ){
        printf("list_init error");
        exit(0);
    }
    p->length = 0;
    p->capacity = num;
    int nsize = sizeof(ElemType) * num;
    p->data = (ElemType*) malloc(nsize);
    if( !p->data ) {
        printf("list_init error");
        free(p);
        exit(0);
    }
    return p;
}

//destroy linear list
void list_destroy(TList * p){
    if( p ) {
            if( p->data ) {
            free(p->data);
            }
        free(p);
    }
}

//Get sepcific element Bi of LB
ElemType get_item(TList* L, int idx){
    if((idx >= 0) && (idx < L->length)){
        return L->data[idx];
    }
    else{
        printf("invaild position of elements");
        exit(0);
    }
}

//boolean check if Bi exists in LA
int list_locate (TList* L, ElemType e) {
    int id = 0;
    while ((id < L->length)&&( e != L->data[id]))
        id++;
        if (id < L->length) return 1;
    else{
        printf("element no existing");
        return 0;
    }
}

//insert element in sepcific index
int list_insert(TList *L, int idx, ElemType e) {
    int i, n = L->length;
    if (n >= L->capacity){
        return 1;   //no space for insertion
    }
    else if ((idx< 0) || ( idx > n)){
        return -1;//invaild index
    }
    else {
        for( i = n; i > idx; --i ) {
            L->data[i] = L->data[i-1];  //move element rightward
        }
        L->data[idx] = e;  //duplicate elements
        L->length ++;   //fix length
    }
    return 0;
}

//extract element in sepcific index
int list_extract(TList *L, int idx, ElemType e) {
    int i, n = L->length;
    if (n >= L->capacity){
        return 1;   //no space for insertion
    }
    else if ((idx< 0) || ( idx > n)){
        return -1;//invaild index
    }
    else {
        for( i = idx; i < n; ++i ) {
            L->data[i] = L->data[i+1];  //move element leftward
        }
        L->length --;   //fix length
    }
    return 0;
}

//merge two list
int list_merge (TList* La, TList * Lb){
    ElemType e; int idx, status, lena, capa, i, j, n = Lb->length;
    lena = La->length;
    capa = La->capacity;
    if ((!La) || (!Lb))
    {
        printf("invaild linear lists");
        exit(0);
    }
    else if ((lena + n)>capa){
        printf("no enough space for merging");
        exit(0);
    }
    else{
    for ( i = 0; i < n; ++i ){
        e = get_item(Lb, i);
        idx = list_locate(La, e);
        if( !idx ){
            status = list_insert(La, 0, e);
        if(status) {
            printf("error when inserting element");
            exit(0);
        }
        }
    }
    list_destroy(Lb);
    return status;
    }
}

///
void creatlist( TList *La)
{
    if( !La ){
        printf("list_init error");
        exit(0);
    }
    else
    {
    int i, n;
    printf("input number of element:");
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
        printf("input the %d th of elements: ", i);
        scanf("%d",&La->data[i]);
        La->length++;
    }
    }
}

//viusalize list
void viusallist(TList *La){
    if( !La ){
        printf("list_init error");
        exit(0);
    }
    else
    {
        int n;
        n = La->length;
        printf("\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d  ", La->data[i]);
        }
        printf("\n");
    }
}


int main(){
    TList *La, *Lb;
    La = list_init(10);
    Lb = list_init(3);
    creatlist(La);
    viusallist(La);
    creatlist(Lb);
    viusallist(Lb);
    list_merge(La, Lb);
    viusallist(La);
    return 0;
}