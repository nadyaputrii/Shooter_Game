#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

class Player
{
	private:
		float currHp;
		float maxHp;
		
		int currAmmo;
		int maxAmmo;
		float fireRate;
		float shootCD;
		float reloadCD;
		
		sf::SoundBuffer pistolShotBuffer;
		sf::SoundBuffer pistolReloadBuffer;
		sf::SoundBuffer hurtBuffer;
		
		std::vector<sf::Sound> pistolShotSFX;
		std::vector<sf::Sound> hurtSFX;
		
		sf::Sound pistolReloadSFX;
		
	public:		
		Player(float, int, float);
		void Update(float);
		
		void Shoot();
		void Reload();
		
		void TakeDamage(float);
		
		bool canShoot() 	{ return shootCD  < 0 ? true : false; };
		bool canReload()	{ return reloadCD < 0 ? true : false; };
		bool isDead()		{ return currHp   < 0 ? true : false; };
		bool isShoot;

		float getCurrHP()	{ return currHp;   };
		int   getCurrAmmo() { return currAmmo; };
};

#endif
