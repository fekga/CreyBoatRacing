#include "TextureLoaderBase.h"

namespace sf
{

TextureLoaderBase::TextureLoaderBase( const sf::AssetExtension& iExtension )
: extension_( iExtension )
{

}

const sf::AssetExtension& TextureLoaderBase::getExtension() const
{
	return extension_;
}

}
