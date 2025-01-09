#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>

class Hitbox : public sf::RectangleShape {
	private:
	    sf::FloatRect m_hitbox;
	    
	public:
	    void setHitbox(const sf::FloatRect& hitbox) { m_hitbox = hitbox; }
	    sf::FloatRect getGlobalHitbox() const { return getTransform().transformRect(m_hitbox); }
};

#endif
