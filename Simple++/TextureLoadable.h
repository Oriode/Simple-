#pragma once

#include "Log.h"
#include "BasicLoadableIO.h"
#include "Math.h"
#include "Vector.h"
#include "String.h"
#include "Utility.h"
#include "Image.h"
#include "Texture.h"


namespace Graphic {

	template<typename T = unsigned char>
	class TextureLoadable : public BasicLoadableIO, public Texture<T> {
	public:
		enum LoadingType {
			EMPTY,	///When loaded the buffer is NOT initialized.
			FILE		///When loaded the file is opened and read.
		};


		///@brief Empty constructor, create an image unallocated of size (0:0)
		///@param format of the image
		TextureLoadable(typename Format format = Format::RGB);

		///@brief Constructor to create an not initialized image of specified size.
		///@param size size of the image to create.
		///@param format of the image
		TextureLoadable(const Math::vec2ui & size, typename Format format = Format::RGB);

		///@brief create a new image using a path to a file (only support official file format)
		TextureLoadable(const WString & filePath);

		///@brief copy constructor
		TextureLoadable(const TextureLoadable<T> & image);

		///@brief move constructor
		TextureLoadable(TextureLoadable<T> && image);

		~TextureLoadable();

		///@brief load this image from a buffer and a specified size.
		///@param dataBuffer buffer to copy inside the new image (the buffer has to have a size of at least size.x * size.y)
		///@param size size of the new image
		///@param format of the image
		///@param invertY if the image has to be flipped vertically or not.
		void setDatas(const T * dataBuffer, const Math::vec2ui & size, typename LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);


		///@brief clear this texture with a new size
		///@param size New size from the mipmap 0
		void clear(const Math::vec2ui & size);


		///@brief reset this image with a new size and a new format
		///@param size new size
		///@param format new format of the image
		void clear(const Math::vec2ui & size, typename Format format);

		///@brief generate the mipmaps from the actual lod 0
		///@template C type able to handle the sum of 4 type T
		template<typename C = unsigned short>
		void generateMipmaps();


		///@brief get the data buffer of this image
		///@param i number of mipmap (0 = original image)
		///@return data buffer
		const T * getDatas(typename Vector<_Image<T>>::Size i = 0) const;

		///@brief get the data buffer of this image
		///@param i number of mipmap (0 = original image)
		///@return data buffer
		T * getDatas(typename Vector<_Image<T>>::Size i = 0);


		///@brief get a pixel from this image
		///@param i mipmap level
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		const T * getPixel(typename Vector<_Image<T>>::Size i, unsigned int x, unsigned int y) const;


		///@brief set a pixel inside this image
		///@param i mipmap level
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@param p The pixel to set.
		void setPixel(typename Vector<_Image<T>>::Size i, unsigned int x, unsigned int y, const T * p);


		///@brief copy operator
		///@param image Image to copy
		Texture<T> & operator=(const Texture<T> & image);

		///@brief move operator
		///@param image Image to move from
		Texture<T> & operator=(Texture<T> && image);


		///@brief get the format of this image
		///@return format of this image (its castable in unsigned char to retrieve the number of components)
		typename Format getFormat() const;

	protected:
		///@brief function to be overloaded to set the action when reading from a stream.
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onRead(std::fstream * fileStream) override;

		///@brief function to be overloaded to set the action when writing from a stream.
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onWrite(std::fstream * fileStream) const override;


		///@brief function to be overloaded to add action during the loading process.
		virtual void onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		virtual void onUnload() override;


	private:
		Math::vec2ui size;	//If not loaded we have to keep the size of the mipmap 0
		typename Format format;
		WString fileName;
		LoadingType loadingType;
	};




}


#include "TextureLoadable.hpp"
