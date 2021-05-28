#include "GameState.h"

//////////////////////////////////////////////////
//
//				CONSTRUCTOR/DESTRUCTOR
//
//////////////////////////////////////////////////

GameState::GameState(RenderWindow* window)
	: State(window)
{
	initPlayer(window);
	initBackground();
	this->window->setMouseCursorVisible(false);

	this->gameSound = new GameSound();
	
	this->gui = new Gui();

	this->gameSound->playMusic("backgroundMusic", 1);
}

GameState::~GameState()
{
	delete this->player;
	delete this->background;
	delete this->gameSound;
	delete this->gui;

	for (auto* bullet : this->bullets)
	{
		delete bullet;
	}
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
}

//////////////////////////////////////////////////
//
//				INIT SECTION 
//
//////////////////////////////////////////////////

void GameState::initBackground()
{
	this->background = new Background();
}

void GameState::initPlayer(RenderTarget* target)
{
	this->player = new Player();
	this->player->setPosition(target);
}

void GameState::initBullet(float pos_x, float pos_y, string type, string genus)
{
	this->bullets.push_back(
		new Bullet(
			/* Srodkowa pozycja gracza x			*/	pos_x,
			/* Gorna pozycja gracza y				*/	pos_y,
			/* Typ pocisku	(1 - enemy, 2 - player)	*/	type,
			/* Rodzaj pocisku						*/	genus
		)
	);
}

void GameState::initEnemy()
{
	this->currentTime = GetTickCount64();
	if (this->secondEnemySpawnTime - this->firstEnemySpawnTime > this->spawnEnemyCooldownInMillis)
	{
		this->enemies.push_back(
			new Enemy(
				/* lewy gorny rog enemy x		*/	(rand() % 800) + 200,
				/* lewy gorny rog enemy y		*/	-100,
				/* Typ enemy				    */	4
			)
		);
		this->firstEnemySpawnTime = this->currentTime;
	}
	else
		this->secondEnemySpawnTime = this->currentTime;
}

//////////////////////////////////////////////////
//
//				UPDATE SECTION 
//
//////////////////////////////////////////////////

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt);
}

void GameState::updateBackground(RenderTarget* target, const float& dt)
{
	this->background->update(target, dt);
}

void GameState::updateBullets(const float& dt)
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update(dt);
		counter++;
	}
}

void GameState::updateEnemies(RenderTarget* target, const float& dt)
{
	this->initEnemy();

	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update(target, dt);

		if ((rand() % 40) == 1)
		{
			this->initBullet((enemy->getEnemyPos().x + (enemy->getEnemyBounds().width / 2)), (enemy->getEnemyPos().y + enemy->getEnemyBounds().height) + 20, "enemyShot", "default");
		}
		counter++;
	}
}

void GameState::updateInput(RenderTarget* target, const float& dt)
{
	this->checkForQuit();

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->player->playerMove(target, dt, -1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->player->playerMove(target, dt, 1.f, 0.f);
	}

	///////////// STRZELANIE ////////////
	if (Keyboard::isKeyPressed(Keyboard::LControl))
	{
		currentTime = GetTickCount64();
		if (this->player->canAttack == true)
		{
			this->initBullet((this->player->getPlayerPos().x + (this->player->getPlayerBounds().width / 2.f)), (this->player->getPlayerPos().y) + 20, "playerShot", "default");
			this->player->firstAttackTime = currentTime;
			this->gameSound->playSound("bulletShot", 1);
		}
		else
			this->player->secondAttackTime = currentTime;
	}
}

void GameState::updateBulletOutside(RenderTarget* target)
{

	unsigned counter_bullet = 0;
	bool bullet_deleted = false;

	//////////////////////////////////
	//
	// Bullet usuwany po przekroczeniu
	// gornej i dolnej granicy ekranu
	//
	//////////////////////////////////


	for (auto* bullet : this->bullets)
	{
		if (((bullet->getBulletPos().y < -(bullet->getBulletBounds().height)) ||
			(bullet->getBulletPos().y > target->getSize().y))
			&& bullet_deleted == false)
		{

			delete this->bullets.at(counter_bullet);

			this->bullets.erase(this->bullets.begin() + counter_bullet);

			bullet_deleted = true;

			break;

		}
		++counter_bullet;
	}
}

void GameState::updateEnemyOutside(RenderTarget* target)
{

	bool enemy_deleted = false;
	unsigned counter_enemy = 0;

	//////////////////////////////////
	//
	// Enemy usuwany po przekroczeniu
	// granic ekranu
	//
	//////////////////////////////////

	for (auto* enemy : this->enemies)
	{

		if ((
			enemy->getEnemyPos().x > target->getSize().x + 200 ||			//Enemy poza prawa krawedzia ekranu
			enemy->getEnemyPos().x < -(enemy->getEnemyBounds().width) - 200||	//Enemy poza lewa krawedzia ekranu
			enemy->getEnemyPos().y > target->getSize().y)			//Enemy poza dolna krawedzia ekranu
			&& enemy_deleted == false)
		{

			delete this->enemies.at(counter_enemy);

			this->enemies.erase(this->enemies.begin() + counter_enemy);
			cout << "enemy deleted" << endl;
			enemy_deleted = true;

			break;

		}

		++counter_enemy;
	}
}

void GameState::updateBulletPlayer(RenderTarget* target)
{
	unsigned counter_bullet = 0;
	bool bullet_deleted = false;

	//////////////////////////////////
	//
	// Bullet od enemy i player 
	// usuwani po zderzeniu sie
	//
	//////////////////////////////////

	for (auto* bullet : this->bullets)
	{

		if (bullet->getBulletBounds().intersects(this->player->getPlayerBounds()))
		{
			if (bullet->bulletType == "enemyShot" &&  // jezeli bullet jest od enemy
				bullet_deleted == false)
			{

				///////////////////////////////////////////////////

				// CO SIE DZIEJE PO TRAFIENIU POCISKU ENEMY W GRACZA


				delete this->bullets.at(counter_bullet);   //  Usuwanie dynamicznie utworzonego bulleta

				this->bullets.erase(this->bullets.begin() + counter_bullet);   //  usuwanie bulleta z wektora

				bullet_deleted = true;

				this->gameSound->playSound("killPlayer", 5);

				if (this->player->getPlayerHp() > 0)
				{
					this->player->removeHp(1);
					this->gui->setGUIhp(this->player->getPlayerHp());
				}


				if (this->player->getPlayerHp() <= 0)
				{
					//this->gui->renderGameOver();
					// this->gameOver = true;
					//this->gameSound->pauseMusic("backgroundMusic");
				}

				break;

			}
		}
		++counter_bullet;
	}
}

void GameState::updateBulletEnemy(RenderTarget* target)
{
	unsigned counter_bullet = 0;

	unsigned counter_enemy = 0;
	bool bullet_deleted = false;

	//////////////////////////////////
	//
	// Enemy usuwany po zdrzeneniu z
	// bulletem gracza, bullet usuwany
	//
	//////////////////////////////////

	for (auto* bullet : this->bullets)
	{
		bool enemy_deleted = false;
		counter_enemy = 0;
		for (auto* enemy : this->enemies)
		{
			if (bullet->getBulletBounds().intersects(enemy->getEnemyBounds())) // Sprawdzanie czy bullet trafil w enemy 
			{
				if (bullet->bulletType != "enemyShot"  // jesli bullet nie jest od enemy (zeby enemy nie zabijali enemy)
					&& enemy_deleted == false
					&& bullet_deleted == false)
				{

					///////////////////////////////////////////////
					// 
					//	CO SIE DZIEJE PO TRAFIENIU BULLETA W ENEMY
					//
					//
					delete this->bullets.at(counter_bullet);
					this->bullets.erase(this->bullets.begin() + counter_bullet);
					bullet_deleted = true;
					enemy->removeEnemyHp(bullet->bulletStrenght);
					//
					if (enemy->getEnemyHp() <= 0)
					{
						delete this->enemies.at(counter_enemy);
						this->enemies.erase(this->enemies.begin() + counter_enemy);
						enemy_deleted = true;
					}
					//
					//
					this->gameSound->playSound("killEnemy", 1);
					this->player->addPoints(10);
					this->gui->setGUIpoints(this->player->getPoints());

					//
					/////////////////////////////////////////////////
					break;
				}
			}
			++counter_enemy;
		}
		++counter_bullet;
	}
}

void GameState::update(RenderTarget* target, const float& dt)
{
	this->updateMousePosition();
	this->updateInput(target, dt);
	this->updatePlayer(dt);
	this->updateBullets(dt);
	this->updateEnemies(target, dt);
	this->updateBackground(target, dt);
	this->updateBulletEnemy(target);
	this->updateBulletOutside(target);
	this->updateBulletPlayer(target);
	this->updateEnemyOutside(target);
}

void GameState::endState()
{
	cout << "End game state" << endl;
}

void GameState::updateMousePosition()
{
}

void GameState::checkForQuit()
{
	if (Keyboard::isKeyPressed((Keyboard::Escape)))
		this->quit = true;
}

const bool& GameState::getQuit() const
{
	return this->quit;
}

//////////////////////////////////////////////////
//
//				 RENDER SECTION 
//
//////////////////////////////////////////////////

void GameState::render(RenderTarget* target)
{
	this->background->render(target);  // Render world (background)

	this->player->render(target);

	// Render enemies
	for (auto* enemy : this->enemies)
	{
		enemy->render(target);
	}

	// Render bullets
	for (auto* bullet : this->bullets)
	{
		bullet->render(target);
	}

	this->gui->reder(target);
}