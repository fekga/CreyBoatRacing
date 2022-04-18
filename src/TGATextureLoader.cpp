#include "TGATextureLoader.h"

namespace sf
{

#pragma pack(push, 1)
struct tga_header_t
{
	sf::u8 idField;
	sf::u8 colorMapType;
	sf::u8 imageTypeCode;
	sf::u16 colorMapOrigin;
	sf::u16 colorMapLength;
	sf::u8 colorMapEntrySize;
	sf::u16 xOriginOfImage;
	sf::u16 yOriginOfImage;
	sf::u16 imageWidth;
	sf::u16 imageHeight;
	sf::u8 bpp;
	sf::u8 imageDescriptorByte;
};
#pragma pack(pop)

TGATextureLoader::TGATextureLoader( const sf::AssetExtension& iExtension )
: TextureLoaderBase( iExtension )
{

}

void TGATextureLoader::loadTexture( const sf::AssetPath& iFilename, sf::Texture& iTexture )
{ 
	SFASSERT( iFilename.length() > 0 );
	SFLOG( "Loading TGA texture:[", iFilename.toChar(), "]\n" );
	std::ifstream file( iFilename.toChar(), std::ios::binary );
	const bool result = file.is_open();
	SFASSERT( result );
	if ( result )
	{
		file.seekg( 0, std::ios_base::beg );
		file.seekg( 0, std::ios::end );
		size_t fsize = file.tellg();
		SFASSERT( fsize > 0 );
		file.seekg( 0, std::ios_base::beg );
		sf::u8* data = new sf::u8[ fsize ];
		SFASSERT( data );
		file.read( ( char* ) data, fsize );
		file.close();
		tga_header_t* header = ( tga_header_t* ) data;
	
		const sf::s32  bpp = header->bpp >> 3;
		const sf::u64 imageDataSize = header->imageWidth * header->imageHeight * bpp;
		sf::u8* pixels = &data[ sizeof( tga_header_t ) ];

		switch ( header->imageTypeCode )
		{
			//uncompressed
			case 2:
			{
				// Swaps The 1st And 3rd Bytes ( 'R'ed and 'B'lue )
				
				for ( sf::u64 i=0; i<imageDataSize; i+=bpp )
				{
					pixels[ i ] = pixels[ i ] ^ pixels[ i + 2 ];
					pixels[ i + 2 ] = pixels[ i ] ^ pixels[ i + 2 ];
					pixels[ i ]  = pixels[ i ] ^ pixels[ i + 2 ]; 
				}
				//*/
			}
			break;

			default:
			{
				SFASSERT( false );
			}
			break;
		}
		iTexture.generateGLTexture( header->imageWidth, header->imageHeight, bpp, pixels );
		delete[] data;
	}
}

}