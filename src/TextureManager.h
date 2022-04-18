#pragma once

namespace sf
{

class TextureManager
{
public:
	TextureManager() = default;
	~TextureManager();

public:
	void loadTexture( const sf::AssetTag& iTag, const sf::AssetPath& iFilename );
	sf::Texture* getTexture( const sf::AssetTag& iTag );

	template< typename TEXTURE_LOADER >
	void registerTextureLoader( const sf::AssetExtension& iExtension );

	void cleanUp();

private:
	sf::TextureLoaderBase* findTextureLoader( const sf::AssetExtension& ext ) const;

private:
	std::vector< std::unique_ptr< sf::Texture > > textures_;
	std::vector< std::unique_ptr< sf::TextureLoaderBase > > textureLoaders_;
};


}