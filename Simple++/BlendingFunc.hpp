#pragma once

namespace Graphic {




	namespace BlendingFunc {

		class Normal {
		public:
			//WITHOUT MASK
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			//WITH MASK
			template<typename T, typename A> void operator()(ColorR<T> & colorDest, const ColorR<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			template<typename T, typename A> void operator()(ColorR<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			template<typename T, typename A> void operator()(ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }

			template<typename T, typename A> void operator()(ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			template<typename T, typename A> void operator()(ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			template<typename T, typename A> void operator()(ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }

			template<typename T, typename A> void operator()(ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			template<typename T, typename A> void operator()(ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			template<typename T, typename A> void operator()(ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }


			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest = colorSrc;
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest.r = colorSrc;
				colorDest.g = colorSrc;
				colorDest.b = colorSrc;
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest.r = colorSrc;
				colorDest.g = colorSrc;
				colorDest.b = colorSrc;
				colorDest.a = _Image<I>::getComponentMaxValue();
			}

			/************************************************************************/
			/* RGB -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGB<I> & colorSrc) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				colorDest = I(( Bigger(colorSrc.r) + Bigger(colorSrc.g) + Bigger(colorSrc.b) ) / Bigger(3));
			}
			inline static void blendColor(ColorR<float> & colorDest, const ColorRGB<float> & colorSrc) {
				colorDest = ( colorSrc.r + colorSrc.g + colorSrc.b ) / float(3);
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorRGB<double> & colorSrc) {
				colorDest = ( colorSrc.r + colorSrc.g + colorSrc.b ) / double(3);
			}
			/************************************************************************/
			/* RGB -> RGB                                                           */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			/************************************************************************/
			/* RGB -> RGBA                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = _Image<I>::getComponentMaxValue();
			}

			/************************************************************************/
			/* RGBA -> R                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - Bigger(colorSrc.a);
				Bigger sum = Bigger(colorSrc.r) + Bigger(colorSrc.g) + Bigger(colorSrc.b);

				colorDest = I(( colorDest * oneMinusAlpha + ( sum / Bigger(3) ) * colorSrc.a ) / Utility::TypesInfos<I>::getMax());
			}

			inline static void blendColor(ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest = colorDest * oneMinusAlpha + ( sum / F(3.0) ) * colorSrc.a;
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest = colorDest * oneMinusAlpha + ( sum / F(3.0) ) * colorSrc.a;
			}


			/************************************************************************/
			/* RGBA -> RGB                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				
				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - Bigger(colorSrc.a);

				colorDest.r = I(( Bigger(colorDest.r) * oneMinusAlpha + Bigger(colorSrc.r) * Bigger(colorSrc.a) ) / Utility::TypesInfos<I>::getMax());
				colorDest.g = I(( Bigger(colorDest.g) * oneMinusAlpha + Bigger(colorSrc.g) * Bigger(colorSrc.a) ) / Utility::TypesInfos<I>::getMax());
				colorDest.b = I(( Bigger(colorDest.b) * oneMinusAlpha + Bigger(colorSrc.b) * Bigger(colorSrc.a) ) / Utility::TypesInfos<I>::getMax());

				/*
				float alpha = float(colorSrc.a);
				float oneMinusAlpha = 255.0f - alpha;
				colorDest.r = I(( float(colorDest.r) * oneMinusAlpha + float(colorSrc.r) * alpha ) / 255.0f);
				colorDest.g = I(( float(colorDest.g) * oneMinusAlpha + float(colorSrc.g) * alpha ) / 255.0f);
				colorDest.b = I(( float(colorDest.b) * oneMinusAlpha + float(colorSrc.b) * alpha ) / 255.0f);
				*/

			}
			inline static void blendColor(ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
			}
			inline static void blendColor(ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - Bigger(colorSrc.a);

				colorDest.r = I(( Bigger(colorDest.r) * oneMinusAlpha + Bigger(colorSrc.r) * Bigger(colorSrc.a) ) / Utility::TypesInfos<I>::getMax());
				colorDest.g = I(( Bigger(colorDest.g) * oneMinusAlpha + Bigger(colorSrc.g) * Bigger(colorSrc.a) ) / Utility::TypesInfos<I>::getMax());
				colorDest.b = I(( Bigger(colorDest.b) * oneMinusAlpha + Bigger(colorSrc.b) * Bigger(colorSrc.a) ) / Utility::TypesInfos<I>::getMax());
				colorDest.a = I(( Bigger(colorDest.a) * oneMinusAlpha ) / Utility::TypesInfos<I>::getMax() + Bigger(colorSrc.a));


			}
			inline static void blendColor(ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
				colorDest.a = colorDest.a * oneMinusAlpha + colorSrc.a;

			}
			inline static void blendColor(ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
				colorDest.a = colorDest.a * oneMinusAlpha + colorSrc.a;
			}


			/************************************************************************/
			/* WITH MASK                                                            */
			/************************************************************************/
			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorR<I> & colorDest, const ColorR<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger a = Bigger(alpha);
				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - a;
				colorDest = I(( Bigger(colorDest) * oneMinusAlpha + Bigger(colorSrc) * a ) / Utility::TypesInfos<I>::getMax());
			}
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorR<I> & colorSrc, float alpha) {
				float oneMinusAlpha = 1.0f - alpha;
				colorDest = I( float(colorDest) * oneMinusAlpha + float(colorSrc) * alpha );
			}
			inline static void blendColor(ColorR<float> & colorDest, const ColorR<float> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest = colorDest * oneMinusAlpha + colorSrc * alpha;
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorR<double> & colorSrc, double alpha) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest = colorDest * oneMinusAlpha + colorSrc * alpha;
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a = Bigger(alpha);
				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - a;
				Bigger tmp = Bigger(colorSrc) * a;

				colorDest.r = I(( Bigger(colorDest.r) * oneMinusAlpha + tmp ) / Utility::TypesInfos<I>::getMax());
				colorDest.g = I(( Bigger(colorDest.g) * oneMinusAlpha + tmp ) / Utility::TypesInfos<I>::getMax());
				colorDest.b = I(( Bigger(colorDest.b) * oneMinusAlpha + tmp ) / Utility::TypesInfos<I>::getMax());
			}
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				F tmp = F(colorSrc) * alpha;
				colorDest.r = I( F(colorDest.r) * oneMinusAlpha + tmp );
				colorDest.g = I( F(colorDest.g) * oneMinusAlpha + tmp );
				colorDest.b = I( F(colorDest.b) * oneMinusAlpha + tmp );
			}
			inline static void blendColor(ColorRGB<float> & colorDest, const ColorR<float> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				F tmp = colorSrc * alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
			}
			inline static void blendColor(ColorRGB<double> & colorDest, const ColorR<double> & colorSrc, double alpha) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - alpha;
				F tmp = colorSrc * alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a = Bigger(alpha);
				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - a;
				Bigger tmp = Bigger(colorSrc) * a;

				colorDest.r = I(( Bigger(colorDest.r) * oneMinusAlpha + tmp ) / Utility::TypesInfos<I>::getMax());
				colorDest.g = I(( Bigger(colorDest.g) * oneMinusAlpha + tmp ) / Utility::TypesInfos<I>::getMax());
				colorDest.b = I(( Bigger(colorDest.b) * oneMinusAlpha + tmp ) / Utility::TypesInfos<I>::getMax());
				colorDest.a = I(( Bigger(colorDest.a) * oneMinusAlpha ) / Utility::TypesInfos<I>::getMax() + alpha);

			}
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				F tmp = F(colorSrc) * alpha;
				colorDest.r = I( F(colorDest.r) * oneMinusAlpha + tmp );
				colorDest.g = I( F(colorDest.g) * oneMinusAlpha + tmp );
				colorDest.b = I( F(colorDest.b) * oneMinusAlpha + tmp );
				colorDest.a = I( F(colorDest.a) * oneMinusAlpha + alpha );
			}
			inline static void blendColor(ColorRGBA<float> & colorDest, const ColorR<float> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				F tmp = colorSrc * alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
				colorDest.a = ( colorDest.a * oneMinusAlpha + alpha );
			}
			inline static void blendColor(ColorRGBA<double> & colorDest, const ColorR<double> & colorSrc, double alpha) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - alpha;
				F tmp = colorSrc * alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
				colorDest.a = ( colorDest.a * oneMinusAlpha + alpha );
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a = Bigger(alpha);
				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - a;
				Bigger sum = ( Bigger(colorSrc.r) + Bigger(colorSrc.g) + Bigger(colorSrc.b) ) / Bigger(3);
				colorDest = I(( Bigger(colorDest) * oneMinusAlpha + sum * a ) / Utility::TypesInfos<I>::getMax());
			}
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				F sum = ( F(colorSrc.r) + F(colorSrc.g) + F(colorSrc.b) ) / F(3);
				colorDest = I( F(colorDest) * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor(ColorR<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				F sum = ( colorSrc.r + colorSrc.g + colorSrc.b ) / F(3);
				colorDest = ( colorDest * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - alpha;
				F sum = ( colorSrc.r + colorSrc.g + colorSrc.b ) / F(3);
				colorDest = ( colorDest * oneMinusAlpha + sum * alpha );
			}
			/************************************************************************/
			/* RGB -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a = Bigger(alpha);
				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - a;
				colorDest.r = I(( Bigger(colorDest.r) * oneMinusAlpha + Bigger(colorSrc.r) * a ) / Utility::TypesInfos<I>::getMax());
				colorDest.g = I(( Bigger(colorDest.g) * oneMinusAlpha + Bigger(colorSrc.g) * a ) / Utility::TypesInfos<I>::getMax());
				colorDest.b = I(( Bigger(colorDest.b) * oneMinusAlpha + Bigger(colorSrc.b) * a ) / Utility::TypesInfos<I>::getMax());
			}
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = I( F(colorDest.r) * oneMinusAlpha + F(colorSrc.r) * alpha );
				colorDest.g = I( F(colorDest.g) * oneMinusAlpha + F(colorSrc.g) * alpha );
				colorDest.b = I( F(colorDest.b) * oneMinusAlpha + F(colorSrc.b) * alpha );
			}
			inline static void blendColor(ColorRGB<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			inline static void blendColor(ColorRGB<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			/************************************************************************/
			/* RGB -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a = Bigger(alpha);
				Bigger oneMinusAlpha = Utility::TypesInfos<I>::getMax() - a;

				colorDest.r = I(( Bigger(colorDest.r) * oneMinusAlpha + Bigger(colorSrc.r) * a ) / Utility::TypesInfos<I>::getMax());
				colorDest.g = I(( Bigger(colorDest.g) * oneMinusAlpha + Bigger(colorSrc.g) * a ) / Utility::TypesInfos<I>::getMax());
				colorDest.b = I(( Bigger(colorDest.b) * oneMinusAlpha + Bigger(colorSrc.b) * a ) / Utility::TypesInfos<I>::getMax());
				colorDest.a = I(( Bigger(colorDest.a) * oneMinusAlpha ) / Utility::TypesInfos<I>::getMax() + alpha);
			}
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = I( F(colorDest.r) * oneMinusAlpha + F(colorSrc.r) * alpha );
				colorDest.g = I( F(colorDest.g) * oneMinusAlpha + F(colorSrc.g) * alpha );
				colorDest.b = I( F(colorDest.b) * oneMinusAlpha + F(colorSrc.b) * alpha );
				colorDest.a = I( F(colorDest.a) * oneMinusAlpha ) + alpha;
			}
			inline static void blendColor(ColorRGBA<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}
			inline static void blendColor(ColorRGBA<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}

			/************************************************************************/
			/* RGBA -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;

				SuperBigger a = SuperBigger(alpha) * SuperBigger(colorSrc.a);
				SuperBigger oneMinusAlpha = Utility::TypesInfos<Bigger>::getMax() - a;
				SuperBigger sum = ( SuperBigger(colorSrc.r) + SuperBigger(colorSrc.g) + SuperBigger(colorSrc.b) ) / SuperBigger(3);
				colorDest = I(( SuperBigger(colorDest) * oneMinusAlpha + sum * a ) / Utility::TypesInfos<Bigger>::getMax());
			}
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, float alpha) {
				typedef float F;
				alpha *= F(colorSrc.a) / Utility::TypesInfos<I>::getMax();
				F oneMinusAlpha = F(1.0) - alpha;
				F sum = ( F(colorSrc.r) + F(colorSrc.g) + F(colorSrc.b) ) / F(3);
				colorDest = I( F(colorDest) * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor(ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha) {
				typedef float F;
				alpha *= colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				F sum = ( colorSrc.r + colorSrc.g + colorSrc.b ) / F(3);
				colorDest = ( colorDest * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha) {
				typedef double F;
				alpha *= colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				F sum = ( colorSrc.r + colorSrc.g + colorSrc.b ) / F(3);
				colorDest = ( colorDest * oneMinusAlpha + sum * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;
				SuperBigger a = SuperBigger(alpha) * SuperBigger(colorSrc.a);
				SuperBigger oneMinusAlpha = Utility::TypesInfos<Bigger>::getMax() - a;
				colorDest.r = I(( SuperBigger(colorDest.r) * oneMinusAlpha + SuperBigger(colorSrc.r) * a ) / Utility::TypesInfos<Bigger>::getMax());
				colorDest.g = I(( SuperBigger(colorDest.g) * oneMinusAlpha + SuperBigger(colorSrc.g) * a ) / Utility::TypesInfos<Bigger>::getMax());
				colorDest.b = I(( SuperBigger(colorDest.b) * oneMinusAlpha + SuperBigger(colorSrc.b) * a ) / Utility::TypesInfos<Bigger>::getMax());
			}
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, float alpha) {
				typedef float F;
				alpha *= F(colorSrc.a) / Utility::TypesInfos<I>::getMax();
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = I( F(colorDest.r) * oneMinusAlpha + F(colorSrc.r) * alpha );
				colorDest.g = I( F(colorDest.g) * oneMinusAlpha + F(colorSrc.g) * alpha );
				colorDest.b = I( F(colorDest.b) * oneMinusAlpha + F(colorSrc.b) * alpha );
			}
			inline static void blendColor(ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha) {
				typedef float F;
				alpha *= colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			inline static void blendColor(ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha) {
				typedef double F;
				alpha *= colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;
				SuperBigger a = SuperBigger(alpha) * SuperBigger(colorSrc.a);
				SuperBigger oneMinusAlpha =  Utility::TypesInfos<Bigger>::getMax() - a;
				colorDest.r = I(( SuperBigger(colorDest.r) * oneMinusAlpha + SuperBigger(colorSrc.r) * a ) / Utility::TypesInfos<Bigger>::getMax());
				colorDest.g = I(( SuperBigger(colorDest.g) * oneMinusAlpha + SuperBigger(colorSrc.g) * a ) / Utility::TypesInfos<Bigger>::getMax());
				colorDest.b = I(( SuperBigger(colorDest.b) * oneMinusAlpha + SuperBigger(colorSrc.b) * a ) / Utility::TypesInfos<Bigger>::getMax());
				colorDest.a = I(( SuperBigger(colorDest.a) * oneMinusAlpha ) / Utility::TypesInfos<Bigger>::getMax() + alpha);
			}
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, float alpha) {
				typedef float F;
				alpha *= F(colorSrc.a) / Utility::TypesInfos<I>::getMax();
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = I( F(colorDest.r) * oneMinusAlpha + F(colorSrc.r) * alpha );
				colorDest.g = I( F(colorDest.g) * oneMinusAlpha + F(colorSrc.g) * alpha );
				colorDest.b = I( F(colorDest.b) * oneMinusAlpha + F(colorSrc.b) * alpha );
				colorDest.a = I( F(colorDest.a) * oneMinusAlpha + Utility::TypesInfos<I>::getMax() * alpha);
			}
			inline static void blendColor(ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha) {
				typedef float F;
				alpha *= colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}
			inline static void blendColor(ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha) {
				typedef double F;
				alpha *= colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}

		};





















		class None {
		public:
			//WITHOUT MASK
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			//WITH MASK
			//template<typename T, typename A> void operator()(ColorR<T> & colorDest, const ColorR<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			//template<typename T, typename A> void operator()(ColorR<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			//template<typename T, typename A> void operator()(ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }

			//template<typename T, typename A> void operator()(ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			//template<typename T, typename A> void operator()(ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			//template<typename T, typename A> void operator()(ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }

			//template<typename T, typename A> void operator()(ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			//template<typename T, typename A> void operator()(ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }
			//template<typename T, typename A> void operator()(ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha) const { blendColor(colorDest, colorSrc, alpha); }


			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest = colorSrc;
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest.r = colorSrc;
				colorDest.g = colorSrc;
				colorDest.b = colorSrc;
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest.r = colorSrc;
				colorDest.g = colorSrc;
				colorDest.b = colorSrc;
				colorDest.a = _Image<I>::getComponentMaxValue();
			}

			/************************************************************************/
			/* RGB -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGB<I> & colorSrc) {
				colorDest = colorSrc.r;
			}
			/************************************************************************/
			/* RGB -> RGB                                                           */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			/************************************************************************/
			/* RGB -> RGBA                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = _Image<I>::getComponentMaxValue();
			}

			/************************************************************************/
			/* RGBA -> R                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				colorDest = colorSrc.r;
			}
			/************************************************************************/
			/* RGBA -> RGB                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = colorSrc.a;


			}
		};







	}



}
