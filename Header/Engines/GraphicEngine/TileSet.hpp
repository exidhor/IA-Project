/*!
* \file TileSet.hpp
* \brief An displayer which provide multiple
* \brief layers of display.
* \brief Store fme::QuadVertices in an array and display them
* \brief by following this cycle :
* \brief		
* \brief	reset();			-- optionnal
* \brief	addVertices(...);
* \brief	...
* \brief	addVertices(...);
* \brief	buildArray();
* \brief	draw();
* \brief It needs to be load before being used
* \author Exhidor
* \version 2.1
* \date 2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace fme
{
	class TileSet : public sf::Drawable
	{
	public:
		TileSet(sf::Texture* textureTile);

		~TileSet();

		void			loading(
							unsigned int maxSizeVerticesArray,
							unsigned int numberOfLayerLevel);

		void			clearAllLayers();
		void			clearLayer(unsigned int layerLevel);

		void			addVertices(
							sf::Vertex vertices[4],
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