
#include <iostream>
#include <map>
#include <rle_image_ppm.hpp>

int main() {
  RLEImagePPM rle("images/CS128Logo400x308.ppm");
  // rle.CropRight(50);
  //  rle.FlipHorizontal();
  rle.FlipVertical();
  // rle.ToPPM("output.ppm");
  rle.ToCSV("out.csv");
  RLEImagePPM rle2("out.csv", 400, 308, 65535);
  rle2.ToPPM("output.ppm");
}
