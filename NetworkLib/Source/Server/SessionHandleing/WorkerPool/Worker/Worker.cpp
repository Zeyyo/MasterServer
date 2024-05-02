#include "pch.h"
#include "Worker.h"


void NetworkLibrary::Worker::stop()
{
	bAwaitingTermination = true;

	pipe->pbWorkerObjectTerminated = &bTerminated;
	pipe->bAwaitingTermination = bAwaitingTermination;

	coThreadContinue.notify_all();
}