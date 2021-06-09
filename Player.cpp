#include "Player.h"

Player::Player()
{

	this->initVariables();
	this->initPlayer();

	cout << "Created player object" << endl;
	cout << "HP: " << this->hp << endl;

}

Player::~Player()
{
	;
}

void Player::initVariables()
{

	this->movementSpeed = 500.f;
	this->attackCooldownInMillis = 150;
	this->hpMax = 100;
	this->hp = this->hpMax;
	this->points = 0;
	this->level = 1;

	cout << "Initializated player variables" << endl;

}

void Player::initPlayer()
{

	if (!this->playerTexture.loadFromFile("Textures/playerTexture.png"))
	{
		cout << "LOAD PLAYER TEXTURE FAILED" << endl;
		system("pause");
	}

	this->player.setTexture(this->playerTexture);

	this->player.scale(0.19, 0.19);

	cout << "Player texture loaded" << endl;

	//this->player.setTextureRect(IntRect(0, 0, 64, 64));

}

const Vector2f& Player::getPlayerPos() const
{
	return this->player.getPosition();
}

const FloatRect Player::getPlayerBounds() const
{
	return this->player.getGlobalBounds();
}

const int& Player::getPlayerHp() const
{
	return this->hp;
}

const int& Player::getPlayerHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const RenderTarget* target)
{
	this->player.setPosition(((target->getSize().x / 2) - (this->player.getGlobalBounds().width / 2)), (target->getSize().y - this->player.getGlobalBounds().height - 50));
}

void Player::removeHp(const int hp)
{
	this->hp -= hp;
}

void Player::addHp(const int hp)
{
	this->hp += hp;
}

void Player::addPoints(const int points)
{
	this->points += points;
}

const int &Player::getPoints() const
{
	return this->points;
}

const int& Player::getLevel() const
{
	return this->level;
}

void Player::setLevel(const int level)
{
	this->level = level;
}

void Player::playerMove(const RenderTarget* target, const float& dt, const float dirX, const float dirY)
{ 
	if (this->player.getPosition().x > 0.f) // Jezeli gracz nie jest w lewej granicy ekranu
	{
		if ((this->player.getPosition().x + this->player.getGlobalBounds().width) < target->getSize().x) // Jezeli gracz nie jest w prawej granicy ekranu
		{
			this->player.move((this->movementSpeed * dirX * dt), (this->movementSpeed * dirY * dt)); // Porusz gracza w obojetnym kierunku
		}
		else if (dirX < 0) // Jesli gracz jest w prawej granicy ekranu ale chcemy go poruszyc w lewo
		{
			this->player.move((this->movementSpeed * dirX * dt), (this->movementSpeed * dirY * dt)); // Porusz gracza w lewo
		}
	}
	else if (dirX > 0) // Jezeli gracz jest w lewej granicy ekranu ale chcemy go poruszyc w prawo
	{
		this->player.move((this->movementSpeed * dirX * dt), (this->movementSpeed * dirY * dt)); // Porusz gracza w prawo
	}
}

void Player::updateCooldownAttack()
{
	if (this->secondAttackTime - this->firstAttackTime > this->attackCooldownInMillis)
		this->canAttack = true;
	else
		this->canAttack = false;
}

void Player::update(const float& dt)
{
	this->updateCooldownAttack();
}

void Player::render(RenderTarget* target)
{
	target->draw(this->player);
}
