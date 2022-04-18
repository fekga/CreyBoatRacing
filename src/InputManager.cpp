#include "InputManager.h"

namespace sf
{

void InputManager::registerInputTag( const sf::InputTag& iInputTag )
{
	inputTags_.push_back( iInputTag );
}

void InputManager::setMousePosition( const glm::vec2& iPos )
{
	mousePos_ = iPos;
}

void InputManager::handleKey( int iKey, int iScancode, int iAction, int iMods )
{
	for ( auto& tag : inputTags_ )
	{
		if ( tag.getKey() == iKey )
		{
			tag.updateAction( iAction );
			break;
		}
	}
}

void InputManager::step()
{
	for ( auto& tag : inputTags_ )
	{
		tag.finalize();
	}
}

const glm::vec2 InputManager::getMousePos() const
{
	return mousePos_;
}

const bool InputManager::isPressed( const sf::InputTag& iTag ) const
{
	for ( auto& tag : inputTags_ )
	{
		if ( tag == iTag )
		{
			return tag.isPressed();
		}
	}
	return false;
}

const bool InputManager::isRepeat( const sf::InputTag& iTag ) const
{
	for ( auto& tag : inputTags_ )
	{
		if ( tag == iTag )
		{
			return tag.isRepeat();
		}
	}
	return false;
}

const bool InputManager::isReleased( const sf::InputTag& iTag ) const
{
	for ( auto& tag : inputTags_ )
	{
		if ( tag == iTag )
		{
			return tag.isReleased();
		}
	}
	return false;
}

}