/*!
* \file		GraphicEngine.hpp
* \brief	The BIG controller of the
*			graphic part of the programm
*			it provides all methods to
*			create, drop and update shapes,
*			sprites and animations
* \author	Exhidor
* \version	0.3
* \date		2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "Engines/GraphicEngine/TileSetsDisplayer.hpp"
#include "Engines/GraphicEngine/TileSetManager.hpp"
#include "Engines/GraphicEngine/TextureCharacteristicsManager.hpp"
#include "Engines/GraphicEngine/RessourceManager.hpp"
#include "Utilities/Vector2.hpp"

namespace fme
{
	class GraphicEngine : public sf::Drawable
	{
	public:
		// initialization
		GraphicEngine();
		~GraphicEngine();

		void init();

		void openWindow(std::string const& title);
		void closeWindow();

		void setFrameRate(float framePerSecond);

		// creation
		void addTileSet(
			std::string const& key, 
			std::string const& path,
			unsigned int maxSizeArray,
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

		void addSprite(
			std::string const& key,
			unsigned int layerLevel,
			unsigned int numberOfElements = 1);

		void addAnimation(
			std::string const& key,
			unsigned int layerLevel,
			unsigned int numberOfElements = 1);

		// ressources gestion

		Sprite*				getFreeSprite(std::string const& key);
		Sprite*				getSpecificSprite(std::string const& key, unsigned int id);
		void				freeSpecificSprite(std::string const& key, unsigned int id);
		RessourceManager *	getResourceManager();

		void				run(int framePerSecond);
		

	private:
		void				update(double time);
		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

		TileSetsDisplayer*	m_tileSetDisplayer;
		TileSetManager*		m_tileSetManager;
		TextureCharacteristicsManager* m_textureCharactertisticsManager;
		RessourceManager*	m_ressourceManager;
		double				m_frameTime;
		double				m_mergeFrameTime;
		sf::RenderWindow*	m_window;
		bool				m_windowIsOpen;

		// deprecated methods
		void				addTileSet(std::string const& key, std::string const& path);
		void				initTileSetLayers(std::string const& key, unsigned int maxSizeArray,
									unsigned int numberOfLayer);
	};
}