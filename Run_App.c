#include "Header.h"

void Run_App(void)
{
	//Variable Declaration.
	int TimeElapsed = 0, RunTime = 0, const TenMinCounter = 10,
		FastLaneArrivalTime = 0, NormalLaneArrivalTime = 0,
		FastLaneServiceTime = 0, NormalLaneServiceTime = 0,
		FastLaneCustomerCount = 0, NormalLaneCustomerCounter = 0,
		FastLaneTotalTime = 0, NormalLaneTotalTime = 0,
		FastLaneSuccess = 0, NormalLaneSuccess = 0,
		FastLaneDequeue = -1, NormalLaneDequeue = -1;

	printf("Please enter the duration as an integer that represents a minute as an unit of time for the simulation:\n");
	scanf("%d", &RunTime);

	Queue Q_FastLane = { NULL, NULL };
	Queue Q_NormalLane = { NULL, NULL };
	Data FastLaneCustomerData = { 0,0,0 }, NormalLaneCustomerData = { 0,0,0 };

	//Arrival Time for each Lane.
	FastLaneArrivalTime = (rand() % 5) + 1;
	NormalLaneArrivalTime = (rand() % 6) + 3;
	printf("Fast Lane Arrival Time: %d\n", FastLaneArrivalTime);
	printf("Normal Lane Arrival Time: %d\n\n", NormalLaneArrivalTime);
	
	while (TimeElapsed != RunTime)
	{
		//enqueue
		if (FastLaneArrivalTime == 0)
		{
			NormalLaneCustomerData.customerNumber = 0;
			NormalLaneCustomerData.serviceTime = 0;
			NormalLaneCustomerData.totalTime = 0;
			//-------------------------------------------------------------
			//printing the lane.
			printf("\nA Customer Arrives in the Express Lane.\n");

			//printing arrival time
			if (RunTime < 24 * 60)
			{
				printf("The Arrival Time is: %d:%d %s\n", (TimeElapsed / 60 >= 12) ? (TimeElapsed / 60) % 13 : TimeElapsed / 60, TimeElapsed % 60, (TimeElapsed / 60 > 12) ? "pm" : "am");
			}
			else
			{
				printf("The Arrival Time is: %d\n", TimeElapsed);
			}

			FastLaneCustomerCount += 1;
			//printing customer number
			printf("The Customer Number is: %d\n", FastLaneCustomerCount);

			//--------------------------------------------------------------

			FastLaneServiceTime = rand() % 5 + 1;
			// pTail's + ServiceTime
			if (Q_FastLane.pTail == NULL)//the queue is empty
			{
				FastLaneTotalTime = FastLaneServiceTime;
			}
			else if (Q_FastLane.pTail->pNext == NULL)//Only one customer
			{
				FastLaneTotalTime = Q_FastLane.pTail->pData->serviceTime + FastLaneServiceTime;
			}
			else //More than one customer
			{
				FastLaneTotalTime = TotalTimeCalculator(Q_FastLane);
			}

			FastLaneCustomerData.customerNumber = FastLaneCustomerCount;
			FastLaneCustomerData.serviceTime = FastLaneServiceTime;
			FastLaneCustomerData.totalTime = FastLaneTotalTime;
			//Now we set new pTail.
			FastLaneSuccess = enqueue(&Q_FastLane, FastLaneCustomerData);
		}

		if (NormalLaneArrivalTime == 0)
		{
			NormalLaneCustomerData.customerNumber = 0;
			NormalLaneCustomerData.serviceTime = 0;
			NormalLaneCustomerData.totalTime = 0;
			//-------------------------------------------------------------------
			//printing which lane
			printf("\nA Customer Arrives in the Normal Lane.\n");

			//printing Arrival Time
			if (RunTime < 24 * 60)
			{
				printf("The Arrival Time is: %d:%d %s\n", (TimeElapsed / 60 >= 12) ? (TimeElapsed / 60) % 13 : TimeElapsed / 60, TimeElapsed % 60, (TimeElapsed / 60 > 12) ? "pm" : "am");
			}
			else
			{
				printf("The Arrival Time is: %d\n", TimeElapsed);
			}

			//printing the customer number
			NormalLaneCustomerCounter += 1;
			printf("The Customer Number is: %d\n", NormalLaneCustomerCounter);

			//----------------------------------------------------------------------------

			NormalLaneServiceTime = rand() % 6 + 3;
			if (Q_NormalLane.pTail == NULL)//list is empty
			{
				NormalLaneTotalTime = NormalLaneServiceTime;
			}
			else if (Q_NormalLane.pTail->pNext == NULL)//only one customer
			{
				NormalLaneTotalTime = Q_NormalLane.pHead->pData->serviceTime + NormalLaneServiceTime;
			}
			else // more than one customers
			{
				NormalLaneTotalTime = TotalTimeCalculator(Q_NormalLane);
			}

			NormalLaneCustomerData.customerNumber = NormalLaneCustomerCounter;
			NormalLaneCustomerData.serviceTime = NormalLaneServiceTime;
			NormalLaneCustomerData.totalTime = NormalLaneTotalTime;
			//Set new pTail
			NormalLaneSuccess = enqueue(&Q_NormalLane, NormalLaneCustomerData);
		}

		//dequeue
		if (Q_FastLane.pHead != NULL)
		{
			if (Q_FastLane.pHead->pData->serviceTime == 0)
			{
				FastLaneDequeue = dequeue(&Q_FastLane);
			}
		}

		if (Q_NormalLane.pHead != NULL)
		{
			if (Q_NormalLane.pHead->pData->serviceTime == 0)
			{
				NormalLaneDequeue = dequeue(&Q_NormalLane);
			}
		}

		//Ten Mins elapsed therefore print both entire Queues to the screen
		if ((TimeElapsed % TenMinCounter) == 0)
		{
			//print entire Queue for each Lane.
			printf("Express Lane:\n");
			printQueue(Q_FastLane);
			printf("\nNormal Lane:\n");
			printQueue(Q_NormalLane);
		}

		//Update Condidtions
		TimeElapsed += 1;
		FastLaneArrivalTime -= 1;
		NormalLaneArrivalTime -= 1;
		if (Q_FastLane.pHead != NULL)
		{
			Q_FastLane.pHead->pData->serviceTime -= 1;
		}
		if (Q_NormalLane.pHead != NULL)
		{
			Q_NormalLane.pHead->pData->serviceTime -= 1;
		}
		system("pause"); 
	}
}