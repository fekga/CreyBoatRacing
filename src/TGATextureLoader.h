#pragma once

namespace sf
{

class TGATextureLoader : public sf::TextureLoaderBase
{
public:
	TGATextureLoader( const sf::AssetExtension& iExtension );
	virtual ~TGATextureLoader() = default;

public:
	virtual void loadTexture( const sf::AssetPath& iFilename, sf::Texture& iTexture ) override;
};

}