#include <stdio.h>
#include <malloc.h>

/*
* 定义节点类型
*/
typedef struct _Node
{
    int value;
    struct _Node *next;
}
/**
*节点类型
*/
Node,
/**
 * 节点指针类型
 */
*PNode;

/**
 * 向后添加一个元素
 */
PNode insertAfter(PNode node, int value)
{
    PNode nextNode = (PNode)malloc(sizeof(Node));
    nextNode->value = value;
    nextNode->next = NULL;
    if (node)
    {
        if (node->next)
        {
            nextNode->next = node->next;
        }

        node->next = nextNode;
    }
    return nextNode;
}

/**
* 初始化
* @param length 表长度
* @param baseValue 起始值
* @return 表头节点地址
*/
PNode init(int length, int baseValue)
{
    PNode head = insertAfter(NULL, baseValue);
    PNode node = head;
    for (int i = baseValue + 1; i < length + baseValue; i++)
    {
        node = insertAfter(node, i);
    }
    return head;
}

/**
 * 获取最后一个节点
 */
PNode getEnd(PNode head)
{
    PNode node = head;
    while (node->next)
    {
        node = node->next;
    }
    return node;
}

/**
 * 通过值查找节点
 */
PNode findByValue(PNode head, int value)
{
    for (PNode node = head; node != NULL; node = node->next)
    {
        if (value == node->value)
        {
            return node;
        }
    }
    return NULL;
}

/**
 * 通过索引查找
 */
PNode findByIndex(PNode head, int index)
{
    PNode node = head;
    for (int i = 0; node; i++, node = node->next)
    {
        if (index == i)
        {
            return node;
        }
    }

    return NULL;
}

/**
 * 清除所有节点
 */
void clear(PNode head)
{
    PNode node = head;
    while (node)
    {
        PNode next = node->next;
        free(node);
        node = next;
    }
}

/**
* 删除指定节点后的节点
* 
* @param head 列表 
* @param priorNode 指定的节点
* @return 无
*/
void removeAfter(PNode head, PNode priorNode)
{
    PNode currentNode = priorNode->next;      //要删除的节点
    PNode removeNodeNext = currentNode->next; //要删除的节点的下一个节点

    if (currentNode)
    {
        free(currentNode); //删除当前节点
    }
    if (removeNodeNext)
    {
        priorNode->next = removeNodeNext;
    }
}

/**
 * 删除指定值的节点
 */
void removeByValue(PNode head, int value)
{
    for (PNode node = head; node; node = node->next)
    {
        PNode nextNode = node->next;
        if (nextNode->value == value)
        {
            removeAfter(head, node);
            break;
        }
    }
}

/**
* 打印单个节点的值
* @param node 指定节点
* @return 无 
*/
void printNode(PNode node)
{
    printf("%d,", *node);
}

/**
* 打印链表里的每一个值
* @param head 表头元素
* @return 无 
*/
void printLinkList(PNode head)
{
    for (PNode node = head; node != NULL; node = node->next)
    {
        printNode(node);
    }
    printf("\n");
}

/**
 * 拼接两个链表
 * @param listA 表A
 * @param listB 表B
 * @return 无
 */
void connect(PNode listA, PNode listB)
{
    PNode listAEnd = getEnd(listA);
    listAEnd->next = listB;
}

int main(int argc, char const *argv[])
{
    PNode list1 = init(10, 0);
    PNode list2 = init(10, 10);

    connect(list1, list2);
    printLinkList(list1);

    clear(list1);
    return 0;
}