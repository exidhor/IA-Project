/*!
* \file		TileSet.hpp
* \brief	A container which provide multiple
*			layers of display.
*			Store sf::Vertices in an array and display them
*			by with this cycle :
* 		
*				clear();			-- optionnal
*				addVertices(...);
*				...
*				addVertices(...);
*				buildArray();
*				draw();
*			It needs to be load before being used.
*			Do a TileSet per sf::PrimitiveType.
* \author	Exhidor
* \version	2.5
* \date		2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace fme
{
	class TileSet : public sf::Drawable
	{
	public:
		TileSet();
		TileSet(sf::Texture* textureTile);

		~TileSet();

		void			loading(
							unsigned int maxSizeVerticesArray,
							unsigned int numberOfLayerLevel,
							sf::PrimitiveType primitiveType = sf::Quads);

		void			clearAllLayers();
		void			clearLayer(unsigned int layerLevel);

		void			addVertices(
							sf::Vertex* vertices, 
							unsigned int sizeArray,
							unsigned int layerLevel);

		void			assembleContinousArray();

		virtual void	draw(sf::RenderTarget& target,
							sf::RenderStates states) const;

		void setTemporary(bool state);

	private:

		bool verifyLevel(int level);
		bool verifyIndice(int indice);

		sf::Texture*			m_textureTile;
		std::vector<sf::Vertex>	m_verticesArrayToDraw;
		sf::PrimitiveType		m_primitiveType;
		unsigned int			m_maxSizeVerticesArray;
		unsigned int			m_numberOfLayerLevel;
		// array of the positions of the last element for the different vertex arrays
		// (has for value -1 if the array is void)
		int*					m_arrayOfCurrentIndices;
		int						m_continousIndexArray;
		bool					m_isContinous;
		bool					m_isTemporary;
	};
}