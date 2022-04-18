#pragma once

namespace sf
{

using u8  = uint8_t;
using s8  = int8_t;
using u16 = uint16_t;
using s16 = int16_t;
using u32 = uint32_t;
using s32 = int32_t;
using u64 = uint64_t;
using s64 = int64_t;

#define GL_CLAMP_TO_EDGE 0x812F

struct AssetExtension
{
public:
	AssetExtension()
		: dataAsU32_( 0 )
	{
	}

	AssetExtension( const char* iExtension )
	{
		SFASSERT( iExtension );
		SFASSERT( strlen( iExtension ) < sizeof( data_ ) );
		strcpy_s( data_, sizeof( data_ ), iExtension );
	}

	void operator=( const char* iExtension )
	{
		SFASSERT( iExtension );
		SFASSERT( strlen( iExtension ) < sizeof( data_ ) );
		strcpy_s( data_, sizeof( data_ ), iExtension );
	}

	const bool operator==( const sf::AssetExtension& iOther ) const
	{
		return dataAsU32_ == iOther.dataAsU32_;
	}
private:
	union
	{
		char data_[4];
		sf::u32 dataAsU32_;
	};
};

constexpr sf::u32 ASSET_TAG_STR_SIZE = 16;
static_assert( ASSET_TAG_STR_SIZE % 8 == 0 );
constexpr sf::u32 ASSET_TAG_U64_SIZE = ASSET_TAG_STR_SIZE / 8;

class AssetTag
{
public:
	AssetTag()
	{
		memset( tagAsU64_, 0, sizeof( tagAsU64_ ) );
	}

	AssetTag( const char* iTag )
	{
		SFASSERT( iTag );
		memset( tagAsU64_, 0, sizeof( tagAsU64_ ) );
		strcpy_s( tag_, sf::ASSET_TAG_STR_SIZE, iTag );
	}

	void operator=( const sf::AssetTag& iOther )
	{
		memcpy_s( tagAsU64_, sizeof( tagAsU64_ ), iOther.tagAsU64_, sizeof( iOther.tagAsU64_ ) );
	}

	const bool operator==( const sf::AssetTag& iOther ) const
	{
		for ( sf::u32 i=0; i<sf::ASSET_TAG_U64_SIZE; ++i )
		{
			if ( tagAsU64_[ i ] != iOther.tagAsU64_[ i ] )
			{
				return false;
			}
		}
		return true;
	}

private:
	union
	{
		char tag_[sf::ASSET_TAG_STR_SIZE];
		sf::u64 tagAsU64_[sf::ASSET_TAG_U64_SIZE];
	};
};

class InputTag
{
private:
	enum KeyState
	{
		Idle = 0,
		Pressed,
		Repeat,
		Released
	};

public:
	InputTag()
	{
		tagAsU64_ = 0;
	}

	InputTag( const char* iTag, const int iKey )
	{
		SFASSERT( iTag );
		SFASSERT( strlen( iTag ) < sizeof( tag_ ) );
		tagAsU64_ = 0;
		strcpy_s( tag_, sizeof( tag_ ), iTag );
		key_ = iKey;
	}

	InputTag( const char* iTag )
	{
		SFASSERT( iTag );
		SFASSERT( strlen( iTag ) < sizeof( tag_ ) );
		tagAsU64_ = 0;
		strcpy_s( tag_, sizeof( tag_ ), iTag );
	}

	void operator=( const sf::InputTag& iOther )
	{
		tagAsU64_ = iOther.tagAsU64_;
	}

	const bool operator==( const sf::InputTag& iOther ) const
	{
		return tagAsU64_ == iOther.tagAsU64_;
	}

	void updateAction( const int iAction )
	{
		switch ( iAction )
		{
			case GLFW_PRESS:
				keyState_ = KeyState::Pressed;
			break;
			case GLFW_REPEAT:
				keyState_ = KeyState::Repeat;
			break;
			case GLFW_RELEASE:
				keyState_ = KeyState::Released;
			break;
		}
	}

	void finalize()
	{
		switch ( keyState_ )
		{
			case KeyState::Pressed:
				keyState_ = KeyState::Repeat;
			break;
			case KeyState::Released:
				keyState_ = KeyState::Idle;
			break;
		}
	}

	const int getKey() const
	{
		return key_;
	}

	const bool isPressed() const
	{
		return keyState_ == KeyState::Pressed;
	}

	const bool isRepeat() const
	{
		return keyState_ == KeyState::Repeat;
	}

	const bool isReleased() const
	{
		return keyState_ == KeyState::Released;
	}

private:
	union
	{
		char tag_[ sizeof( sf::u64 ) ];
		sf::u64 tagAsU64_;
	};
	int key_;
	KeyState keyState_ = KeyState::Idle;
};

}
