#include "Header.h"

/*************************************************************
* Function: QueueNode * makeNode(Data newData)
* Date Created: 3rd October 2017
* Date Last Modified: 5th October 2017
* Description: makes a node consisting of pointer to the data strict and pointer to the next QueueNode
* Input parameters: Data to be entered in the the Node
* Returns: pointer to the node where it is in the dynamic memory (heap)
* Preconditions: None
* Postconditions: gives us the pointer to the node in the heap.
*************************************************************/
QueueNode * makeNode(Data newData)
{
	QueueNode * pMem = (QueueNode *)malloc(sizeof(QueueNode));

	if (pMem != NULL)
	{
		pMem->pNext = NULL;

		pMem->pData = (Data*)malloc(sizeof(Data));

		if (pMem->pData != NULL)
		{
			pMem->pData->customerNumber = newData.customerNumber;
			pMem->pData->serviceTime = newData.serviceTime;
			pMem->pData->totalTime = newData.totalTime;
		}
	}
	return pMem;
}

/*************************************************************
* Function: int enqueue(Queue *pQ, Data newData)
* Date Created: 3rd October 2017
* Date Last Modified: 5th October 2017
* Description: accepts the pointer to the queue and the data that will go in the Node which is pushed at the first position in the Node.
* Input parameters: pointer to the Queue struct and the data that has to go into the new Node that we create
* Returns: an integer 0 to tell if the function worked successfully otherwise 1 meaning the function executed successfully
* Preconditions: None
* Postconditions: The Node with the data passed in is pointed to by the pHead of the Queue struct.
*************************************************************/
int enqueue(Queue *pQ, Data newData)
{
	int success = 0;

	QueueNode *pMem = makeNode(newData);

	if (pMem != NULL)
	{
		if (pQ->pHead == pQ->pTail == NULL)//Queue is empty
		{
			pQ->pHead = pQ->pTail = pMem;
			success = 1;
		}
		else//Queue has one or more QueueNodes.
		{
			pMem->pNext = pQ->pTail;
			pQ->pTail = pMem;
			success = 1;
		}
	}

	return success;
}

/*************************************************************
* Function: void printQueue(Queue Q)
* Date Created: 3rd October 2017
* Date Last Modified: 5th October 2017
* Description: prints the data within a node till the function is done traversing through the queue
* Input parameters: the struct Q
* Returns: nothing
* Preconditions: none
* Postconditions: prints the queue to the std out
*************************************************************/
void printQueue(Queue Q)
{
	QueueNode *pTemp = Q.pTail;

	while (pTemp != NULL)
	{
		printf("Customer Number: %d, ", pTemp->pData->customerNumber);
		printf("Service Time: %d, ", pTemp->pData->serviceTime);
		printf("Total Time: %d ", pTemp->pData->totalTime);
		printf("-----> \n");
		pTemp = pTemp->pNext;
	}
	if (pTemp == NULL)
	{
		printf("bruhhhhhhh your Queue is empty, what are you even trying to print.\n");
	}
	else
	{
		printf("\n");
	}
}

/*************************************************************
* Function: Boolean isEmpty(Queue Q)
* Date Created: 3rd October 2017
* Date Last Modified: 5th October 2017
* Description: checks whether the queue is empty or not.
* Input parameters: the struct Q
* Returns: a boolean type so true or false
* Preconditions: None
* Postconditions: tells us whether the queue is empty or not and we determine that by the value returned by the function.
*************************************************************/
Boolean isEmpty(Queue Q)
{
	if (Q.pTail == NULL)
	{
		return True;
	}
	else
	{
		return False;
	}
}

/*************************************************************
* Function: void dequeue(Queue *Q)
* Date Created: 3rd October 2017
* Date Last Modified: 7th October 2017
* Description: deletes the node at the end of the queue
* Input parameters: pointer to the Queue
* Returns: an integer 1, 2 or 0 based on if the function was executed successfully or not. 1 and 2 represents whats the status of the queue, how many nodes are left. if it is 1 meaning 0 nodes are left in the queue and if the return value is 2 meaning there are more than 1 Nodes left.
* Preconditions: the queue shouldn't be empty
* Postconditions: deletes the last node
*************************************************************/
int dequeue(Queue *pQ)
{
	int returnValue = 0;
	QueueNode * pTemp = pQ->pTail;

	if (pQ->pHead == pQ->pTail) // only one customer
	{
		free(pQ->pHead->pData);
		free(pQ->pHead);
		pQ->pHead = pQ->pTail = NULL;
		returnValue = 1;
	}
	else
	{
		while (pTemp->pNext != pQ->pHead) //more than one customer
		{
			pTemp = pTemp->pNext;
		}
		free(pQ->pHead->pData);
		free(pQ->pHead);
		pQ->pHead = pTemp;
		returnValue = 2;
	}
	return returnValue;
}

/*************************************************************
* Function: int TotalTimeCalculator(Queue Q)
* Date Created: 3rd October 2017
* Date Last Modified: 7th October 2017
* Description: Calculates the total time before the customer departs
* Input parameters: Queue Q
* Returns: the number of minutes taken before the customer departs.
* Preconditions: Queue doesn't have one or 0 customers.
* Postconditions: none
*************************************************************/
int TotalTimeCalculator(Queue Q)
{
	int LaneTotalTime = 0;

	QueueNode * pTemp = Q.pTail;

	//list is not empty and is not beyond pHead
	while (pTemp != NULL)
	{
		LaneTotalTime += pTemp->pData->serviceTime;
		pTemp = pTemp->pNext;
	}
	return LaneTotalTime;
}

/*************************************************************
* Function:
* Date Created:
* Date Last Modified:
* Description:
* Input parameters:
* Returns:
* Preconditions:
* Postconditions:
*************************************************************/

