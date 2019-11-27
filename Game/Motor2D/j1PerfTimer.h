#ifndef __j1PERFTIMER_H__
#define __j1PERFTIMER_H__

#include "p2Defs.h"

class j1PerfTimer
{
public:

	// Constructor
	j1PerfTimer();

	void Start();
	double ReadMs() const;
	uint ReadTicks() const;

private:
	uint	started_at;
	static uint frequency;
};

#endif //__j1PERFTIMER_H__