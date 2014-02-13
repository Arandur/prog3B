#pragma once

class God;

class ObjectInterface
{
public:
	virtual void* stuff( God* = 0 ) = 0;
};
