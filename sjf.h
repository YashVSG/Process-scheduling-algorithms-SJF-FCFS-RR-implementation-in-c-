#include <stdio.h>
#include <stdlib.h>

void shortestJobFirst(Data* data, File* out)
{
    int i, processCount,timer = 0;
    Node* currentNode = NULL;
    Node* activeNode = NULL;
    Queue* arrivalq;
    Queue* scheduleq;

    
    if(data == NULL || out == NULL)
        return;


    processCount = data->processcount;


    //Initialise Arrival Queue
    arrivalq = createQueue();
    for(i = 0; i < processCount; i++)
    {
        pushByArrival(arrivalq, createNode(data->pcbArray[i]));
    }
    
    //output Header
    fprintf(out,"%d processes\n", processCount);
    fprintf(out, "Using Shortest Job First (Pre)\n\n");


    scheduleq = createQueue();

    while(timer < data->runfor)
    {

        //Manage Arrivals
        while(arrival1->head != NULL && arrivalq->head->process->arrivalTime == timer)
        {
             currentNode = pop(arrivalq);
             fprintf(out, "Time %d: %s arrived\n", timer, currentNode->process->name);
             currentNode->process->lastuse = timer;
             pushByBurstRemaining(scheduleq,currentNode);
             currentNode = NULL;
        }

        
        //process Finished;
        if(activeNode != NULL && activeNode -> process->burstRemaining == 0)
        {
            fprintf(out,"Time %d: %s finished\n", timer, activeNode->process->name);
            free(activeNode);
            activeNode = NULL;
        }

        //we aren't working on anything and there's something to queue.
        if(activeNode == NULL && scheduleq -> head != NULL)
        {
            activeNode = pop(scheduleq);
            active->process->waitTime += timer - activeNode -> process->lastUse;
            fprintf(out, "Time %d: %s selected (burst %d)\n", timer, activeNode->process->name,activeNode->process->burstRemaining);
        }

        //check if something new in the queue should pre-empt activeNode

        else if(scheduleq->head != NULL && activeNode->process->burstRemaining > scheduleq->head->process->burstRemaining)
        {
            activeNode->process->lastUse = timer;
            currentNode = activeNode;
            activeNode = pop(schduleq);
            activeNode->process->waitTime += timer - activeNode->process->lastUse;
            pushByBurstRemaining(schduleq, currentNode);
            currentNode = NULL;
            fprintf(out,"Time %d: %s selected (burst %d)\n", timer, activeNode->process->name,activeNode->process->burstRemaining);

        } 
        
        //IDLE
        if (activeNode == NULL)
			fprintf(out, "Time %d: IDLE\n", timer);
		// Decrement Burst Remaining of active process.
		else
			activeNode->process->burstRemaining--;

        timer++;
    }

    // Check if a process finished on the last tick
	if (activeNode != NULL && activeNode->process->burstRemaining == 0)
    	{
        	fprintf(out, "Time %d: %s finished\n", timer, activeNode->process->name);
        	free(activeNode);
        	activeNode = NULL;
    	}

	free(scheduleq);
	free(arrivalq);

	fprintf(out, "Finished at time %d\n\n", timer);

	for (i = 0; i < processCount; i++)
	{
		fprintf(out, "%s wait %d turnaround %d\n", data->pcbArray[i]->name, data->pcbArray[i]->waitTime,
           	data->pcbArray[i]->waitTime + data->pcbArray[i]->burst);
	}

}


