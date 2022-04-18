#pragma once

namespace sf
{

enum RenderFlag
{
	NoEffect = 0,
	Mirror,
	Flip,
	MirrorFlip,
};

class Texture
{
public:
	Texture() = default;
	virtual ~Texture() = default;

public:
	void generateGLTexture( const sf::u32 iWidth, const sf::u32 iHeight, const sf::u8 iBpp, const sf::u8* iPixels );
	void deleteGLTexture();

	void renderTexture( const glm::vec2& iPos, const RenderFlag iRenderFlag, const float iAngle, const float iSx, const float iSy, const float iBx, const float iBy ); 

	sf::u32 getWidth() const;
	sf::u32 getHeight() const;

	void setTag( const sf::AssetTag& iTag )
	{
		tag_ = iTag;
	}

	const sf::AssetTag& getTag() const
	{
		return tag_;
	}

private:
	sf::u32 width_ = 0;
	sf::u32 height_ = 0;
	GLuint id_ = GL_INVALID_VALUE;
	sf::AssetTag tag_;
};

}