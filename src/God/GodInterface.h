#pragma once

#include "../Object/ObjectInterface.h"

class GodInterface :
	public ObjectInterface
{
public:
	void* stuff( God* = 0 ) = 0;
};
