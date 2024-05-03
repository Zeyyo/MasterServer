#include "NEtw_pch.h"

#include "Includes/WorkerPool.h"
#include "Server/SessionHandling/SessionQueue/SessionQueue.h"
#include "Includes/Types/Worker.h"

void NetworkLibrary::Worker::stop()
{
	bAwaitingTermination = true;

	pipe->pbWorkerObjectTerminated = &bTerminated;
	pipe->bAwaitingTermination = bAwaitingTermination;

	coThreadContinue.notify_all();
}