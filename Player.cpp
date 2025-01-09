#include "Player.h"

Player::Player(float hp_init, int maxAmmo, float fireRate)
{
	pistolShotBuffer.loadFromFile("SFX/m1911-shootSFX.wav");
	pistolReloadBuffer.loadFromFile("SFX/m1911-reloadSFX.wav");
	hurtBuffer.loadFromFile("SFX/HurtSFX1.wav");
	
	maxHp  = hp_init;
	currHp = maxHp;	
	
	this->maxAmmo = maxAmmo;
	currAmmo 	  = maxAmmo;
	
	this->fireRate = fireRate;
}

void Player::Update(float dt){
	shootCD  -= dt;
	reloadCD -= dt;
}

void Player::Shoot(){
	static int x;
	pistolShotSFX.push_back(sf::Sound());
    pistolShotSFX[x].setBuffer(pistolShotBuffer);
	pistolShotSFX[x].play();
	currAmmo--;	x++; isShoot = true;
	shootCD = 1 / fireRate;
}

void Player::Reload(){
	pistolReloadSFX.setBuffer(pistolReloadBuffer);
	pistolReloadSFX.play();
	currAmmo = maxAmmo;
	reloadCD = 1;
}

void Player::TakeDamage(float dmg){
	static int x;
	hurtSFX.push_back(sf::Sound());
    hurtSFX[x].setBuffer(hurtBuffer);
	hurtSFX[x].play();
	currHp -= dmg;
}
