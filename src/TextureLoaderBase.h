#pragma once

namespace sf
{

class TextureLoaderBase
{
public:
	TextureLoaderBase( const sf::AssetExtension& iExtension );
	virtual ~TextureLoaderBase() = default;

public:
	const sf::AssetExtension& getExtension() const;

public:
	virtual void loadTexture( const sf::AssetPath& filename, sf::Texture& iTexture ) = 0;

private:
	sf::AssetExtension extension_;
};

}