#include "Enemy.h"

Enemy::Enemy(sf::Texture* tex, sf::Vector2u imageCount, float switchTime, float hp_init, float dmg) : 
	anim(tex, imageCount, switchTime)
{
	maxHp  = hp_init;
	currHp = maxHp;
	
	damage = dmg;
	
	row = 0;
	
	tex->setSmooth(true);
	graphics.setSize(sf::Vector2f(54, 96));
	graphics.setOrigin(27, 48);
	graphics.setTexture(tex);
	
	enemyHB.setSize(sf::Vector2f(54, 96));
	enemyHB.setOrigin(27, 48);
	enemyHB.setFillColor(sf::Color::Transparent);
	enemyHB.setHitbox(sf::FloatRect(7, 0, 40, 96));
	
	bodyLifeTime = .6f;
}

void Enemy::SetPos(sf::Vector2f position){
	enemyHB.setPosition(position.x, position.y);
	graphics.setPosition(position.x, position.y);
}

void Enemy::Update(sf::RenderWindow& window, sf::Event& event, Player& player, float speed, float dt){
	attackCD -= dt;
	anim.Update(row, dt);
	graphics.setTextureRect(anim.uvRect);
	if(currHp > 0){
		if(enemyHB.getScale().x < 10 && enemyHB.getScale().y < 10){
			enemyHB.scale(1 + speed, 1 + speed);
			graphics.scale(1 + speed, 1 + speed);
		}else{
			row = 1;
			if(attackCD <= 0) {
				player.TakeDamage(damage);
				attackCD = 1;
			}
		}
	}else{
		Dead();
		bodyLifeTime -= dt;
	}
}

void Enemy::TakeDamage(float dmg){
	currHp -= dmg;
}

void Enemy::Dead(){
	row = 2;
}

void Enemy::Draw(sf::RenderWindow& window){
	window.draw(graphics);
	window.draw(enemyHB);
}
