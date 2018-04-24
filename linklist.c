#include "linklist.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void LinkListInit(LinkNode** head)
{
    //条件为假的时候中断程序并给出错误
    assert(head);
    *head = NULL;
}

LinkNode* CreateLinkNode(LinkType value)
{
    LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

LinkNode* LinkListPushBack(LinkNode** head,LinkType value)
{
    assert(head);
    LinkNode* new_node = CreateLinkNode(value);
    if(*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        LinkNode* cur = *head;
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = new_node;
    }
    return new_node;
}

void DeleteLinkNode(LinkNode* node)
{
    free(node);
}

void RemoveLinkNode(LinkNode** head,LinkNode* delete_node)
{
    assert(head);
    if(*head == NULL || delete_node == NULL)
    {
        return;
    }
    //被删除的节点是头结点
    if(delete_node == *head)
    {
        //如果只有一个节点,那么头结点就指向空
        //如果不止一个节点,那么头结点就指向要删除节点的下一个节点
        *head = delete_node->next;
        DeleteLinkNode(delete_node);
        return;
    }
    //被删除的节点是尾节点并且链表中不止有有一个节点,这时候需要遍历链表,找到这个节点的前一个节点
    if(delete_node->next == NULL)
    {
        LinkNode* pre = *head;
        while(pre->next != delete_node)
        {
            pre = pre->next;
        }
        pre->next = NULL;
        DeleteLinkNode(delete_node);
        return;
    }
    //正常情况:要删除的节点不是头结点也不是尾节点,这时候链表一定是多于两个节点的
    //我们使用移花接木的方法:将要删除的节点的内容改变为他的下一个节点的内容
    //                       让要删除的节点指向下一个节点的下一个节点
    //                       删除要删除节点的下一个节点
    delete_node->data = delete_node->next->data;
    delete_node->next = delete_node->next->next;
    delete_node = delete_node->next;
    DeleteLinkNode(delete_node);
}

void RemoveRepetNode(LinkNode** head)
{
    assert(head);
    if(*head == NULL)
    {
        return;
    }
    if((*head)->next == NULL)
    {//只有一个节点的时候不需要删除
        return;
    }
    LinkNode* pre = *head;
    while(pre != NULL && pre->next != NULL)
    {
        LinkNode* cur = pre->next;
        if(pre->data == cur->data)
        {
            pre->next = cur->next;
            DeleteLinkNode(cur);
        }
        else
        {
            pre = cur;
        }
    }
    return;
}

LinkNode* FindKthToTail(LinkNode** head,int K)
{
    assert(head);
    if(*head == NULL)
    {
        return NULL;
    }
    if(K <= 0)
    {
        return NULL;
    }
    LinkNode* node = *head;
    int i = 1;
    //先让这个指针走 K-1 步
    for(; i <= K - 1; ++i)
    {
        if(node->next != NULL)
        {
            node = node->next;
        }
        else
        {//证明没有倒数第K个节点
            return NULL;
        }
    }
    LinkNode* Knode = *head;
    while(node->next != NULL)
    {
        node = node->next;
        Knode = Knode->next;
    }
    return Knode;
}

LinkNode* HasCycle(LinkNode* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    LinkNode* slow = head->next;
    if(slow == NULL)
    {
        return NULL;
    }
    LinkNode* fast = slow->next;
    while(fast != NULL && fast->next != NULL)
    {
        if(fast == slow)
        {
            return fast;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    return NULL;
}

int CycleLenth(LinkNode* point)
{
    int count = 1;
    LinkNode* cur = point->next;
    while(cur != point)
    {
        cur = cur->next;
        ++count;
    }
    return count;
}

LinkNode* Entry(LinkNode* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    //1.判断当前的链表带不带环
    LinkNode* point = HasCycle(head);
    if(point == NULL)
    {
        return NULL;
    }
    //2.如果带环求出环的长度
    int len = CycleLenth(point);
    //3.定义两个指针,快指针先走环的长度个节点,慢指针再从头结点开始走,两个指针相交的时候就是当前链表环的入口点
    LinkNode* fast = head;
    LinkNode* slow = head;
    while(len--)
    {
        fast = fast->next;
    }
    while(fast != slow)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

LinkNode* Reverse(LinkNode* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    LinkNode* new_head = head;
    LinkNode* cur = head;
    LinkNode* pre = NULL;
    while(cur != NULL)
    {
        LinkNode* next = cur->next;
        if(next != NULL)
        {
            new_head = next;
        }
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return new_head;
}

LinkNode* Merge(LinkNode* head1,LinkNode* head2)
{
    if(head1 == NULL)
    {
        return head2;
    }
    else if(head2 == NULL)
    {
        return head1;
    }
    LinkNode* new_head = NULL;
    if(head1->data < head2->data)
    {
        new_head = head1;
        new_head->next = Merge(head1->next,head2);
    }
    else
    {
        new_head = head2;
        new_head->next = Merge(head1,head2->next);
    }
    return new_head;
}

size_t ListLength(LinkNode* head)
{
    if(head == NULL)
    {
        return 0;
    }
    LinkNode* cur = head;
    size_t length = 0;
    while(cur != NULL)
    {
        cur = cur->next;
        ++length;
    }
    return length;
}

LinkNode* FindFirstCommentNode(LinkNode* head1,LinkNode* head2)
{
    if(head1 == NULL || head2 == NULL)
    {
        return NULL;
    }
    size_t len1 = ListLength(head1);
    size_t len2 = ListLength(head2);
    size_t len = len1 - len2;
    LinkNode* quick = head1;
    LinkNode* slow = head2;
    if(len2 > len1)
    {
        len = len2 - len1;
        quick = head2;
        slow = head1;
    }
    while(len-- && quick != NULL)
    {
        quick = quick->next;
    }
    while(quick != NULL && slow != NULL)
    {
        if(quick == slow)
        {
            return quick;
        }
        quick = quick->next;
        slow = slow->next;
    }
    return NULL;
}

/////////////////////////////////////////////
// 测试代码
/////////////////////////////////////////////

#if 1

#define TEST_HEADER printf("\n~~~~~~~~~~~%s~~~~~~~~~~~\n",__FUNCTION__)

void PrintLink(LinkNode* head)
{
    LinkNode* cur = head;
    while(cur != NULL)
    {
        printf("%d[%p] -> ",cur->data,cur);
        cur = cur->next;
    }
    printf("NULL\n");
}

void TestInit_Pushback()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,1);
    LinkListPushBack(&head,2);
    LinkListPushBack(&head,3);
    LinkListPushBack(&head,4);
    PrintLink(head);
}

void TestDeleteNode()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,1);
    LinkListPushBack(&head,2);
    LinkListPushBack(&head,3);
    LinkListPushBack(&head,4);
    RemoveLinkNode(&head,head);
    PrintLink(head);
    RemoveLinkNode(&head,head->next);
    PrintLink(head);
    RemoveLinkNode(&head,head->next);
    PrintLink(head);
    RemoveLinkNode(&head,head);
    PrintLink(head);
}

void TestRemoveRepet()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,1);
    LinkListPushBack(&head,1);
    LinkListPushBack(&head,2);
    LinkListPushBack(&head,2);
    LinkListPushBack(&head,3);
    LinkListPushBack(&head,3);
    PrintLink(head);
    RemoveRepetNode(&head);
    PrintLink(head);
}

void TestFindKToTail()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,1);
    LinkListPushBack(&head,2);
    LinkListPushBack(&head,3);
    LinkListPushBack(&head,4);
    LinkListPushBack(&head,5);

    LinkNode* ret = FindKthToTail(&head,1);
    printf("expect 5,actual %d\n",ret->data);

    ret = FindKthToTail(&head,5);
    printf("expect 1,actual %d\n",ret->data);

    ret = FindKthToTail(&head,3);
    printf("expect 3,actual %d\n",ret->data);

    ret = FindKthToTail(&head,8);
    printf("expect NULL,actual %p\n",ret);

    ret = FindKthToTail(&head,0);
    printf("expect NULL,actual %p\n",ret);
}

void TestEntry()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,1);
    LinkListPushBack(&head,2);
    LinkListPushBack(&head,3);
    LinkNode* pos_entry = LinkListPushBack(&head,4);
    LinkListPushBack(&head,5);
    LinkListPushBack(&head,6);
    LinkListPushBack(&head,7);
    LinkNode* pos = LinkListPushBack(&head,8);
    pos->next = pos_entry;
    LinkNode* entry = Entry(head);
    printf("entry expect 4,%p;actual %d,%p\n",pos_entry,entry->data,entry);
}

void TestReverse()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,1);
    LinkListPushBack(&head,2);
    LinkListPushBack(&head,3);
    LinkListPushBack(&head,4);
    PrintLink(head);
    LinkNode* new_head = Reverse(head);
    PrintLink(new_head);
}

void TestMerge()
{
    TEST_HEADER;
    LinkNode* head1;
    LinkListInit(&head1);
    LinkListPushBack(&head1,1);
    LinkListPushBack(&head1,4);
    LinkListPushBack(&head1,5);
    LinkListPushBack(&head1,9);
    LinkNode* head2;
    LinkListInit(&head2);
    LinkListPushBack(&head2,2);
    LinkListPushBack(&head2,3);
    LinkListPushBack(&head2,6);
    LinkListPushBack(&head2,8);
    LinkNode* new_head = Merge(head1,head2);
    PrintLink(new_head);
}

void TestFindFirstCommentNode()
{
    TEST_HEADER;
    LinkNode* head1;
    LinkListInit(&head1);
    LinkListPushBack(&head1,1);
    LinkListPushBack(&head1,2);
    LinkListPushBack(&head1,3);
    LinkNode* pos4 = LinkListPushBack(&head1,4);
    LinkListPushBack(&head1,5);

    LinkNode* head2;
    LinkListInit(&head2);
    LinkListPushBack(&head2,100);
    LinkNode* pos200 = LinkListPushBack(&head2,200);
    pos200->next = pos4;
    LinkNode* comment_node = FindFirstCommentNode(head1,head2);
    printf("comment node expect 4,%p; actual %d,%p\n",pos4,comment_node->data,comment_node);
}

int main()
{
    TestInit_Pushback();
    TestDeleteNode();
    TestRemoveRepet();
    TestFindKToTail();
    TestEntry();
    TestReverse();
    TestMerge();
    TestFindFirstCommentNode();
    return 0;
}
 
#endif
