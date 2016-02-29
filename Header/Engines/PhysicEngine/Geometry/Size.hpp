#pragma once

class Size
{
public:
	Size();
	Size(float width, float height);
	Size(Size const& size);


	float width;
	float height;
};