#include "Enemy.h"

Enemy::Enemy(float pos_x, float pos_y, int type)
{

	this->initEnemy(type);
	this->setEnemyPosition(pos_x, pos_y);

}

Enemy::~Enemy()
{
	;
}

void Enemy::initEnemy(int type)
{
	if (type == 1)
	{

		if (!this->enemyTexture.loadFromFile("Textures/enemyTexture.png"))
		{
			cout << "LOAD ENEMY TEXTURE FAILED" << endl;
		}
		this->enemy.setTexture(this->enemyTexture);
		this->enemy.scale(0.3, 0.3);
		this->enemy.setColor(Color::White);

		mt19937 rng(rd());
		uniform_int_distribution<> gen(10, 30);
		this->direction.x = 0;
		this->direction.y = gen(rng) / 10;
		this->c_direction.x = this->direction.x;
		this->c_direction.y = this->direction.y;

		this->enemySpeed = 3;
		this->enemyStrenght = 1;
		this->enemyHp = 1.f;

	}

	else if (type == 2)
	{

		if (!this->enemyTexture.loadFromFile("Textures/enemyTexture.png"))
		{
			cout << "LOAD ENEMY TEXTURE FAILED" << endl;
		}
		this->enemy.setTexture(this->enemyTexture);
		this->enemy.scale(0.3, 0.3);
		this->enemy.setColor(Color::Green);

		mt19937 rng(rd());
		uniform_int_distribution<> gen(10, 30);
		this->direction.x = 0;
		this->direction.y = gen(rng) / 10;
		this->c_direction.x = this->direction.x;
		this->c_direction.y = this->direction.y;

		this->enemySpeed = 4;
		this->enemyStrenght = 2;
		this->enemyHp = 2.f;

	}

	else if (type == 3)
	{
		if (!this->enemyTexture.loadFromFile("Textures/enemyTexture.png"))
		{
			cout << "LOAD ENEMY TEXTURE FAILED" << endl;
		}
		this->enemy.setTexture(this->enemyTexture);
		this->enemy.scale(0.3, 0.3);
		this->enemy.setColor(Color::Red);

		mt19937 rng(rd());
		uniform_int_distribution<> gen(10, 30);
		this->direction.x = 0;
		this->direction.y = gen(rng) / 10;
		this->c_direction.x = this->direction.x;
		this->c_direction.y = this->direction.y;

		this->enemySpeed = 5;
		this->enemyStrenght = 3;
		this->enemyHp = 3.f;

	}

}

void Enemy::setEnemyPosition(float x, float y)
{
	this->enemy.setPosition(x, y);
}

const Vector2f Enemy::getEnemyPos() const
{
	return this->enemy.getPosition();

}

const FloatRect Enemy::getEnemyBounds() const
{
	return this->enemy.getGlobalBounds();

}

const int& Enemy::getEnemyHp() const
{
	return this->enemyHp;
}

const int& Enemy::getEnemyHpMax() const
{
	return this->enemyHpMax;
}

const int& Enemy::getEnemyStrenght() const
{
	return this->enemyStrenght;
}

void Enemy::removeEnemyHp(int hp)
{
	this->enemyHp -= hp;
}

void Enemy::update(RenderTarget* target, const float& dt)
{

	mt19937 rng(rd());
	uniform_int_distribution<> gen(0, 30);

//////////////////////////////////////////////////
//
//				LEFT ANIMATION
//
//////////////////////////////////////////////////

	if (gen(rng) == 1)
	{
		if (this->enemyLeftAnimation == false &&
			this->enemyRightAnimation == false &&
			this->enemy.getPosition().x > 200)
		{
			this->enemyLeftAnimation = true;
			generated = (gen(rng) / 20) + 1;
		}
	}

	if (this->enemyLeftAnimation == true &&
		this->enemyRightAnimation == false)
	{
		if (this->sinus >= 0 && this->sinus <= PI)
		{
			this->direction.x = -(this->generated * sin(this->sinus));
			this->sinus += 0.05;
		}

		if (this->sinus >= PI)
		{
			this->sinus = 0.f;
			this->direction.x = 0.f;
			this->enemyLeftAnimation = false;
		}
	}

//////////////////////////////////////////////////
//
//				RIGHT ANIMATION
//
//////////////////////////////////////////////////

	if (gen(rng) == 2)
	{
		if (this->enemyLeftAnimation == false 
			&& this->enemyRightAnimation == false
			&& static_cast<int>(this->enemy.getPosition().x) + this->enemy.getGlobalBounds().width < target->getSize().x - 100)
		{
			this->enemyRightAnimation = true;
			generated = (gen(rng) / 20) + 1;
		}
	}

	if (this->enemyRightAnimation == true && 
		this->enemyLeftAnimation == false)
	{
		if (this->sinus >= 0 && this->sinus <= PI)
		{
			this->direction.x = (this->generated * sin(this->sinus));
			this->sinus += 0.05;
		}

		if (this->sinus >= PI)
		{
			this->sinus = 0.f;
			this->direction.x = 0.f;
			this->enemyRightAnimation = false;
		}
	}

//////////////////////////////////////////////////
//
//				RE UP ANIMATION
//
//////////////////////////////////////////////////

	if (this->enemy.getPosition().y > target->getSize().y - 150
		&& this->enemyReUpAnimation == false
		&& this->enemyReDownAnimation == false)
	{
		this->enemyReUpAnimation = true;
		if (!this->CanReDown)
			this->CanReDown = true;
	}

	if (this->enemyReUpAnimation == true)
	{

		if (this->REsinus >= PI/2 && this->REsinus <= 1.5 * PI)
		{
			this->direction.y = (this->c_direction.y * sin(this->REsinus));
			this->REsinus += 0.05;
		}

		if (this->REsinus >= 1.5 * PI)
		{
			if (this->enemy.getPosition().y < target->getSize().y - 300)
			{
				this->enemyReUpAnimation = false;
				REsinus = PI / 2;
			}
		}
	}

//////////////////////////////////////////////////
//
//				RE DOWN ANIMATION
//
//////////////////////////////////////////////////

	if (this->enemy.getPosition().y < 100
		&& this->enemyReUpAnimation == false
		&& this->enemyReDownAnimation == false
		&& this->CanReDown == true)
	{
		this->enemyReDownAnimation = true;
	}

	if (this->enemyReDownAnimation == true)
	{

		if (this->REsinus >= PI / 2 && this->REsinus <= 1.5 * PI)
		{
			this->direction.y = (-this->c_direction.y * sin(this->REsinus));
			this->REsinus += 0.05;
		}

		if (this->REsinus >= 1.5 * PI)
		{
			if (this->enemy.getPosition().y < target->getSize().y - 300)
			{
				this->enemyReDownAnimation = false;
				this->CanReDown = false;
				REsinus = PI / 2;
			}
		}

	}

	///////////////
	this->enemy.move(this->enemySpeed * this->direction * dt * 50.f);
	///////////////

}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->enemy);
}
