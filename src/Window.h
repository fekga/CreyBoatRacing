#pragma once

namespace sf
{
	class Window
	{
	public:
		Window() = default;
		~Window() = default;

	public:
		void setup( const sf::u32 iWidth, const sf::u32 iHeight, const static_string< 512 >& iTitle )
		{
			windowWidth_ = iWidth;
			windowHeight_ = iHeight;
			title_ = iTitle;
		}

		const bool createWindow()
		{
			glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
			window_ = glfwCreateWindow( windowWidth_, windowHeight_, title_.toChar(), NULL, NULL );
			return window_;
		}		 

		const sf::u32 getWindowWidth() const
		{
			return windowWidth_;
		}

		const sf::u32 getWindowHeight() const
		{
			return windowHeight_;
		}

		GLFWwindow* getGLFWWindow() const
		{
			return window_;
		}

	private:
		GLFWwindow* window_ = nullptr;
		sf::u32 windowWidth_;
		sf::u32 windowHeight_;
		static_string< 512 > title_;
	};
}