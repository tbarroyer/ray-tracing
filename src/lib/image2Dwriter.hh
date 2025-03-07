# pragma once

# include <iostream>
# include <string>
# include "color.hh"
# include "image2D.hh"

template <typename TValue>
class Image2DWriter {
public:
  typedef TValue Value;
  typedef Image2D<Value> Image;

  static bool write( Image & img, std::ostream & output, bool ascii );
};

template <typename TValue>
bool
Image2DWriter<TValue>::write( Image & img, std::ostream & output, bool ascii )
{
  return false;
}

/// Specialization for gray-level images.
template <>
class Image2DWriter<unsigned char> {
public:
  typedef unsigned char Value;
  typedef Image2D<Value> Image;

  static bool write( Image & img, std::ostream & output, bool ascii );
};

/// Specialization for color images.
template <>
class Image2DWriter<Color> {
public:
  typedef Color Value;
  typedef Image2D<Value> Image;

  static bool write( Image & img, std::ostream & output, bool ascii );
};



bool
Image2DWriter<unsigned char>::write( Image & img, std::ostream & output, bool ascii )
{
  typedef unsigned char GrayLevel;
  output << ( ascii ? "P2" : "P5" ) << std::endl;
  output << "# Generated by You !" << std::endl;
  output << img.w() << " " << img.h() << std::endl;
  output << "255" << std::endl;
  if ( ascii ) 
    {
      for ( Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    output << (int) *it << " ";
    }
  else 
    {
      for ( Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    output << (GrayLevel) *it;
    }
  return true;
}


bool
Image2DWriter<Color>::write( Image & img, std::ostream & output, bool ascii )
{
  output << ( ascii ? "P3" : "P6" ) << std::endl;
  output << "# Generated by You !" << std::endl;
  output << img.w() << " " << img.h() << std::endl;
  output << "255" << std::endl;
  if ( ascii ) 
    {
      for ( Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    { 
      Color c = *it;
      output << (int) (c.r()*255.0f) << " " << (int) (c.g()*255.0f) << " " << (int) (c.b()*255.0f) << " ";
    }
    }
  else 
    {
      for ( Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    { 
      Color c = *it;
          unsigned char red = (unsigned char) (c.r()*255.0f);
          unsigned char green = (unsigned char) (c.g()*255.0f);
          unsigned char blue = (unsigned char) (c.b()*255.0f);
      output << red << green << blue;
    }
    }
  return true;
}
