
#include <iostream>
#include <map>
#include <rle_image_ppm.hpp>

int main() {
  RLEImagePPM rle("images/CS128Logo400x308.ppm");
  // rle.CropRight(50);
  //  rle.FlipHorizontal();
  rle.FlipVertical();
  rle.ToPPM("output.ppm");
}
