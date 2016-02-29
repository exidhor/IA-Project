#pragma once
#include "Engines/PhysicEngine.hpp"

class Object
{
public:
	Object();
	virtual ~Object();

private:
	CollisionBox collisionBox;
};