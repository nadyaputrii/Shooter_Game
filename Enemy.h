#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "Hitbox.h"
#include "Animation.h"
#include "Player.h"

class Enemy
{
	private:
		float currHp;
		float maxHp;
		
		float damage;
		
		sf::RectangleShape graphics;
		Animation anim;
		unsigned int row;
		
		float attackCD;
		
	public:
		Hitbox enemyHB;
		float bodyLifeTime;
		
		Enemy(sf::Texture*, sf::Vector2u, float, float, float);
		
		void SetPos(sf::Vector2f);
		void TakeDamage(float);
		void Dead();
		
		void Update(sf::RenderWindow&, sf::Event&, Player&, float, float);
		void Draw(sf::RenderWindow&);
		
		float getDamage()	{ return damage; };	
		float getCurrHP()	{ return currHp; };
};

#endif
