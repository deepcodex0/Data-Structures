/**
430. Flatten a Multilevel Doubly Linked List
https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/description/?envType=company&envId=bloomberg&favoriteSlug=bloomberg-thirty-days
You are given a doubly linked list, which contains nodes that have a next pointer, a previous pointer, and an additional child pointer. This child pointer may or may not point to a separate doubly linked list, also containing these special nodes. These child lists may have one or more children of their own, and so on, to produce a multilevel data structure as shown in the example below.

Given the head of the first level of the list, flatten the list so that all the nodes appear in a single-level, doubly linked list. Let curr be a node with a child list. The nodes in the child list should appear after curr and before curr.next in the flattened list.

Return the head of the flattened list. The nodes in the list must have all of their child pointers set to null.
Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
Output: [1,2,3,7,8,11,12,9,10,4,5,6]
 */

#include <iostream>
#include <vector>
using namespace std;

class Node {
 public:
     int val;
     Node* prev;
     Node* next;
     Node* child;

     // Constructor for easy creation
    Node(int _val) {
        val = _val;
        prev = nullptr;
        next = nullptr;
        child = nullptr;
    }
 };

Node* flatten_dfs(Node* curr) {
    Node* last = curr;

    while(curr) {
        Node* nextPtr = curr->next;

        if(curr->child) {
            Node* childTail = flatten_dfs(curr->child);

            curr->next = curr->child;
            curr->child->prev = curr;

            if(nextPtr) {
                nextPtr->prev = childTail;
            }

            childTail->next = nextPtr;

            curr->child = nullptr;
            last = childTail;
        } else {
            last = curr;
        }

        curr = nextPtr;
    }

    return last;

}

Node* flatten(Node* head) {
        if (!head) return nullptr;
        flatten_dfs(head);
        return head;
}

// Helper function to print the list
void printList(Node* head) {
    if (!head) return;
    cout << "Result: ";
    while (head) {
        cout << head->val;
        if (head->next) cout << " <-> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // --- Step 1: Create Nodes ---
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);
    Node* n9 = new Node(9);
    Node* n10 = new Node(10);
    
    Node* n11 = new Node(11);
    Node* n12 = new Node(12);

    // --- Step 2: Link Level 1 (1-2-3-4-5-6) ---
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;
    n3->next = n4; n4->prev = n3;
    n4->next = n5; n5->prev = n4;
    n5->next = n6; n6->prev = n5;

    // --- Step 3: Link Level 2 (7-8-9-10) and attach to Node 2 ---
    n2->child = n7; // Parent 2 has child 7
    
    n7->next = n8; n8->prev = n7;
    n8->next = n9; n9->prev = n8;
    n9->next = n10; n10->prev = n9;

    // --- Step 4: Link Level 3 (11-12) and attach to Node 8 ---
    n8->child = n11; // Parent 8 has child 11

    n11->next = n12; n12->prev = n11;

    // --- Step 5: Run Solution ---
    cout << "Original structure created..." << endl;
    
    Node* newHead = flatten(n1);

    // --- Step 6: Verify Output ---
    // Expected: 1 <-> 2 <-> 7 <-> 8 <-> 11 <-> 12 <-> 9 <-> 10 <-> 3 <-> 4 <-> 5 <-> 6
    printList(newHead);

    return 0;
}