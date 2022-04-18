#include "TextureManager.h"

namespace sf
{

TextureManager::~TextureManager()
{
	cleanUp();
}

TextureLoaderBase* TextureManager::findTextureLoader( const sf::AssetExtension& ext ) const
{
	for ( int i=0; i<textureLoaders_.size(); ++ i )
	{
		if ( textureLoaders_[ i ]->getExtension() == ext )
		{
			return textureLoaders_[ i ].get();
		}
	}
	return nullptr;
}


sf::Texture* TextureManager::getTexture( const sf::AssetTag& iTag )
{
	for ( sf::u32 i=0; i<textures_.size(); ++i )
	{
		if ( textures_[ i ]->getTag() == iTag )
		{
			return textures_[ i ].get();
		}
	}
	SFASSERT( false );
	return nullptr;
}

void TextureManager::loadTexture( const sf::AssetTag& iTag, const sf::AssetPath& iFilename )
{
	const sf::AssetExtension ext = getExtension( iFilename );
	TextureLoaderBase* textureLoader = findTextureLoader( ext );
	SFASSERT( textureLoader != nullptr );
	textures_.push_back( std::make_unique< sf::Texture >() );
	textures_.back()->setTag( iTag );
	textureLoader->loadTexture( iFilename, *textures_.back() );
}

template< typename TEXTURE_LOADER >
void TextureManager::registerTextureLoader( const sf::AssetExtension& iExtension )
{
	textureLoaders_.push_back( std::make_unique< TEXTURE_LOADER >( iExtension ) );
}

void TextureManager::cleanUp()
{
	SFLOG( "Cleaning up textures...\n" );
	for ( auto& texture : textures_ )
	{
		texture->deleteGLTexture();
	}
	textures_.clear();
	textureLoaders_.clear();
}

}