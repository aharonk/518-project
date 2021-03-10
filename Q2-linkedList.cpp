//
//  linkedList.cpp
//  algorithms
//
#ifndef linkedList_cpp
#define linkedList_cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
  
struct Node
{
    int data;
    Node *next;
};

class LinkedList
{
public:
    Node *head,*tail;
public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    void newNode(int n) {
        Node *tmp = new Node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL) {
            head = tmp;
            tail = tmp;
        } else {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    
    struct Node* middle(Node* start, Node* last) {
        if (start == NULL)
            return NULL;
      
        struct Node* back = start;
        struct Node* front = start -> next;
      
        while (front != last) {
            front = front -> next;
            if (front != last) {
                back = back -> next;
                front = front -> next;
            }
        }
        return back;
    }
    
   
    bool binarySearch(Node *head, int value) {
        struct Node* start = head;
        struct Node* last = NULL;
      
        do {
            // middle node
            Node* mid = middle(start, last);
            if (mid == NULL)
                return false;
            if (mid -> data == value)
                return true;
            else if (mid -> data < value)
                start = mid -> next;
            else
                last = mid;
      
        } while (last == NULL || last != start);
        
        return false;
    }
};

#endif /* linkedList_cpp */
