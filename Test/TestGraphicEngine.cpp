#include "Engines/GraphicEngine.hpp"
/*
int main()
{
	fme::GraphicEngine moteurGraphique;

	// allocation dynamique de la memoire
	moteurGraphique.init();

	// creation du TileSet et initialisation
	moteurGraphique.addTileSet("test", "Res/tileTest.png", 1000, 1);

	std::string nomCleAnimation("vieuxJaune");
	fme::Vector2f tailleTuile(32, 48);

	// preparation necessaire pour la creation des sprites/animations
	// creation des caracteristiques des textures
	for (unsigned int indiceLigne = 0; indiceLigne < 4; indiceLigne++)
	{
		//creation des points pour les textures/animations
		std::vector <fme::Vector2f> texturePoints;

		for (unsigned int indiceColonne = 0; indiceColonne < 3; indiceColonne++)
		{
			texturePoints.push_back(fme::Vector2f(indiceColonne*tailleTuile.x, indiceLigne*tailleTuile.y));
		}

		// ajout dans le moteur des caracteristiques
		moteurGraphique.addTextureCharacteristics(
			nomCleAnimation,
			"test",
			tailleTuile,
			texturePoints,
			0.25);
	}

	// creation d'une animation a partir des caracteristiques "vieuxJaune" au niveau 0
	moteurGraphique.addAnimation(nomCleAnimation, 0, 1);

	// creation de la fenetre
	moteurGraphique.openWindow("test du Graphic Engine !!!");

	// pour les animations dans le temps
	//sf::Clock clock;
	//double timePasse = 0;

	// lancement de l'animation en mode infini
	std::vector <fme::Sprite*> animations;
	for (unsigned int i = 0; i < 1000; i++)
	{
		animations.push_back(moteurGraphique.getFreeSprite(nomCleAnimation));
		animations[i]->setRepeated(true);
		animations[i]->setPosition((i % 10) * 32, (i / 10) * 48);
		animations[i]->start();
	}

	while (true)
	{

	}
	
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// démonstration des fonctionnalités du moteur
			if (event.type == sf::Event::KeyReleased)
			{
				// depart de l'animation
				if (event.key.code == sf::Keyboard::A)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->start();
					}
				}

				// arret de l'animation ainsi que de la rotation
				if (event.key.code == sf::Keyboard::S)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->stop();
						animations[i]->stopRotation();
					}
				}

				// changement d'animation
				if (event.key.code == sf::Keyboard::Left)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->goToLine(1);
					}
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->goToLine(2);
					}
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->goToLine(3);
					}
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->goToLine(0);
					}
				}

				// cache l'animation
				if (event.key.code == sf::Keyboard::Q)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->hide();
					}
				}

				// montre l'animation
				if (event.key.code == sf::Keyboard::W)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->show();
					}
				}

				// lance une rotation infini
				if (event.key.code == sf::Keyboard::R)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->setRotationByAngle(200, 360);
						animations[i]->setInfiniteRotation(true);
						animations[i]->startRotation();
					}
				}

				// translation au point 450, 450 en 3 secondes
				if (event.key.code == sf::Keyboard::T)
				{
					for (unsigned int i = 0; i < 1000; i++)
					{
						animations[i]->setTranslationByTargetPoint(3, 500, 300);
						animations[i]->startTranslation();
					}

				}
			}
		}

		timePasse = clock.getElapsedTime().asSeconds();
		clock.restart();

		moteurGraphique.update(timePasse);
		window.clear();
		window.draw(moteurGraphique);
		window.display();
	}
	
	return 0;
}
*/