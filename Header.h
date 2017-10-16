#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
	int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
	int serviceTime; //Random time; varies between express and normal lanes; units in minutes
	int totalTime; //totalTime = serviceTime +sum of serviceTimes of customers in line before this customer; units in minutes
}Data; //This memory needs to be allocated on the heap!

typedef struct queueNode
{
	Data *pData; // The memory for Data will need to be allocated on the heap as well!
	struct queueNode *pNext;
} QueueNode;

typedef struct queue
{
	QueueNode *pHead;
	QueueNode *pTail;
} Queue;

typedef enum boolean
{
	False, True
}Boolean;

//contains all the code for the program
void Run_App(void);

//makes a new QueueNode and returns the pointer to the memory in the heap.
QueueNode * makeNode(Data newData);

//takes the input as the struct Queue and the Data required to create a new node for the queue and it to the start of the queue.
int enqueue(Queue *pQ, Data newData);

//prints the data which resides within each node of the Q till the Node's pNext = NULL
void printQueue(Queue Q);

//returns true if the queue is empty or else false
Boolean isEmpty(Queue Q);

//deletes the node at the end of the queue.
int dequeue(Queue *pQ);

//Calculates the total time before the customer departs.
int TotalTimeCalculator(Queue Q);

#endif // !HEADER_H

