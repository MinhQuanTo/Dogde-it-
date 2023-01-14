#include "Animation.h"
#include "Entity.h"
#include "Header.h"
#include "asteroid.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

using namespace sf;

float DegToRad = 0.017453f;

bool isCollide(Entity* a, Entity* b) // check collide of entity
{
	return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) < (a->R + b->R) * (a->R + b->R);
}

int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(screenWidth, screenHeight), "Dodge it!");
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4;
	t1.loadFromFile("spaceship.png");
	t2.loadFromFile("background.png");
	t3.loadFromFile("rock.png");
	t4.loadFromFile("explosions/type_B.png");

	t1.setSmooth(true);
	t2.setSmooth(true);

	Sprite sBackground(t2);

	Animation sRock(t3, 0, 0, 64, 64, 16, 0.2);
	Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
	Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
	Animation sExplosion_ship(t4, 0, 0, 192, 192, 64, 0.5);

	Font font;
	Text hud;
	font.loadFromFile("../Data/ARCADECLASSIC.ttf");
	hud.setFont(font);
	hud.setCharacterSize(30);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(screenWidth / 2, 0);

	int score = 0;

	std::list<Entity*> entities;

	for (int i = 0; i < 15; i++) // create asteroid and push it to entity vector
	{
		asteroid* a = new asteroid();
		a->settings(sRock, rand() % screenWidth, rand() % screenHeight, rand() % 360, 25);
		entities.push_back(a);
	}

	player* p = new player();
	p->settings(sPlayer, 200, 200, 0, 20);
	entities.push_back(p);

	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				app.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 3;
			if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle -= 3;
			if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust = true;
			else p->thrust = false;

			for (auto a : entities) // compare entities to set collide of them
			{
				for (auto b : entities)
				{
					if (a->name == "player" && b->name == "asteroid")
					{
						if (isCollide(a, b))
						{
							b->life = false;

							Entity* e = new Entity();
							e->settings(sExplosion_ship, a->x, a->y);
							e->name = "explosion";
							entities.push_back(e);

							p->settings(sPlayer, screenWidth / 2, screenHeight / 2, 0, 20);
							p->dx = 0; p->dy = 0;
						}
					}
				}
			}

			if (p->thrust)  p->anim = sPlayer_go;
			else   p->anim = sPlayer;

			for (auto e : entities)
			{
				if (e->name == "explosion")
				{
					score = 0;
					if (e->anim.isEnd())
					{
						e->life = 0;
					}
				}
				else
				{
					score++;
				}
			}

			if (rand() % 150 == 0) //spam more rock
			{
				asteroid* a = new asteroid();
				a->settings(sRock, 0, rand() % screenHeight, rand() % 360, 25);
				entities.push_back(a);
			}

			for (auto i = entities.begin(); i != entities.end();)
			{
				Entity* e = *i;
				e->update();
				e->anim.update();

				if (e->life == false)
				{
					i = entities.erase(i); 
					delete e;
				}
				else
				{
					i++;
				}
			}

			stringstream ss2;
			ss2 << "Score " << score;
			hud.setString(ss2.str());

			app.draw(sBackground);
			app.draw(hud);
			for (auto i : entities)
			{
				i->draw(app);
			}
			app.display();
		}
	}

	return 0;
}