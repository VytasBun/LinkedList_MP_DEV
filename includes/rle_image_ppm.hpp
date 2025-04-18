#ifndef RLE_IMAGE_PPM_HPP
#define RLE_IMAGE_PPM_HPP

#include <iostream>
#include <string>

#include "node.hpp"
#include "pixel.hpp"

class RLEImagePPM {
public:
  RLEImagePPM() = default;
  // read from ppm image
  RLEImagePPM(const std::string& filename);
  // read from csv
  RLEImagePPM(const std::string& filename,
              unsigned int width,
              unsigned int height);

  // rule of three
  RLEImagePPM(const RLEImagePPM& rhs);
  RLEImagePPM& operator=(const RLEImagePPM& rhs);
  ~RLEImagePPM();

  // output
  void ToPPM(const std::string& filename) const;
  void ToCSV(const std::string& filename) const;

  // image transformations
  void CropLeft(unsigned int pixel_amt);
  void CropRight(unsigned int pixel_amt);
  void CropTop(unsigned int pixel_amt);
  void CropBottom(unsigned int pixel_amt);

  void FlipHorizontal();
  void FlipVertical();

  // getters
  unsigned int GetWidth() const { return width_; }
  unsigned int GetHeight() const { return height_; }
  unsigned int GetMaxColorValue() const { return max_color_value_; }

private:
  unsigned int width_ = 0;
  unsigned int height_ = 0;
  unsigned int max_color_value_ = 0;
  Node** image_ = nullptr;
};
#endif