#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

// C++ Program for Implementation of linked list
#include <iostream>
using namespace std;

// Structure for a node in the linked list
struct linkedNode {
    int data;  
    linkedNode* next; 
};

// Define the linked list class
class LinkedList {
     // Pointer to the first node in the list
    linkedNode* head;

public:
    // Constructor initializes head to NULL
    LinkedList() : head(NULL) {}

    // Function to Insert a new node at the beginning of the list
    void insertAtBeginning(int value) {
        linkedNode* newNode = new linkedNode(); 
        newNode->data = value;      
        newNode->next = head;      
        head = newNode;            
    }

    // Function Insert a new node at the end of the list
    void insertAtEnd(int value) {
        linkedNode* newNode = new linkedNode(); 
        newNode->data = value;      
        newNode->next = NULL;       

        // If the list is empty, update the head to the new node
        if (!head) {
            head = newNode;
            return;
        }

        // Traverse to the last node
        linkedNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }

        // Update the last node's next to the new node
        temp->next = newNode;
    }

    // Function to Insert a new node at a specific position in the list
    void insertAtPosition(int value, int position) {
        if (position < 1) {
            return;
        }

        if (position == 1) {
            insertAtBeginning(value);
            return;
        }

        linkedNode* newNode = new linkedNode(); 
        newNode->data = value;     

        // Traverse to the node before the desired position
        linkedNode* temp = head;
        for (int i = 1; i < position - 1 && temp; ++i) {
            temp = temp->next;
        }

        // If the position is out of range, print an error message
        if (!temp) {
            delete newNode;
            return;
        }

        // Insert the new node at the desired position
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Function to Delete the first node of the list
    void deleteFromBeginning() {
        if (!head) {
            return;
        }

        linkedNode* temp = head; 
        head = head->next; 
        delete temp;      
    }

    // Function to Delete the last node of the list
    void deleteFromEnd() {
        if (!head) {
            return;
        }

        if (!head->next) {
            delete head;   
            head = NULL;   
            return;
        }

        // Traverse to the second-to-last node
        linkedNode* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        
        //  Delete the last node
        delete temp->next; 
        // Set the second-to-last node's next to NULL
        temp->next = NULL; 
    }

    // Function to Delete a node at a specific position in the list
    void deleteFromPosition(int position) {
        if (position < 1) {
            return;
        }

        if (position == 1) {
            deleteFromBeginning();
            return;
        }

        linkedNode* temp = head;
        for (int i = 1; i < position - 1 && temp; ++i) {
            temp = temp->next;
        }

        if (!temp || !temp->next) {
            return;
        }
        // Save the node to be deleted
        linkedNode* nodeToDelete = temp->next; 
        // Update the next pointer
        temp->next = temp->next->next;   
         // Delete the node
        delete nodeToDelete;            
    }

    // Function to print the nodes of  the linked list
    void display() {
        if (!head) {
            return;
        }

        linkedNode* temp = head;
        while (temp) {
            temp = temp->next;
        } 
    }

    linkedNode* getHead() {
        return head; // Return the head node of the list
    }
};

#endif