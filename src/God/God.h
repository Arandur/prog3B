#pragma once

#include "GodInterface.h"

class God :
	public GodInterface
{
public:
	God();
	~God();
	
	void* stuff( God* = 0 );

private:
	void* things;
};
