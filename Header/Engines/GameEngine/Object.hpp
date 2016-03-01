#pragma once
#include "Engines/PhysicEngine.hpp"
#include "Engines/GraphicEngine.hpp"

class Object
{
public:
	Object();
	virtual ~Object();

private:
	CollisionBox	m_collisionBox;
	fme::Sprite		m_sprite;
};