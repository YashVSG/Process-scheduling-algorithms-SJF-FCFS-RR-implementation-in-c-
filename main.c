#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"
#include "data.h"
#include "queue.h"
#include "sjf.h"
#include "RR.h"
#include "fcfs.h"

int main()
{
	FILE* out;
	Data* data;

	out = fopen("processes.out", "w");
	data = parseFile("processes.in");

	if (strcmp(data->algorithm, "sjf") == 0)
	{
		shortestJobFirst(data, out);
	}
	else if (strcmp(data->algorithm, "rr") == 0)
	{
		rr(data, out);
	}
	else if (strcmp(data->algorithm, "fcfs") == 0)
	{
		firstComeFirstServed(data, out);
	}

	destroyData(data);
	fclose(out);
	return 0;
}