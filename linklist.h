#pragma once
#include <stddef.h>

typedef int LinkType;

typedef struct LinkNode
{
    LinkType data;
    struct LinkNode* next;
}LinkNode;

void LinkListInit(LinkNode** head);

LinkNode* LinkListPushBack(LinkNode** head,LinkType value);

//删除链表节点 18
void RemoveLinkNode(LinkNode** head,LinkNode* delete_node);
//在排序链表中删除链表中重复的节点
void RemoveRepetNode(LinkNode** head);

//找到倒数第K个节点 22
LinkNode* FindKthToTail(LinkNode** head,int K);

//链表中环的入口点 23
LinkNode* Entry(LinkNode* head);

//反转链表 24
LinkNode* Reverse(LinkNode* head);

//合并两个有序链表 25
LinkNode* Merge(LinkNode* head1,LinkNode* head2);

//两个链表的第一个公共节点
LinkNode* FindFirstCommentNode(LinkNode* head1,LinkNode* head2);

//求两个链表长度
size_t ListLength(LinkNode* head);
