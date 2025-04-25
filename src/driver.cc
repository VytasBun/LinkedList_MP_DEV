
#include <iostream>
#include <map>
#include <rle_image_ppm.hpp>

int char_count(const std::string& file_name) {
  std::ifstream ifs{file_name};
  int ans = 0;
  char c;
  while (ifs.get(c)) {
    ans++;
  }
  return ans;
}
int main() {
  RLEImagePPM rle("images/CS128Logo400x308.ppm");
  // rle.CropRight(50);
  //  rle.FlipHorizontal();
  rle.FlipVertical();
  // rle.ToPPM("output.ppm");
  rle.ToCSV("out.csv");
  rle.ToPPM("output_right.ppm");
  RLEImagePPM rle2("out.csv", 400, 308, 65535);
  rle2.ToPPM("output.ppm");

  std::cout << "Char Count for PPM: " << char_count("output.ppm") << std::endl;
  std::cout << "Char Count for CSV: " << char_count("out.csv") << std::endl;
}
