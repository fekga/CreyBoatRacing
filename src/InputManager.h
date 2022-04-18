#pragma once

namespace sf
{

class InputManager
{
public:
	InputManager() = default;
	virtual ~InputManager() = default;

public:
	void registerInputTag( const sf::InputTag& iInputTag );
	void handleKey( int iKey, int iScancode, int iAction, int iMods );
	void setMousePosition( const glm::vec2& iPos );
	void step();

	const glm::vec2 getMousePos() const;
	const bool isPressed( const sf::InputTag& iTag ) const;
	const bool isRepeat( const sf::InputTag& iTag ) const;
	const bool isReleased( const sf::InputTag& iTag ) const;

private:
	glm::vec2 					mousePos_;
	std::vector< sf::InputTag > inputTags_;
};

}