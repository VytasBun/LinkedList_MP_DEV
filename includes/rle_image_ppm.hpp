#include <iostream>
#include <string>

#include "node.hpp"
#include "pixel.hpp"

class RLEImagePPM {
public:
  RLEImagePPM() = default;
  RLEImagePPM(const std::string& filename);
  ~RLEImagePPM();

  unsigned int GetWidth() const { return width_; }
  unsigned int GetHeight() const { return height_; }
  unsigned int GetMaxColorValue() const { return max_color_value_; }

private:
  unsigned int width_;
  unsigned int height_;
  unsigned int max_color_value_;
}