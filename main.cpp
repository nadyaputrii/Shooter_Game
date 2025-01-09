#include <SFML/Graphics.hpp>

#include <time.h>
#include <vector>

#include "UI.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
	time_t t;
	srand((unsigned)time(&t));
	
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Shooter Game");
	
	sf::Music menuMusic; menuMusic.openFromFile("Music/y2mate.com-Horror-Game-Menu-Music-1.ogg");
    menuMusic.play(); menuMusic.setLoop(true);
	
	sf::Texture menuBGTex; menuBGTex.loadFromFile("Img/Menu BG.png");
	sf::Sprite menuBG; menuBG.setTexture(menuBGTex);
	menuBG.setPosition(-300, 50); menuBG.setScale(sf::Vector2f(2, 2));
	
	sf::Texture logoTex; logoTex.loadFromFile("Img/logo.png");
	sf::Sprite logo; logo.setTexture(logoTex);
	logo.setPosition(200, 50); logo.setScale(sf::Vector2f(2, 2));
	
	sf::Font menuFont;
	menuFont.loadFromFile("Font/stocky.ttf");
	sf::Text playText; playText.setFont(menuFont);		        
    
	playText.setPosition(sf::Vector2f(440 , 500));
	playText.setCharacterSize(100);
	playText.setString("PLAY");
	
	Hitbox playHB;
	playHB.setPosition(sf::Vector2f(440 , 520));
	playHB.setHitbox(sf::FloatRect(0, 0, 300, 90));
	
	float dt;
	sf::Clock dtClock;
	
	bool isStart;
	bool isPause;
	bool isDead;
	
//////////////////////////////////////////////////////////////////////////////////////// 
//MENU//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////// 

    while (window.isOpen() && !isStart)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
			    window.close(); return 0;
        	}
            if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Return) {
					isStart = true;
				}
			}
			
			if (playHB.getGlobalHitbox().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))){
				playText.setFillColor(sf::Color::Red);
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) isStart = true;
			}else{
				playText.setFillColor(sf::Color::White);	
			}
	                
    	}

        window.clear(sf::Color(25, 25, 25, 255));
        
        //Draw Menu
        window.draw(menuBG);
        window.draw(logo);
        window.draw(playHB);
        window.draw(playText);
        
        window.display();
    }
//////////////////////////////////////////////////////////////////////////////////////// 
//GAMEPLAY//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////// 

	menuMusic.stop();
    window.close();
    sf::RenderWindow play(sf::VideoMode(1080, 720), "Gameplay");
    
    sf::Music gpMusic; gpMusic.openFromFile("Music/Undertale-OST_-024-Bonetrousle.ogg");
    gpMusic.play(); gpMusic.setLoop(true);
    gpMusic.setVolume(50);
    
    sf::Texture background; background.loadFromFile("Img/Desert Bg.png");
	sf::Texture enemyTex;   enemyTex.loadFromFile("Img/Zombie Anim.png");
	
	sf::RectangleShape bg; bg.setTexture(&background);
	bg.setSize(sf::Vector2f(play.getSize().x, play.getSize().y));
	
	int maxAmmo = 10;
	
	UI ui(play, 10);
	Player player(100, maxAmmo, 1.5f);
	std::vector<Enemy> enemies;
	
	float spawnTime;
	int enemyCount;
	
	while(play.isOpen() && isStart){
		sf::Event pEvent;
		
		dt = dtClock.restart().asSeconds();
		
        while (play.pollEvent(pEvent))
        {
        	if (pEvent.type == sf::Event::Closed)
			{
				play.close();
			}
			if (pEvent.type == sf::Event::KeyPressed)
			{				
				///Player Reload
				if(pEvent.key.code == sf::Keyboard::R)
					if(player.canReload() && player.getCurrAmmo() < maxAmmo) player.Reload();
			}
			if (pEvent.type == sf::Event::MouseButtonPressed) {
                if (pEvent.mouseButton.button == sf::Mouse::Left) {
                ///Player
                	if(player.canShoot() && player.getCurrAmmo() > 0) {
                		player.Shoot();
                		for(int i = 0; i < enemyCount; i++)
                			if(enemies[i].enemyHB.getGlobalHitbox().contains(play.mapPixelToCoords(sf::Vector2i(pEvent.mouseButton.x, pEvent.mouseButton.y))))
                				 enemies[i].TakeDamage(1);
					}
                
                ///UI
                    if (ui.quitUI.getGlobalHitbox().contains(play.mapPixelToCoords(sf::Vector2i(pEvent.mouseButton.x, pEvent.mouseButton.y))))
                        play.close();
                }
            }
        }
        
        //Update
        ui.Update(play, player.getCurrHP());
		player.Update(dt);
		
		spawnTime -= dt;
		if(spawnTime <= 0){
			enemies.push_back(Enemy(&enemyTex, sf::Vector2u(10, 3), .2f, 3, (rand() % 3) + 1));
			enemies[enemyCount].SetPos(sf::Vector2f((rand() % 860) + 40, 450));
			enemyCount++;
			spawnTime = 5;
		}
		
		for(int i = 0; i < enemyCount; i++){
			enemies[i].Update(play, pEvent, player, .0002f, dt);
			if(enemies[i].bodyLifeTime <= 0){
				enemies.erase(enemies.begin() + i);	
				enemyCount--;
			} 
		}
		
		if(player.getCurrHP() <= 0)	play.close();
        
        play.clear();
        
        //background
        play.draw(bg);
        
        //Draw
		for(int i = enemyCount - 1; i >= 0; --i) enemies[i].Draw(play);
        
        ui.Draw(play, player.getCurrAmmo());
        
        play.display();
	}
	
	gpMusic.stop();
	sf::RenderWindow deadWindow(sf::VideoMode(1080, 720), "YoU ARe DeAd");
			
	sf::Font deadFont; deadFont.loadFromFile("Font/horrendo.ttf");
	sf::Text deadText; deadText.setFont(deadFont);
	deadText.setCharacterSize(100);
	deadText.setString("YoU ARe DeAd");
	deadText.setFillColor(sf::Color::Red);
	
	sf::SoundBuffer deadBuffer; deadBuffer.loadFromFile("SFX/HurtSFX4.wav");
	sf::Sound deadSFX; deadSFX.setBuffer(deadBuffer);
	deadSFX.play();
	
	while(deadWindow.isOpen() && !play.isOpen()){
		sf::Event dEvent;
		
		while(deadWindow.pollEvent(dEvent)){
			if (dEvent.type == sf::Event::Closed)
			{
				deadWindow.close();
			}
			if (dEvent.type == sf::Event::KeyPressed)
			{				
				if(dEvent.key.code == sf::Keyboard::Return) deadWindow.close();
			}
		}
		
		deadText.setPosition((rand() % 200 + 100), (rand() % 50 + 250));
					
		deadWindow.clear();
		
		deadWindow.draw(deadText);
		
		deadWindow.display();
	}
	
    return 0;
}
