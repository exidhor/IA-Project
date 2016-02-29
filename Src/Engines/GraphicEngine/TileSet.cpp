#include "Engines/GraphicEngine/TileSet.hpp"

fme::TileSet::TileSet(sf::Texture* newTextureTile)
{
	textureTile = newTextureTile;
	arrayOfCurrentIndices = NULL;
	maxSizeVerticesArray = 0;
	numberOfLayerLevel = 0;
	continousIndexArray = -1;
	isTemporary = true;

	isContinous = false;
}

fme::TileSet::~TileSet()
{
	delete[] arrayOfCurrentIndices;
	verticesArrayToDraw.clear();
}

void fme::TileSet::loading(unsigned int newMaxSizeVerticesArray, unsigned int newNumberOfLayerLevel)
{
	maxSizeVerticesArray = newMaxSizeVerticesArray * 4;
	numberOfLayerLevel = newNumberOfLayerLevel;

	verticesArrayToDraw.resize(numberOfLayerLevel * maxSizeVerticesArray, sf::Vertex());
	/*verticesArray.resize(
			numberOfLayerLevel, 
			std::vector <sf::Vertex> (maxSizeVerticesArray*4, sf::Vertex())
		);*/

	arrayOfCurrentIndices = new int[numberOfLayerLevel];
		for (unsigned int i = 0; i < numberOfLayerLevel; ++i)
	{	
		arrayOfCurrentIndices[i] = -1;
	}
}

void fme::TileSet::assembleContinousArray()
{
	if (!isContinous)
	{
		continousIndexArray = arrayOfCurrentIndices[0];

		for (unsigned int level = 1; level < numberOfLayerLevel; level++)
		{
			int baseIndex = level * maxSizeVerticesArray;

			for (int i = 0; i < arrayOfCurrentIndices[level] + 1; i++)
			{
				continousIndexArray++;
				verticesArrayToDraw[continousIndexArray].position.x = 
					verticesArrayToDraw[baseIndex + i].position.x;

				verticesArrayToDraw[continousIndexArray].position.y = 
					verticesArrayToDraw[baseIndex + i].position.y;

				verticesArrayToDraw[continousIndexArray].texCoords.x = 
					verticesArrayToDraw[baseIndex + i].texCoords.x;

				verticesArrayToDraw[continousIndexArray].texCoords.y = 
					verticesArrayToDraw[baseIndex + i].texCoords.y;
			}
		}

		isContinous = true;
	}
}

void fme::TileSet::addVertices(sf::Vertex vertices[4], unsigned int level)
{
	isContinous = false;
	for (int i = 0; i < 4; i++)
	{
		arrayOfCurrentIndices[level]++;
		verticesArrayToDraw[level*maxSizeVerticesArray + arrayOfCurrentIndices[level]].position.x = vertices[i].position.x;
		verticesArrayToDraw[level*maxSizeVerticesArray + arrayOfCurrentIndices[level]].position.y = vertices[i].position.y;
		verticesArrayToDraw[level*maxSizeVerticesArray + arrayOfCurrentIndices[level]].texCoords.x = vertices[i].texCoords.x;
		verticesArrayToDraw[level*maxSizeVerticesArray + arrayOfCurrentIndices[level]].texCoords.y = vertices[i].texCoords.y;
	}
}

void fme::TileSet::clearAllLayers()
{
	if (isTemporary)
	{
		for (unsigned int i = 0; i < numberOfLayerLevel; i++)
		{
			arrayOfCurrentIndices[i] = -1;
		}
		continousIndexArray = -1;
		isContinous = false;
	}
}

void fme::TileSet::clearLayer(unsigned int layerLevel)
{
	arrayOfCurrentIndices[layerLevel] = -1;
	continousIndexArray = -1;
	isContinous = false;
}

void fme::TileSet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = textureTile;
	if (isContinous)
	{
		target.draw(&verticesArrayToDraw[0], continousIndexArray + 1, sf::Quads, states);
	}
}

void fme::TileSet::setTemporary(bool state)
{
	isTemporary = state;
}