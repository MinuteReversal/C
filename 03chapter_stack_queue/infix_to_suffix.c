/******************************************************************************
* fileName    : calc.c 
* author      : 114233763@qq.com
* date        : 2020-09-09 13:24:58
* description : 中缀表达式转后缀表达式
 \ p2
P1\   |+|-|*|/|(|)|@|
+      > > < < < > > 
-      > > < < < > >
*      > > > > < > >
/      > > > > < > >
(      < < < < < =  
)      > > > >   > >
@      < < < < <   =
***************************************************************************** */
#include <stdio.h>
#include <malloc.h>
#define SYMBOLS_LENGTH 7
#define NUMBERS_LENGTH 10

//数学符号
char symbols[SYMBOLS_LENGTH] = {'+', '-', '*', '/', '(', ')', '@'};
//数字符号
char numbers[NUMBERS_LENGTH] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
//运算符优先级
char precedence[SYMBOLS_LENGTH][SYMBOLS_LENGTH] = {
    //p1\p2   +    -    *    /    (    )    @
    /* + */ {'>', '>', '<', '<', '>', '<', '>'},
    /* - */ {'>', '>', '<', '<', '>', '<', '>'},
    /* * */ {'>', '>', '>', '>', '>', '<', '>'},
    /* / */ {'>', '>', '>', '>', '>', '<', '>'},
    /* ( */ {'<', '<', '<', '<', '<', '=', ' '},
    /* ) */ {'>', '>', '>', '>', ' ', '>', '>'},
    /* @ */ {'<', '<', '<', '<', '<', ' ', '='},
};

/**
* @struct 栈节点
*/
typedef struct _StackNode
{
    int value;
    struct _StackNode *next;
} StackNode, *PStackNode;

/**
* 创建节点
* @param value 值
* @param next 下一个节点地址
* @return 创建的节点
*/
PStackNode create(int value, PStackNode next)
{
    PStackNode node = (PStackNode)malloc(sizeof(StackNode));
    node->next = next;
    node->value = value;
    return node;
}

/**
* 进栈
* @param stack 栈
* @param  value 值
* @return 栈顶
*/
PStackNode push(PStackNode stack, int value)
{
    PStackNode node = create(value, stack);
    return node;
}

/**
* 出栈
* @param stack 栈
* @param value 值
* @return 栈顶
*/
PStackNode pop(PStackNode stack, int *value)
{
    if (stack->next != NULL)
    {
        PStackNode next = stack->next;
        *value = stack->value;
        free(stack);
        return next;
    }
    return stack;
}

/**
* 找索引
* @param array 数组
* @param length 数组长度
* @return index -1 没找到 >-1 为找到
*/
int findIndexByChar(char *array, int length, char c)
{
    for (size_t i = 0; i < length; i++)
    {
        if (array[i] == c)
        {
            return i;
        }
    }
    return -1;
}

/**
* 获取优先级
* @param p1 操作符1
* @param p2 操作符2
* @return 优先关系 >< =
*/
char getPrecedence(char p1, char p2)
{
    int p1Index = findIndexByChar(symbols, SYMBOLS_LENGTH, p1);
    int p2Index = findIndexByChar(symbols, SYMBOLS_LENGTH, p2);
    return precedence[p1Index][p2Index];
}

/**
* 空栈
* @param stack 栈
* @return 0 非空 1 空
*/
int isEmpty(PStackNode stack)
{
    return stack->next == NULL;
}

/**
* 是否为数字
* @param c 字符 
* @return  0 否 1 是
*/
int isNumber(char c)
{
    return findIndexByChar(numbers, 11, c) > 0;
}

/**
* 是否为符号
* @param c 符号 
* @return 0 否 1 是
*/
int isSymbol(char c)
{
    return findIndexByChar(symbols, 7, c) > 0;
}

/**
* 计算
* @param numberStack 数字栈 
* @param symbolStack 符号栈
* @return 无
*/
void exitToBrack(PStackNode *symbolStack)
{
    int value;
    while ((*symbolStack)->value != (int)'(')
    {
        *symbolStack = pop(*symbolStack, &value);
        printf("%c ", value);
    }
    *symbolStack = pop(*symbolStack, &value);
}

/**
* 退出栈顶元素并打印
* @param symbolStack 栈顶
* @return 栈顶
*/
PStackNode exitAndPrint(PStackNode symbolStack)
{
    //退栈顶元素
    int value;
    symbolStack = pop(symbolStack, &value);
    printf("%c ", value);
    return symbolStack;
}

/**
* 计算
* @param str 字符串
* @param length 字符串长度
* @return 无
*/
void scanInput(char *input, int length)
{
    PStackNode numberStack = create(-1, NULL);
    PStackNode symbolStack = create(-1, NULL);
    symbolStack = push(symbolStack, '@');

    int result;
    //遍历字符串中的每个字符
    for (size_t i = 0; i < length; i++)
    {
        char c = input[i];
        if (isNumber(c))
        {
            printf("%d ", atoi(&c));
        }
        else if (c == '(')
        {
            //左括号进栈
            symbolStack = push(symbolStack, c);
        }
        else if (c == ')')
        {
            //退到括号为止
            exitToBrack(&symbolStack);
            symbolStack = exitAndPrint(symbolStack);
        }
        else if (getPrecedence(c, symbolStack->value) == '>')
        {
            //大就进栈
            symbolStack = push(symbolStack, c);
        }
        else if (getPrecedence(c, symbolStack->value) == '<')
        {
            symbolStack = exitAndPrint(symbolStack);
        }
        else if (getPrecedence(c, symbolStack->value) == '=')
        {
            //相等退一次栈
            int symbol;
            symbolStack = pop(symbolStack, &symbol);
        }
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    char *input = "2*(3+5)/(6-4)@";
    int length = 14;

    scanInput(input, length);
    return 0;
}