#pragma once

namespace sf
{

template < sf::s64 TSIZE >
class static_string
{
public:
	static_string()
	: size_( TSIZE )
	, length_( 0 )
	{
		data_[ 0 ] = 0;
	}

	static_string( const char* p_Chars )
		: size_( TSIZE )
		, length_( 0 )
	{
		data_[ 0 ] = 0;
		set( p_Chars );
	}

	virtual ~static_string() = default;

public:
	const sf::s64 length() const
	{
		return length_;
	}

	void set( const char* p_Chars, const sf::s64 p_Len )
	{
		SFASSERT( p_Chars );
		if ( p_Len == 0 )
		{
			data_[ 0 ] = 0;
			size_ = 0;
			length_ = 0;
		}

		SFASSERT( size_ > p_Len );
		for ( sf::s64 i = 0; i < p_Len; ++i )
		{
			data_[ i ] = p_Chars[ i ];
		}

		data_[ p_Len ] = 0;
		length_ = p_Len;
	}

	void unify()
	{
		for ( sf::s64 i = 0; i < size_; ++i )
		{
			if ( data_[ i ] == '\\' )
			{
				data_[ i ] = '/';
			}
		}
	}

	void set( const char* p_Chars )
	{
		SFASSERT( p_Chars );
		
		sf::s64 cnt = 0;
		while ( *p_Chars != 0 )
		{
			SFASSERT( cnt < TSIZE );
			data_[ cnt ] = *p_Chars;
			++cnt;
			++p_Chars;
		}

		length_ = cnt;
		data_[ length_ ] = 0;
	}

	void substring( const sf::s64 p_From, const sf::s64 p_To )
	{
		SFASSERT( p_From <= p_To );
		SFASSERT( p_To < size_ );
		
		for ( sf::s64 i=p_From; i<=p_To; ++i )
		{
			data_[ i - p_From ] = data_[ i ];
		}

		length_			= p_To - p_From;
		data_[length_]	= 0;
	}

	const sf::s64 findLast( const char p_Char ) const
	{
		if ( length_ == 0 )
		{
			return -1;
		}

		for ( sf::s64 i = length_ - 1; i >= 0 ; --i )
		{
			const char c = data_[ i ];
			
			if ( c == p_Char )
			{
				return i;
			}
		}

		return -1;
	}

	const bool startsWith( const char* p_String ) const
	{
		sf::s64 cnt = 0;
		while ( *p_String != 0 && cnt < length_ )
		{
			char c = *p_String;
			if ( c != data_[ cnt ] )
			{
				return false;
			}
			++cnt;
			++p_String;
		}

		return true;
	}

	static_string& operator+=( const static_string& p_OtherString )
	{
		return ( *this ) += p_OtherString.ToChar();
	}

	static_string& operator+=( const char* p_Chars )
	{
		const sf::s64 len = getCharsLen( p_Chars );
		const sf::s64 newLen = len + length_;
		
		if ( newLen < length_ )
		{
			for ( sf::s64 i = 0; i < len; ++i )
			{
				data_[ length_ ] = p_Chars[ i ];
				++length_;
			}

			data_[ length_ ] = 0;
		}

		return *this;
	}

	const char lastChar() const
	{
		if ( isEmpty() )
		{
			return 0;
		}

		return data_[ length_ - 1 ];
	}

	const bool isEmpty() const
	{
		return length_ <= 0;
	}

	const char* toChar() const
	{
		return data_;
	}

	const bool operator==( const static_string< TSIZE >& p_OtherString ) const
	{
		if ( length_ != p_OtherString.length_ )
		{
			return false;
		}

		for ( sf::s64 i=length_-1; i>=0; --i )
		{
			if ( data_[ i ] != p_OtherString.data_[ i ] )
			{
				return false;
			}
		}

		return true;
	}

private:
	const sf::s64 getCharsLen( const char* p_Chars ) const
	{
		const char* c = p_Chars;
		sf::s64 len = 0;
		while (*c != 0)
		{
			++c;
			++len;
		}

		return len;
	}

private:
	char		data_[ TSIZE ];
	sf::s64		size_;
	sf::s64		length_;
};

using AssetPath = static_string< 1024 >;

}