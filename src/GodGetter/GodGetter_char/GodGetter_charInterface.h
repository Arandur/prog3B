#pragma once

#include "../../Object/ObjectInterface.h"
#include "../../God/God.h"

class GodGetter_charInterface :
	public ObjectInterface
{
public:
	virtual GodGetter_charInterface* next() const = 0;
	virtual void* stuff( God* = 0 ) = 0;
};
