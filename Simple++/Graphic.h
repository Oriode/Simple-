#pragma once


#include <limits>
#include "Image.h"
#include "Font.h"
#include "FreeImage.h"










namespace Graphic {


	template<size_t N>
	unsigned int computeGaussianKernel(unsigned int(&kernel)[N]);

	///@brief compute the Vertical/Horizontal Gaussian Kernel (I : Type of Values in your Kernel, N : Size of your kernel (has to be odd), C : Type of the data of the image (only for integer types) )
	///@param kernel table to be filled (has to be already allocated)
	///@param sigma Sigma used during the computation
	///@return The weight computed
	template<typename I, size_t N, typename C = unsigned char>
	I computeGaussianKernel(I(&kernel)[N], const float & sigma = float(N) / float(4));
	template<size_t N>
	float computeGaussianKernel(float(&kernel)[N], const float & sigma = float(N) / float(4));
	template<size_t N>
	double computeGaussianKernel(double(&kernel)[N], const double & sigma = double(N) / double(4));





	template<typename T, size_t N>
	T _computeGaussianKernelf(T(&kernel)[N], const T & sigma = T(N) / T(4));


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>(false));


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>(false));


	///@brief draw the text to the specified position without a blending, the character bitmap will directly by copied to the specified image
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>(false));



	///@brief draw the text to the specified position without a blending, the character bitmap will directly by copied to the specified image
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>(false));


	///@brief private function do not touch this.
	template<typename Func>
	void _drawText(const Font & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func);


	///@brief private function do not touch this.
	template<typename Func>
	void _drawText(const Font & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );
}



#include "Graphic.hpp"


