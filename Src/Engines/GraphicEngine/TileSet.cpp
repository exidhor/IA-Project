#include "Engines/GraphicEngine/TileSet.hpp"

fme::TileSet::TileSet(sf::Texture* newTextureTile)
{
	m_textureTile = newTextureTile;
	m_arrayOfCurrentIndices = NULL;
	m_maxSizeVerticesArray = 0;
	m_numberOfLayerLevel = 0;
	m_continousIndexArray = -1;
	m_isTemporary = true;

	m_isContinous = false;
}

fme::TileSet::TileSet()
	: TileSet(NULL)
{
	// void
}

fme::TileSet::~TileSet()
{
	if (m_arrayOfCurrentIndices != NULL)
	{
		delete[] m_arrayOfCurrentIndices;
	}

	m_verticesArrayToDraw.clear();
}

void fme::TileSet::loading(unsigned int newMaxSizeVerticesArray,
							unsigned int newNumberOfLayerLevel,
							sf::PrimitiveType primitiveType)
{
	m_maxSizeVerticesArray = newMaxSizeVerticesArray * 4;
	m_numberOfLayerLevel = newNumberOfLayerLevel;

	m_verticesArrayToDraw.resize(m_numberOfLayerLevel * m_maxSizeVerticesArray, sf::Vertex());

	m_arrayOfCurrentIndices = new int[m_numberOfLayerLevel];
		
	for (unsigned int i = 0; i < m_numberOfLayerLevel; ++i)
	{	
		m_arrayOfCurrentIndices[i] = -1;
	}

	m_primitiveType = primitiveType;
}

void fme::TileSet::assembleContinousArray()
{
	if (!m_isContinous)
	{
		m_continousIndexArray = m_arrayOfCurrentIndices[0];

		for (unsigned int level = 1; level < m_numberOfLayerLevel; level++)
		{
			int baseIndex = level * m_maxSizeVerticesArray;

			for (int i = 0; i < m_arrayOfCurrentIndices[level] + 1; i++)
			{
				m_continousIndexArray++;
				m_verticesArrayToDraw[m_continousIndexArray].position.x = 
					m_verticesArrayToDraw[baseIndex + i].position.x;

				m_verticesArrayToDraw[m_continousIndexArray].position.y = 
					m_verticesArrayToDraw[baseIndex + i].position.y;

				m_verticesArrayToDraw[m_continousIndexArray].texCoords.x = 
					m_verticesArrayToDraw[baseIndex + i].texCoords.x;

				m_verticesArrayToDraw[m_continousIndexArray].texCoords.y = 
					m_verticesArrayToDraw[baseIndex + i].texCoords.y;
			}
		}

		m_isContinous = true;
	}
}

void fme::TileSet::addVertices(sf::Vertex* vertices, unsigned int sizeArray, unsigned int level)
{
	if (verifyLevel(level))
	{
		if (verifyIndice(m_arrayOfCurrentIndices[level] - m_maxSizeVerticesArray*level))
		{
			m_isContinous = false;
			for (int i = 0; i < sizeArray; i++)
			{
				m_arrayOfCurrentIndices[level]++;

				int index = level*m_maxSizeVerticesArray + m_arrayOfCurrentIndices[level];

				m_verticesArrayToDraw[index].position.x = vertices[i].position.x;
				m_verticesArrayToDraw[index].position.y = vertices[i].position.y;
				m_verticesArrayToDraw[index].texCoords.x = vertices[i].texCoords.x;
				m_verticesArrayToDraw[index].texCoords.y = vertices[i].texCoords.y;
			}
		} 
	} 
	
}

void fme::TileSet::clearAllLayers()
{
	if (m_isTemporary)
	{
		for (unsigned int i = 0; i < m_numberOfLayerLevel; i++)
		{
			m_arrayOfCurrentIndices[i] = -1;
		}
		m_continousIndexArray = -1;
		m_isContinous = false;
	}
}

void fme::TileSet::clearLayer(unsigned int layerLevel)
{
	if (verifyLevel(layerLevel))
	{
		m_arrayOfCurrentIndices[layerLevel] = -1;
		m_continousIndexArray = -1;
		m_isContinous = false;
	}
}

void fme::TileSet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_isContinous)
	{
		states.texture = m_textureTile;

		target.draw(&m_verticesArrayToDraw[0], m_continousIndexArray + 1, m_primitiveType, states);
	}
}

void fme::TileSet::setTemporary(bool state)
{
	m_isTemporary = state;
}

bool fme::TileSet::verifyLevel(int level)
{
	if (level < m_numberOfLayerLevel)
		return true;

	std::cerr << "Level too high" << std::endl;
	return false;

}

bool fme::TileSet::verifyIndice(int indice)
{
	if (indice < (int)m_maxSizeVerticesArray)
		return true;

	std::cerr << "Adding a element on a fullTileSet" << std::endl;
	return false;
}