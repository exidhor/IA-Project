/*!
* \file GraphicEngine.hpp
* \brief ...
* \author Exhidor
* \version 0.1
* \date 2016-02-01
*/


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicEngine/TileSetsDisplayer.hpp"
#include "GraphicEngine/TileSetManager.hpp"
#include "GraphicEngine/TextureCharacteristicsManager.hpp"
#include "GraphicEngine/RessourceManager.hpp"
#include "GraphicEngine/Vector2f.hpp"

namespace fme
{
	class GraphicEngine : public sf::Drawable
	{
	public:
		// initialization
		GraphicEngine();
		~GraphicEngine();
		void init();

		// creation
		void addTileSet(std::string const& key, std::string const& path);
		void initTileSetLayers(std::string const& key, unsigned int maxSizeArray,
			unsigned int numberOfLayer);

		void addTextureCharacteristics(
			std::string const& spriteKey,
			std::string const& tileSetKey,
			Vector2f const& tileSize,
			std::vector <Vector2f> texturePoints,
			double timePerFrame);

		void addTextureCharacteristics(
			std::string const& spriteKey,
			std::string const& tileSetKey,
			Vector2f const& tileSize,
			Vector2f const& oneTexturePoint);

		void addSprite(std::string const& key,
			unsigned int layerLevel,
			unsigned int numberOfElements = 1);

		void addAnimation(std::string const& key,
			unsigned int layerLevel,
			unsigned int numberOfElements = 1);

		// ressources gestion
		Sprite* getFreeSprite(std::string const& key);
		Sprite* getSpecificSprite(std::string const& key, unsigned int id);
		void freeSpecificSprite(std::string const& key, unsigned int id);
		RessourceManager * getResourceManager();
		void update(double time);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		TileSetsDisplayer* tileSetDisplayer;
		TileSetManager* tileSetManager;
		TextureCharacteristicsManager* textureCharactertisticsManager;
		RessourceManager* ressourceManager;
	};
}