#include "Engines/GameEngine/GameEngine.hpp"

GameEngine::GameEngine()
{
	m_threadGraphic = NULL;
}

GameEngine::~GameEngine()
{
	if (m_threadGraphic != NULL)
	{
		delete m_threadGraphic;
	}
}

bool GameEngine::construct()
{
	// dynamic allocations
	m_graphicEngine.init();

	int numberOfElements = 1000;

	// TODO : 
			// temporary : to remplace by a ressource loader

	// creation du TileSet et initialisation
	m_graphicEngine.addTileSet("test", "Res/tileTest.png", numberOfElements, 1);

	std::string nomCleAnimation("vieuxJaune");
	Vector2f tailleTuile(32, 48);

	// preparation necessaire pour la creation des sprites/animations
	// creation des caracteristiques des textures
	for (unsigned int indiceLigne = 0; indiceLigne < 4; indiceLigne++)
	{
		//creation des points pour les textures/animations
		std::vector <Vector2f> texturePoints;

		for (unsigned int indiceColonne = 0; indiceColonne < 3; indiceColonne++)
		{
			texturePoints.push_back(Vector2f(indiceColonne*tailleTuile.x, indiceLigne*tailleTuile.y));
		}

		// ajout dans le moteur des caracteristiques
		m_graphicEngine.addTextureCharacteristics(
			nomCleAnimation,
			"test",
			tailleTuile,
			texturePoints,
			0.25);
	}

	// creation d'une animation a partir des caracteristiques "vieuxJaune" au niveau 0
	m_graphicEngine.addAnimation(nomCleAnimation, 0, 1);

	// lancement de l'animation en mode infini
	std::vector <fme::Sprite*> animations;
	for (unsigned int i = 0; i < numberOfElements; i++)
	{
		animations.push_back(m_graphicEngine.getFreeSprite(nomCleAnimation));
		animations[i]->setRepeated(true);
		animations[i]->setPosition((i % 100) * 3, (i / 100) * 3);
		animations[i]->start();
	}

	return true;
}

void GameEngine::startGraphicEngine(float framePerSecond)
{
	m_graphicEngine.openWindow("test Graphic Engine");
	m_threadGraphic = new std::thread(&fme::GraphicEngine::run, std::ref(m_graphicEngine), framePerSecond);
	m_threadGraphic->detach();
}