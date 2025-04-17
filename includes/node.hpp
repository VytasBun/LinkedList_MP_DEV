#ifndef NODE_HPP
#define NODE_HPP
#include "pixel.hpp"

struct Node {
  Pixel pixel_;
  unsigned int count_ = 0;
  Node* next_ = nullptr;  // NOLINT
  Node(Pixel pixel): pixel_(pixel) {}
  Node(Pixel pixel, unsigned int count): pixel_(pixel), count_(count) {}
  Node(Pixel pixel, unsigned int count, Node* next):
      pixel_(pixel), count_(count), next_(next) {}
  Node(int r, int g, int b): pixel_(Pixel(r, g, b)) {}
  Node(int r, int g, int b, unsigned int count):
      pixel_(Pixel(r, g, b)), count_(count) {}
  Node(int r, int g, int b, unsigned int count, Node* next):
      pixel_(Pixel(r, g, b)), count_(count), next_(next) {}
};

#endif