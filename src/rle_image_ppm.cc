#include "rle_image_ppm.hpp"
RLEImagePPM::RLEImagePPM(const std::string& filename) {
  std::ifstream ifs{filename};
  if (!ifs.is_open()) {
    throw std::runtime_error("file could not open");
  }
  std::string throw_away;
  std::getline(ifs, throw_away);
  ifs >> width_;
  ifs >> height_;
  ifs >> max_color_value_;
  image_ = new Node*[height_];

  for (unsigned int row = 0; row < height_; row++) {
    Node* curr = nullptr;
    for (unsigned int col = 0; col < width_; col++) {
      if (!ifs.good()) {
        throw std::runtime_error("ppm file has too little data");
      }
      int r, g, b;
      ifs >> r >> g >> b;
      Pixel p(r, g, b);
      if (col == 0) {
        curr = new Node(p);
        image_[row] = curr;
        continue;
      }
      if (curr->pixel_ == p) {
        curr->count_++;
      } else {
        curr->next_ = new Node(p);
        curr = curr->next_;
      }
    }
  }
}
RLEImagePPM::RLEImagePPM(const std::string& filename,
                         unsigned int width,
                         unsigned int height,
                         unsigned int max_color_value) {
  // doesnt make sense atm???
  width_ = width;
  height_ = height;
  max_color_value_ = max_color_value;
  std::ifstream ifs{filename};
  if (!ifs.is_open()) {
    throw std::runtime_error("file could not open");
  }

  image_ = new Node*[height_];
  for (unsigned int row = 0; row < height_; row++) {
    Node* curr = nullptr;
    int count = static_cast<int>(width_);
    while (ifs.good()) {
      if (count < 0) {
        throw std::runtime_error("Encoding is invalid with the width");
      }
      if (count == 0) {
        break;
      }
      char throw_away;
      int r, g, b;
      unsigned int c;
      ifs >> throw_away >> r >> g >> b >> throw_away >> throw_away >> c >>
          throw_away;
      Pixel p(r, g, b);
      Node* n = new Node(p, c);
      if (count == static_cast<int>(width_)) {
        image_[row] = n;
        curr = n;
        count -= static_cast<int>(c);
      } else {
        curr->next_ = n;
        curr = n;
        count -= static_cast<int>(c);
      }
    }
  }
}
RLEImagePPM::RLEImagePPM(const RLEImagePPM& rhs) { Copy(rhs); }
RLEImagePPM& RLEImagePPM::operator=(const RLEImagePPM& rhs) {
  if (&rhs == this) {
    return *this;
  }
  Clear();
  Copy(rhs);
  return *this;
}
RLEImagePPM::~RLEImagePPM() { Clear(); }
void RLEImagePPM::ToPPM(const std::string& filename) const {
  std::ofstream ofs{filename};
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << max_color_value_ << std::endl;
  for (unsigned int r = 0; r < height_; r++) {
    Node* curr = image_[r];
    while (curr != nullptr) {
      for (unsigned int i = 0; i < curr->count_; i++) {
        ofs << curr->pixel_.GetRed() << " " << curr->pixel_.GetGreen() << " "
            << curr->pixel_.GetBlue() << " ";
      }
      curr = curr->next_;
    }
    ofs << std::endl;
  }
}
void RLEImagePPM::ToCSV(const std::string& filename) const {
  std::ofstream ofs{filename};
  for (unsigned int r = 0; r < height_; r++) {
    Node* curr = image_[r];
    while (curr != nullptr) {
      ofs << '(' << curr->pixel_.GetRed() << " " << curr->pixel_.GetGreen()
          << " " << curr->pixel_.GetBlue() << ")," << curr->count_ << ",";
      curr = curr->next_;
    }
    ofs << std::endl;
  }
}
void RLEImagePPM::CropLeft(unsigned int pixel_amt) {
  auto crop_row = [pixel_amt](Node*& head) {
    Node* curr = head;
    int count = static_cast<int>(pixel_amt);
    while (count > 0) {
      if (count < static_cast<int>(curr->count_)) {
        curr->count_ -= count;
        break;
      }
      if (count == static_cast<int>(curr->count_)) {
        Node* temp = curr;
        curr = curr->next_;
        delete temp;
        break;
      }
      count -= static_cast<int>(curr->count_);
      Node* temp = curr;
      curr = curr->next_;
      delete temp;
    }
    head = curr;
  };
  if (pixel_amt >= width_) {
    throw std::runtime_error("invalid crop amount");
  }
  for (unsigned int r = 0; r < height_; r++) {
    crop_row(image_[r]);
  }
  width_ -= pixel_amt;
}
void RLEImagePPM::CropRight(unsigned int pixel_amt) {
  auto crop_row = [this, pixel_amt](Node*& head) {
    Node* curr = head;
    int count = static_cast<int>(width_ - pixel_amt);
    Node* prev = nullptr;
    while (count > 0) {
      if (static_cast<int>(curr->count_) <= count) {
        count -= curr->count_;
        prev = curr;
        curr = curr->next_;
        continue;
      }
      if (static_cast<int>(curr->count_) > count) {
        curr->count_ = count;
        prev = curr;
        curr = curr->next_;
        break;
      }
    }
    prev->next_ = nullptr;
    while (curr != nullptr) {
      Node* temp = curr;
      curr = curr->next_;
      delete temp;
    }
  };
  if (pixel_amt >= width_) {
    throw std::runtime_error("invalid crop amount");
  }
  for (unsigned int r = 0; r < height_; r++) {
    crop_row(image_[r]);
  }
  width_ -= pixel_amt;
}
void RLEImagePPM::CropTop(unsigned int pixel_amt) {
  if (pixel_amt >= height_) {
    throw std::runtime_error("invalid crop amount");
  }
  Node** next_image = new Node*[height_ - pixel_amt];
  for (unsigned int r = 0; r < pixel_amt; r++) {
    Node* curr = image_[r];
    while (curr != nullptr) {
      Node* temp = curr;
      curr = curr->next_;
      delete temp;
    }
  }
  for (unsigned int r = pixel_amt; r < height_; r++) {
    next_image[r - pixel_amt] = image_[r];
  }
  delete[] image_;
  image_ = next_image;
  height_ = height_ - pixel_amt;
}
void RLEImagePPM::CropBottom(unsigned int pixel_amt) {
  if (pixel_amt >= height_) {
    throw std::runtime_error("invalid crop amount");
  }
  Node** next_image = new Node*[height_ - pixel_amt];
  for (unsigned int r = 0; r < height_; r++) {
    if (r < height_ - pixel_amt) {
      next_image[r] = image_[r];
    } else {
      Node* curr = image_[r];
      while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next_;
        delete temp;
      }
    }
  }
  delete[] image_;
  image_ = next_image;
  height_ = height_ - pixel_amt;
}
void RLEImagePPM::FlipHorizontal() {
  auto reverse = [](Node*& head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
      Node* n = curr->next_;
      curr->next_ = prev;
      prev = curr;
      curr = n;
    }
    head = prev;
  };
  for (unsigned int r = 0; r < height_; r++) {
    reverse(image_[r]);
  }
}
void RLEImagePPM::FlipVertical() {
  for (unsigned int r = 0; r < height_ / 2; r++) {
    Node* temp = image_[r];
    image_[r] = image_[height_ - r - 1];
    image_[height_ - r - 1] = temp;
  }
}
