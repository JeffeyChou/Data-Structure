// ---
// title: 霍夫曼编码
// date: 2022-11-18 22:26:19
// excerpt:
// tags: Data_Structure Huffman
// rating: ⭐
// status: Complete
// share: false
// ---

// 1. 从文本文件读入英文字符串
// 2. 针对读入的字符串，设计算法统计不同字符在该字符串中出现的次数（字符要区分大小写）
// 3. 实现哈夫曼树的构建算法
// 4. 遍历哈夫曼树生成每个字符的二进制编码
// 5. 显示输出每个字母的编码
// 6. 对编码后的字符串进行解码
// 7. 对解码后的字符串与原串进行比较（选做）
// 8. 独立完成实验报告

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXNUM 2000
#define MAXBIT 50

// Huffman树的节点结构定义
typedef struct
{
    int weight;
    char ch;
    int lchild, rchild, parent;
} TNode, *PHT;

// Huffman编码表的元素结构定义
typedef struct
{
    char ch; // 编码对应的字符
    int bit[MAXBIT];
    int start;
} TCode, *PCode;

// 从文本文件 filename 读入字符串，保存到数组 message 中
int read_file(char *filename, char message[])
{

    int slen;
    FILE *pFile = NULL;

    // 打开文件
    pFile = fopen(filename, "r");
    if (!pFile)
    {
        printf("read_file(): 打开文件%s失败!\n", filename);
        exit(0);
    }
    else
    {
        printf("read_file(): 成功打开文件%s!\n", filename);
    }

    // 对缓冲区清零（准备从文件读入字符串）
    memset(message, 0, MAXNUM);

    if (fgets(message, MAXNUM, pFile) == NULL)
    {
        printf("fgets error\n");
        exit(0);
    }
    else
    {
        printf("%s", message);
    }

    slen = strlen(message);
    fclose(pFile);

    printf("read_file(): 成功读入文件%s!\n", filename);

    return slen;
}

// 统计字符串text中字符出现的频率，参数n为字符串长度
// 返回值为：text中出现的不同种类的字符个数
// 副作用：通过指针参数间接返回两个数组，其中：
//		dict：字符数组，存放 text中出现的不同种类的字符
//		freq：整型数组，存放 text中出现的不同种类的字符的出现频率
int calc_freq(char text[], int **freq, char **dict, int n)
{
    int i, k, nchar = 0;
    int *pwght;
    char *pch;
    int tokens[256] = {0};

    // 根据输入的文本字符串逐一统计字符出现的频率
    for (i = 0; i < n; ++i)
    {
        tokens[text[i]]++;
    }

    // 统计共有多少个相异的字符出现在文本串中
    for (i = 0; i < 256; i++)
    {
        if (tokens[i] > 0)
        {
            nchar++;
        }
    }

    // 为权重数组分配空间
    pwght = (int *)malloc(sizeof(int) * (nchar + 1));
    if (!pwght)
    {
        printf("为权重数组分配空间失败！\n");
        exit(0);
    }

    // 为字符数组（字典）分配空间
    pch = (char *)malloc(sizeof(char) * (nchar + 1));
    if (!pch)
    {
        printf("为字符数组（字典）分配空间失败！\n");
        exit(0);
    }

    k = 0;
    for (i = 0; i < 256; ++i)
    {
        if (tokens[i] > 0)
        {
            pwght[k] = tokens[i];
            pch[k] = (char)i; // 强制类型转换
            k++;
        }
    }

    *freq = pwght;
    *dict = pch;

    return nchar;
}

// 创建Huffman树， 传入Huffman树节点，Huffman编码表节点，权重表， 对应的字符， 编码的字符的长度
void CreatHuffmanTree(TNode *HT, TCode *HC, int weight[], char dict[], int size)
{
    int i;
    int min1, min2;
    int N = size;
    int M = 2 * size - 1;
    printf("正在创建Huffman树, 请稍后。。。\n\n");
    // 初始化用于储存编码的节点
    for (i = 0; i < N; i++)
    {
        HT[i].weight = weight[i];
        HT[i].ch = dict[i];
        HC[i].ch = dict[i];
        HT[i].parent = -1;
        HT[i].lchild = HT[i].rchild = -1;
    }
    // 初始化连接用的root节点
    for (i = N; i < M; i++)
    {
        HT[i].weight = 0;
        HT[i].parent = -1;
        HT[i].lchild = HT[i].rchild = -1;
    }

    for (int k = N; k < M; k++)
    {
        min1 = MAXNUM, min2 = MAXNUM; // 最小值
        int x1 = 0, x2 = 0;           // 最小值的下标
        for (int j = 0; j < k; j++)   // 找出权重值之和最小的两个值的下标
        {
            if (HT[j].parent == -1 && HT[j].weight < min1)
            {
                min2 = min1;
                x2 = x1;
                min1 = HT[j].weight;
                x1 = j;
            }
            else if (HT[j].parent == -1 && HT[j].weight < min2)
            {
                x2 = j;
                min2 = HT[j].weight;
            }
        }
        HT[x1].parent = HT[x2].parent = k;
        HT[k].lchild = x1;
        HT[k].rchild = x2;
        HT[k].weight = min1 + min2;
    }
    printf("\n\n成功创建Huffman树!\n\n");

    // 字符编码
    for (int j = 0; j < size; j++)
    {
        int start = MAXBIT - 1;
        for (int k = j, f = HT[j].parent; f != -1; k = f, f = HT[k].parent)
        {
            if (HT[f].lchild == k)
            {
                HC[j].bit[start] = 0;
                start--;
            }
            else
            {
                HC[j].bit[start] = 1;
                start--;
            }
        }
        HC[j].start = start + 1;
    }
}

// 打印编码表， Hchar是二维数组，第一个维度对应编码字符的编号， 第二个长度对应最长编码长度， charcount对应编码字符的数量
void PrintHuffmanCode(TNode *tree, TCode *code, char Hchar[][20], int charcount)
{
    printf("\t\t\t字符    权重    编码\n");
    for (int i = 0; i < charcount; i++)
    {
        printf("%d\t\t\t( %c )   %d    ", i, tree[i].ch, tree[i].weight);
        int l = 0;
        for (int t = code[i].start; t < MAXBIT; t++)
        {
            Hchar[i][l] = (char)('0' + code[i].bit[t]);
            l++;
        }
        printf("%s\n", Hchar[i]);
    }
}

// 对传入的message进行编码，
void HuffmanEncode(TCode *code, char *message, char Hchar[][20], char *str, int charcount)
{
    int i = 0;
    int time = 0;
    int key = 0;
    char keyval;
    while (message[i])
    {
        keyval = message[i];
        for (int j = 0; j < charcount; j++)
        {
            if (code[j].ch == keyval)
            {
                strcat(str, Hchar[j]); // 使用strcat 把编程append到str里面
                break;
            }
        }
        i++;
    }
    printf("%s\n", str);
}

// 对编码后的encoderstr进行解码，储存在decodestr里。
void HuffmanDecode(TNode *tree, char *encodestr, char *decodestr, int TotalSize)
{
    int ii = 0;
    int iii = 0;
    int temptop = TotalSize - 1;
    while (encodestr[ii])
    {
        while (tree[temptop].rchild != -1 && tree[temptop].lchild != -1)
        {
            if (encodestr[ii] == '1')
            {
                temptop = tree[temptop].rchild;
                ii++;
            }
            else if (encodestr[ii] == '0')
            {
                temptop = tree[temptop].lchild;
                ii++;
            }
        }
        decodestr[iii] = tree[temptop].ch;
        temptop = TotalSize - 1;
        iii++;
    }
    printf("%s", decodestr);
}

int main()
{
    char message[MAXNUM];
    int *freq;
    char *dict;
    int len = read_file("love_letter.txt", message);
    int charcount = calc_freq(message, &freq, &dict, len);
    int TotalSize = charcount * 2 - 1;
    TNode tree[TotalSize];
    TCode code[charcount];
    CreatHuffmanTree(tree, code, freq, dict, charcount);
    char Hchar[charcount][20] = {'\0'}; // 储存字符串编码
    PrintHuffmanCode(tree, code, Hchar, charcount);
    // 对message编码,这里对message里的前面七个字母编码
    char encodestr[100000]; // 储存message编码后的二进制代码
    char toencodestr[] = "Napoleon to Josephine : I have your letter";
    HuffmanEncode(code, toencodestr, Hchar, encodestr, charcount);
    char decodestr[len]; // 储存解码后的字符串
    HuffmanDecode(tree, encodestr, decodestr, TotalSize);
    return 0;
}