#include "Texture.h"

namespace sf
{

void Texture::generateGLTexture( const sf::u32 iWidth, const sf::u32 iHeight, const sf::u8 iBpp, const sf::u8* iPixels )
{
	SFASSERT( id_ == GL_INVALID_VALUE );
	SFASSERT( iPixels );
	width_ = iWidth;
	height_ = iHeight;
	glGenTextures( 1, &id_ );
	SFASSERT( id_ != GL_INVALID_VALUE );
	glBindTexture( GL_TEXTURE_2D, id_ );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	const int type = ( iBpp == 3 ) ? GL_RGB: GL_RGBA;
	glTexImage2D( GL_TEXTURE_2D, 0, type, width_, height_, 0, type, GL_UNSIGNED_BYTE, iPixels );
	glBindTexture( GL_TEXTURE_2D, NULL );
}

void Texture::deleteGLTexture()
{
	if ( id_ != GL_INVALID_VALUE )
	{
		glDeleteTextures( 1, &id_ );
		id_ = GL_INVALID_VALUE;
	}
}

sf::u32 Texture::getWidth() const
{
	return width_;
}

sf::u32 Texture::getHeight() const
{
	return height_;
}

void Texture::renderTexture( const glm::vec2& iPos, const RenderFlag iRenderFlag, const float iAngle, const float iSx, const float iSy, const float iBx, const float iBy )
{
	SFASSERT( id_ != GL_INVALID_VALUE );
	float sx = iSx;
	float sy = iSy;
	float bx = iBx;
	float by = iBy;
	const float xscale = 1.0f;
	const float yscale = 1.0f;
	GLfloat	w = ( GLfloat )( bx - sx ) * xscale;
	GLfloat h = ( GLfloat )( by - sy ) * yscale;
	
	float x1 = sx;
	float y1 = sy;
	float x2 = bx;
	float y2 = by;
	
	switch ( iRenderFlag )
	{
		case NoEffect:
		break;
		case Mirror:
		{
			y1 = by;
			y2 = sy;
		}
		break;
		case Flip:
		{
			x1 = bx;
			x2 = sx;
		}
		break;
		case MirrorFlip:
		{
			x1 = bx;
			y1 = by;
			x2 = sx;
			y2 = sy;
		}
		break;
	}

	const GLfloat coordinates[] = 
	{
		x1 / width_,	( h - y2 ) / height_,
		x2 / width_,	( h - y2 ) / height_,
		x1 / width_,	( h - y1 ) / height_,
		x2 / width_,	( h - y1 ) / height_
	};
	
	const GLfloat vertices[] = 
	{	
		/*pPoint.x*/ -w / 2, /*pPoint.y*/ -h / 2, 0.0,
		/*pPoint.x +*/ w / 2, /*pPoint.y*/ -h / 2, 0.0,
		/*pPoint.x*/ -w / 2, /*pPoint.y +*/ h / 2, 0.0,
		/*pPoint.x +*/ w / 2, /*pPoint.y +*/ h / 2, 0.0
	};
	
	const unsigned char colors[] = 
	{
		255, 255, 255, 255,
		255, 255, 255, 255,
		255, 255, 255, 255,
		255, 255, 255, 255,
	};
	
	glPushMatrix();
	glBindTexture( GL_TEXTURE_2D, id_ );
	glTranslatef( iPos.x, iPos.y, 0 );
	glRotatef( iAngle, 0, 0, 1 );
	glBegin( GL_QUADS );
		glColor4f( 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f );
		
		glTexCoord2f( coordinates[ 0 ], coordinates[ 1 ] );
		glVertex2f( -w / 2.0f, -h / 2.0f );
	
		glTexCoord2f( coordinates[ 4 ], coordinates[ 5 ] );
		glVertex2f( -w / 2.0f, h / 2.0f );
	
		glTexCoord2f( coordinates[ 2 ], coordinates[ 7 ] );
		glVertex2f( w / 2.0f, h / 2.0f );
	
		glTexCoord2f( coordinates[ 6 ], coordinates[ 3 ] );
		glVertex2f( w / 2.0f, -h / 2.0f );
	glEnd();
	glPopMatrix();
}

}