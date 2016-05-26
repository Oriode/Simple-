///@file Image.h
///@brief Image Class with some drawing methods
///@author Cl�ment Gerber
///@date 19/04/2016 (DMY) 



#pragma once


#include "Log.h"
#include "BasicLoadableIO.h"
#include "Math.h"
#include "Vector.h"
#include "String.h"
#include "Utility.h"
#include "BasicIO.h"
#include "Gradient.h"
#include "BlendingFunc.hpp"





namespace Graphic {
	///@brief Image Class
	///@template T Type of one pixel
	///@template F Format of the image
	template<typename T = unsigned char>		
	class _Image : public BasicIO {
	public:

		enum class ConvolutionMode {NormalSize, ExtendedSize};
		enum class ConversionMode {Luminance, Trunquate, Alpha};


		
		///@brief copy constructor with an another storage type
		///@param image image to copy
		template<typename C>
		_Image(const _Image<C> & image);

		///@brief Empty constructor, create an image unallocated of size (0:0)
		///@param format of the image
		_Image(Format format = Format::RGB);

		///@brief Constructor to create an initialized image of specified size.
		///@param size size of the image to create.
		///@param format of the image
		_Image(const Math::Vec2<Size> & size, Format format = Format::RGB);

		///@brief create a new image data from a file stream.
		///@param fileStream Stream to read
		///@param format of the image
		_Image(std::fstream * fileStream);


		///@brief Constructor to create an image from a data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param format of the image
		///@param invertY if the image has to be flipped vertically or not.
		_Image(const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);

		///@brief copy constructor
		_Image(const _Image<T> & image);

		///@brief move constructor
		_Image(_Image<T> && image);

		~_Image();

		///@brief get the actual size (width:height) of the image
		///@return the actual size of this image
		const Math::Vec2<Size> & getSize() const;

		///@brief get the actual width of the image
		///@return actual width of this image
		Size getWidth() const;

		///@brief get the actual height of the image
		///@return actual height of this image
		Size getHeight() const;

		
		///@brief get the number of pixels of this image
		///@return number of pixels
		size_t getNbPixels() const;

		///@brief reset this image with a new size.
		///@param size new size
		void clear(const Math::Vec2<Size> & size);


		///@brief reset this image with a new size and a new format
		///@param size new size
		///@param format new format of the image
		void clear(const Math::Vec2<Size> & size, Format format);


		///@brief set the data from an another data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param invertY if the image has to be flipped vertically or not.
		void setDatas(const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);


		///@brief create a new image from this one with a size of width / 2 and height / 2
		///@return new image created from this one with an halved size.
		template<typename C = unsigned short>
		_Image<T> * createMipmap();					

		///@brief get the data buffer of this image 
		///@return data buffer
		const T * getDatas() const;


		///@brief get the data buffer of this image 
		///@return data buffer
		T * getDatas();



		///@brief get the data buffer of this image starting with the selected pixel
		///@return data buffer
		const T * getDatas(Size x, Size y) const;

		///@brief get the data buffer of this image starting with the selected pixel
		///@return data buffer
		T * getDatas(Size x, Size y);


		///@brief get a pixel from this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		const T * getPixel(Size x, Size y) const;

		///@brief get a pixel from this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		T * getPixel(Size x, Size y);


		///@brief get the offset of pixel from the beginning of the data
		///@param x X coordinate
		///@param y Y coordinate
		///@return offset to be added to go from the begining of the data (getData()) and the selected pixel
		size_t getDataOffset(Size x, Size y) const;



		///@brief set a pixel inside this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@param p The pixel to set.
		void setPixel(Size x, Size y, const T * p);



		///@brief copy operator with another type
		///@param image Image to copy
		template<typename C>
		_Image<T> & operator=(const _Image<C> & image);

		///@brief copy operator
		///@param image Image to copy
		_Image<T> & operator=(const _Image<T> & image);

		///@brief move operator
		///@param image Image to move from
		_Image<T> & operator=(_Image<T> && image);


		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(std::fstream * fileStream);

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(std::fstream * fileStream) const;

		///@brief get the format of this image
		///@return format of this image
		Format getFormat() const;


		///@brief  get the number of components per pixels of this image.
		///@return Number of components per pixels.
		inline unsigned int getNbComponents() const;


		///@brief Create a new Image from this one with a new format
		///@param newFormat Format of the new image
		///@param conversionMode Only used when converted to Format::R (Luminance : Use the average of the RGB channels, Trunquate : Use the R channel, Alpha : Use the Alpha Channel)
		///@return Image based of this one with a new format
		_Image<T> toFormat(Format newFormat, ConversionMode conversionMode = ConversionMode::Luminance) const;



		///@brief get the maximum value of a color component
		///@param maximum value of a component depending of the template type T
		inline static T getComponentMaxValue();


		/************************************************************************/
		/* Gradient                                                             */
		/************************************************************************/
		///@brief Compute the interpolation for horizontal gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation(const GradientHorizontal<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle) const;


		///@brief Compute the interpolation for vertical gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation(const GradientVertical<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle) const;


		///@brief Compute the interpolation for Linear gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation(const GradientLinear<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle) const;

		///@brief Compute the interpolation for Radial gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation(const GradientRadial<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle) const;

		/************************************************************************/
		/* Drawing methods                                                      */
		/************************************************************************/

		///@brief draw an anti aliased line from point p1 to point p2
		///@see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
		///@param l Line
		///@param color Color to draw
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawLine(const Line & l, const ColorR<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw an anti aliased line from point p1 to point p2
		///@see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
		///@param l Line
		///@param color Color to draw
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawLine(const Line & l, const ColorRGB<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw an anti aliased line from point p1 to point p2
		///@see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
		///@param l Line
		///@param color Color to draw
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawLine(const Line & l, const ColorRGBA<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief Set a functor to each pixels in the rectangle of this image
		///@param colorFunc Functor with operator() overloaded with 
		///					"inline void operator()(const Math::Vec2<Size> & p, Graphic::ColorR<T> & c);"
		///					"inline void operator()(const Math::Vec2<Size> & p, Graphic::ColorRGB<T> & c);"
		///					"inline void operator()(const Math::Vec2<Size> & p, Graphic::ColorRGBA<T> & c);"
		///														
		///@param rectangle Rectangle where to apply the functor.
		template<typename ColorFunc>
		void setPixels(ColorFunc & colorFunc, const Rectangle & rectangle);



		///@brief Set a functor to each pixels of this image
		///@param colorFunc Functor with operator() overloaded with 
		///					"void operator()(const Math::Vec2<Size> & p, Graphic::ColorR<T> & c);"
		///					"void operator()(const Math::Vec2<Size> & p, Graphic::ColorRGB<T> & c);"
		///					"void operator()(const Math::Vec2<Size> & p, Graphic::ColorRGBA<T> & c);"
		template<typename ColorFunc>
		void setPixels(ColorFunc & colorFunc);


		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param color Color to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle(const Rectangle & rectangle, const ColorR<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param color Color to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle(const Rectangle & rectangle, const ColorRGB<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param color Color to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle(const Rectangle & rectangle, const ColorRGBA<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		template<typename C, typename InterFunc>
		void drawRectangle(const Rectangle & rectangle, const GradientHorizontal<C, InterFunc> & gradient);

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle(const Rectangle & rectangle, const GradientLinear<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle(const Rectangle & rectangle, const GradientRadial<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc>
		void drawRectangle(const Rectangle & rectangle, const GradientHorizontal<C, InterFunc> & gradient, const BlendFunc & blendFunc);

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle(const Rectangle & rectangle, const GradientVertical<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param colorFunc functor that wille generate the color for each pixels, overloaded with operator() :
		///					"inline Graphic::ColorR<T> operator()(const Math::Vec2<Size> & p);"
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangleR(const Rectangle & rectangle, const ColorFunc & colorFunc, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param colorFunc functor that wille generate the color for each pixels, overloaded with operator() :
		///					"inline Graphic::ColorRGB<T> operator()(const Math::Vec2<Size> & p);"
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangleRGB(const Rectangle & rectangle, const ColorFunc & colorFunc, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param colorFunc functor that wille generate the color for each pixels, overloaded with operator() :
		///					"inline Graphic::ColorRGBA<T> operator()(const Math::Vec2<Size> & p);"
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangleRGBA(const Rectangle & rectangle, const ColorFunc & colorFunc, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief fill the complete image with a color.
		///param color pointer to a color with the same number of component of this image
		void fillImage(const T * color);

		///@brief fill the complete image with a color.
		///@param color pointer to a color with the same number of component of this image
		///@param rectangle Rectangle where to fill the color
		void fillImage(const T * color, const Rectangle & rectangle);

		///@brief fill the complete image with a color.
		///@param color R color
		void fillImage(const ColorR<T> & color);

		///@brief fill the complete image with a color.
		///@param color RGB color
		void fillImage(const ColorRGB<T> & color);

		///@brief fill the complete image with a color.
		///@param color RGBA color
		void fillImage(const ColorRGBA<T> & color);


		///@brief fill the complete image with a color.
		///@param color R color
		///@param rectangle Rectangle where to fill the color
		void fillImage(const ColorR<T> & color, const Rectangle & rectangle);

		///@brief fill the complete image with a color.
		///@param color RGB color
		///@param rectangle Rectangle where to fill the color
		void fillImage(const ColorRGB<T> & color, const Rectangle & rectangle);

		///@brief fill the complete image with a color.
		///@param color RGBA color
		///@param rectangle Rectangle where to fill the color
		void fillImage(const ColorRGBA<T> & color, const Rectangle & rectangle);

		///@brief fill the complete image with a horizontal gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage(const GradientHorizontal<C, InterFunc> & gradient, const Rectangle & rectangle);

		///@brief fill the complete image with a vertical gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage(const GradientVertical<C, InterFunc> & gradient, const Rectangle & rectangle);

		///@brief fill the complete image with a Linear gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage(const GradientLinear<C, InterFunc> & gradient, const Rectangle & rectangle);

		///@brief fill the complete image with a Radial gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage(const GradientRadial<C, InterFunc> & gradient, const Rectangle & rectangle);

		///@brief fill an another image into this one (no blending will be applied)
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void fillImage(const Point & point, const _Image<T> & image);

		///@brief fill an another image into this one (no blending will be applied)
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void fillImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image);

		
		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param image Another image to draw
		void drawImage(const Point & point, const _Image<T> & image);

		
		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image);
		

		///@brief draw an another image into this one with a custom blending function
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const BlendFunc & blendFunc = BlendingFunc::Normal());



		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage(const Point & point, const ColorR<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage(const Point & point, const ColorRGB<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage(const Point & point, const ColorRGBA<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage(const Point & point, const ColorR<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage(const Point & point, const ColorRGB<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage(const Point & point, const ColorRGBA<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param colorFunc Functor with operator() overloaded with 
		///					"inline Graphic::ColorR<T> operator()(const Math::Vec2<Size> & p) const;"
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawImageR(const Point & point, const ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param colorFunc Functor with operator() overloaded with 
		///					"inline Graphic::ColorRGB<T> operator()(const Math::Vec2<Size> & p) const;"
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawImageRGB(const Point & point, const ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param colorFunc Functor with operator() overloaded with 
		///					"inline Graphic::ColorRGBA<T> operator()(const Math::Vec2<Size> & p) const;"
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawImageRGBA(const Point & point, const ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());
		

		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const _Image<T> & image, const _Image<T> & maskImage);

		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage);


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());




		///@brief apply a symmetrical convolution filter (Gaussian blur for example)
		///@param filter Filter table (the table has to have an odd size)
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@return Image with the filter applied
		template<typename C, int N>
		_Image<T> applyFilter(const C(&filter)[N], ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null) const;



		///@brief apply a symmetrical convolution filter (Gaussian blur for example)
		///@param filter Filter table (the table has to have an odd size)
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@return Image with the filter applied
		template<typename C>
		_Image<T> applyFilter(const C * filter, size_t size, ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null) const;


		///@brief Clamp a rectangle inside the image
		///@param rectangle rectangle to be clamped
		///@return an unsigned rectangle clamped inside the image
		inline Math::Rectangle<Size> clampRectangle(const Rectangle & rectangle) const;

	protected:

		
	private:
		template<typename BlendFunc, typename C1, typename C2>
		void _drawLine(const Line & l, const C2 & color, unsigned int thickness, const BlendFunc & blendFunc);


		template<typename C1, typename C2>
		void _fillImage(const C2 & color);

		template<typename C1, typename C2>
		void _fillImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image);

		template<typename C1, typename C2, typename InterFunc>
		void _fillImage(const GradientHorizontal<C2, InterFunc> & color, const Rectangle & rectangle);

		template<typename BlendFunc, typename C1, typename C2>
		void _drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage, const BlendFunc & functor = BlendingFunc::Normal());

		template< typename ColorFunc, typename BlendFunc, typename C1, typename C2>
		void _drawImage(const Point & point, const ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal());

		template<typename BlendFunc, typename C1, typename C2>
		void _drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const BlendFunc & blendFunc);

		template<typename C1, typename C2>
		void _drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image);

		template<typename ColorFunc, typename BlendFunc, typename C1, typename C2>
		void _drawRectangleFunctor(const Rectangle & rectangle, const ColorFunc & colorFunctor, const BlendFunc & blendingFunctor = BlendingFunc::Normal());

		template<typename BlendFunc, typename C1, typename C2>
		void _drawRectangle(const Rectangle & rectangle, const C2 & color, const BlendFunc & functor = BlendingFunc::Normal());

		template<typename ColorFunc, typename C>
		void _setPixels(ColorFunc & functor, const Rectangle & rectangle);

		template<typename C1, typename C2, typename InterFunc>
		void _drawRectangle(const Rectangle & rectangle, const GradientHorizontal<C2, InterFunc> & gradient);

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle(const Rectangle & rectangle, const GradientLinear<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor);

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle(const Rectangle & rectangle, const GradientRadial<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor);

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle(const Rectangle & rectangle, const GradientHorizontal<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor);

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle(const Rectangle & rectangle, const GradientVertical<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor);

		void _allocateAndCopy(const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);

		static Format _loadingFormat2Format(LoadingFormat loadingFormat);


		template<typename C>
		_Image<T> _applyFilter(const C * filter, size_t size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<typename C>
		_Image<T> _applyFilterf(const C * filter, size_t size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<int N>
		_Image<T> _applyFilter(const float * filter, size_t size, ConvolutionMode convolutionMode , const ColorRGBA<T> & color) const;

		template<int N>
		_Image<T> _applyFilter(const double * filter, size_t size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<typename C = Math::vec3ui, typename PIX>
		_Image<T> * _createMipmap(_Image<T> * destinationImage);

		bool _read(std::fstream * fileStream);


		template<typename C, typename D>
		inline static void _castComponment(D * dest, const C * source);
		inline static void _castComponment(unsigned char * dest, const float * source);
		inline static void _castComponment(unsigned char * dest, const double * source);
		inline static void _castComponment(float * dest, const unsigned char * source);
		inline static void _castComponment(double * dest, const unsigned char * source);


		Format format;
		Math::Vec2<Size> size;
		size_t nbPixels;
		T * buffer;

	};





	typedef _Image<unsigned char> Image;
	typedef _Image<float> ImageF;



}


#include "Image.hpp"
