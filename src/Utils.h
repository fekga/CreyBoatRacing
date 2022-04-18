#pragma once

namespace sf
{

static sf::AssetExtension getExtension( const sf::AssetPath& iFilename )
{
	sf::AssetPath fname = iFilename;
	sf::AssetExtension ext;
	sf::s64 idx = fname.findLast( '.' );
	if ( idx != -1 )
	{
		fname.substring( idx + 1, fname.length() );
		ext = fname.toChar();
	}
	return ext;
}

}