#pragma once

namespace sf
{

class Texture;

class Sprite
{
public:
	Sprite() = default;
	~Sprite() = default;

public:
	void 			setTexture( sf::Texture* iTexture, const sf::s32 iNumTileX = 1, const sf::s32 iNumTileY = 1 );
	void			setTile( const sf::s32 iTileX, const sf::s32 iTileY );
	void 			setAngle( const float iAngleInDegrees );
	float			getAngle() const;
	void			setRenderFlag( const sf::RenderFlag iRenderFlag );
	void 			setPosition( const glm::vec2 iPosition );
	glm::vec2 		getPosition() const;
	void 			render();

private:
	sf::Texture*	texture_ 	= nullptr;
	float			angle_ 		= 0.0f; // degrees
	sf::RenderFlag	renderFlag_ = sf::RenderFlag::NoEffect;
	sf::s32			numTileX_;
	sf::s32			numTileY_;
	sf::s32			tileX_;
	sf::s32			tileY_;
	glm::vec2		position_;
};

}