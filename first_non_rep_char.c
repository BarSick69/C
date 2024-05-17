#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a Node structure
typedef struct Node{
    char data; // Character data
    struct Node *next; // Pointer to the next node
    struct Node *prev; // Pointer to the previous node
}*Node;

// Define a Queue structure
typedef struct Queue{
    Node head; // Pointer to the head of the queue
    Node firstNonRepeating; // Pointer to the first non-repeating character in the queue
}*Queue;

// Function to add a character to the queue and update the frequency array
void add_character(Queue q, char c, int *freq){
    freq[(int)c]++; // Increment the frequency of the character

    // If the queue is empty, create a new node and make it the head of the queue
    if(q->head == NULL){
        q->head = (Node)malloc(sizeof(struct Node));
        q->head->data = c;
        q->head->next = NULL;
        q->head->prev = NULL;
        q->firstNonRepeating = q->head; // Set the first non-repeating character to the head of the queue
        return;
    }

    // Traverse to the end of the queue
    Node tmp = q->head;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    // Add the new node to the end of the queue
    tmp->next = (Node)malloc(sizeof(struct Node));
    tmp->next->data = c;
    tmp->next->next = NULL;
    tmp->next->prev = tmp;

    // If the first non-repeating character is now repeating, find the next non-repeating character
    if(q->firstNonRepeating != NULL && freq[(int)q->firstNonRepeating->data] > 1) {
        Node tmp = q->firstNonRepeating;
        while(tmp != NULL && freq[(int)tmp->data] > 1) {
            tmp = tmp->next;
        }
        q->firstNonRepeating = tmp;
    }
}

// Function to get the first non-repeating character from the queue
char firstNonRepeating(Queue q, int *freq){
    if(q->firstNonRepeating != NULL)
        return q->firstNonRepeating->data;
    return '\0'; // Return null character if no non-repeating character is found
}

int main(){
    int *freq = (int*)calloc(256, sizeof(int)); // Initialize frequency array
    Queue q = (Queue)malloc(sizeof(struct Queue)); // Initialize queue
    q->head = NULL;
    char *string = "abcadefbac"; // Input string

    // Add each character in the string to the queue
    for(int i = 0; i < strlen(string); i++)
        add_character(q, string[i], freq);

    // Print the first non-repeating character
    printf("%c\n", firstNonRepeating(q, freq));

    // Print the frequency of each character
    for(int i = 0; i < 256; i++)
        if(freq[i] != 0)
            printf("%c %d\n", i, freq[i]);

    return 0;
}
