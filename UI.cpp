#include "UI.h"

UI::UI(sf::RenderWindow& window, int ammoCount){
	
//Initialize
	pistolTex.loadFromFile		("Img/Pistol1.png");
	ARTex.loadFromFile			("Img/AR gun.png");
	pAmmoTex.loadFromFile		("Img/Pistol Ammo.png");
	ARAmmoTex.loadFromFile		("Img/AR bullet.png");
	quitTex.loadFromFile		("Img/Quit UI.png");
	crosshairTex.loadFromFile	("Img/crosshair.png");
	
	hpFont.loadFromFile("Font/stocky.ttf");

//Initialize Ammo
	for(int i = 0; i < ammoCount; i++){
		ammoUI.push_back(sf::RectangleShape(sf::Vector2f(27, 55)));
		ammoUI[i].setOrigin(ammoUI[i].getSize().x/2, ammoUI[i].getSize().y/2);
		ammoUI[i].setPosition(190 + (i * 30), 600);
		ammoUI[i].setFillColor(sf::Color::Yellow);
		ammoUI[i].setTexture(&pAmmoTex);
	}
	
	hpUI.setSize (sf::Vector2f(150, 150)); hpUI.setOrigin(hpUI.getSize().x/2, hpUI.getSize().y/2);
	gunUI.setSize(sf::Vector2f(296, 170)); gunUI.setOrigin(gunUI.getSize().x/2, gunUI.getSize().y/2);
	quitUI.setSize (sf::Vector2f(50, 50)); quitUI.setOrigin(quitUI.getSize().x/2, quitUI.getSize().y/2);
	
	hpText.setFont(hpFont);
	
	crosshair.setRadius(10); crosshair.setOrigin(sf::Vector2f(5, 5));
	
//Set Position
	hpUI.setPosition(80, 640);
	gunUI.setPosition(920, 640);
	quitUI.setPosition(30, 30);
	
	hpText.setPosition(50, 600);
	
	crosshair.setPosition(window.getSize().x/2, window.getSize().y/2);
	
//Color
	hpUI.setFillColor(sf::Color::Red);
	
//Texture
	gunUI.setTexture	(&pistolTex);
	crosshair.setTexture(&crosshairTex);
	quitUI.setTexture	(&quitTex);
	
//Hitbox
	quitUI.setHitbox (sf::FloatRect(0, 0, 50.f, 50.f));
}

void UI::Update(sf::RenderWindow& window, float playerHP){
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	crosshair.setPosition(sf::Vector2f(mousePos));
	hpText.setCharacterSize(40);
	hpText.setString(patch::to_string(playerHP));
}

void UI::Draw(sf::RenderWindow& window, int currAmmo){
	for(int i = 0; i < currAmmo; i++) window.draw(ammoUI[i]);
	
	window.draw(hpUI);
	window.draw(hpText);
	window.draw(gunUI);
	window.draw(enemyUI);
	window.draw(quitUI);
	window.draw(crosshair);
}
