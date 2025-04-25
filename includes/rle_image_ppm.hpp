#ifndef RLE_IMAGE_PPM_HPP
#define RLE_IMAGE_PPM_HPP

#include <fstream>
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
              unsigned int height,
              unsigned int max_color_value);

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
  void Clear() {
    for (unsigned int r = 0; r < height_; r++) {
      Node* curr = image_[r];
      while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next_;
        delete temp;
      }
    }
    delete[] image_;
    image_ = nullptr;
  }
  void Copy(const RLEImagePPM& rhs) {
    width_ = rhs.width_;
    height_ = rhs.height_;
    max_color_value_ = rhs.max_color_value_;
    image_ = new Node*[height_];

    for (unsigned int r = 0; r < height_; r++) {
      Node* rhs_curr = rhs.image_[r];
      Node* curr = new Node(*rhs_curr);
      image_[r] = curr;
      rhs_curr = rhs_curr->next_;
      while (rhs_curr != nullptr) {
        curr->next_ = new Node(*rhs_curr);
        curr = curr->next_;
        rhs_curr = rhs_curr->next_;
      }
    }
  }
};
#endif