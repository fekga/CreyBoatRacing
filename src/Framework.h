#pragma once

namespace sf
{
	template< typename TGAME >
	class Framework
	{
	private:
		struct Asset
		{
			sf::AssetTag 	asset_tag_;
			sf::AssetPath 	filename_;
		};

	public:
		Framework() = default;
		~Framework() = default;
		Framework( const Framework& ) = delete;
		Framework& operator=( const Framework& ) = delete;

	public:
		const bool 	init();
		void 		loop();
		void		shouldClose();
		void 		terminate();

		const bool 			loadJSONConfig( std::vector< Asset >& oAssetList );
		void 				loadTextures( std::vector< Asset >& iAssetList );
		const sf::Window& 	getWindow() const;
		sf::TextureManager& getTextureManager();
		sf::InputManager&	getInputManager();

	private:
		sf::Window 			window_;
		TGAME 				game_;
		sf::TextureManager 	textureManager_;
		sf::InputManager	inputManager_;
	};
}