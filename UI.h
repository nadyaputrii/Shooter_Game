#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

#include <vector>
#include "Hitbox.h"
#include "patch.h"

class UI
{
	private:
		sf::RectangleShape hpUI;
		sf::RectangleShape gunUI;
		sf::RectangleShape enemyUI;
		sf::CircleShape crosshair;
		
		std::vector<sf::RectangleShape> ammoUI;
		
		sf::Texture pistolTex;
    	sf::Texture ARTex;
		sf::Texture pAmmoTex;
		sf::Texture ARAmmoTex;
		
		sf::Texture quitTex;
		sf::Texture crosshairTex;
		
		sf::Font hpFont;
		
		sf::Text hpText;
		
	public:
		Hitbox quitUI;
		
		UI(sf::RenderWindow&, int);
		void Update(sf::RenderWindow&, float);
		void Draw(sf::RenderWindow&, int);
};

#endif
