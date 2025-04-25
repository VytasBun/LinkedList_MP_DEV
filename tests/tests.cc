// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "node.hpp"
#include "pixel.hpp"
#include "rle_image_ppm.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

bool CompareFiles(const std::string& file_1, const std::string& file_2) {
  std::ifstream f1(file_1);
  std::ifstream f2(file_2);

  if (!f1.is_open() || !f2.is_open()) {
    return false;
  }

  std::string f1_line;
  std::string f2_line;

  while (f1.good() && f2.good()) {
    f1 >> f1_line;
    f2 >> f2_line;
    if (f1_line != f2_line) {
      return false;
    }
  }

  return !(f1.good() || f2.good());
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Black and White Image Height and Width", "[Height and Width]") {
  RLEImagePPM rle("images/BlackWhiteAlternating10X5.ppm");
  REQUIRE(rle.GetHeight() == 5);
  REQUIRE(rle.GetWidth() == 10);
}

TEST_CASE("All Images Height and Width", "[Height and Width]") {
  RLEImagePPM rle_1("images/BlackWhiteAlternating10X5.ppm");
  RLEImagePPM rle_2("images/AlternatingColors35x25.ppm");
  RLEImagePPM rle_3("images/Blue_Marble300x300.ppm");
  RLEImagePPM rle_4("images/CS128Logo400x308.ppm");
  REQUIRE(rle_1.GetHeight() == 5);
  REQUIRE(rle_1.GetWidth() == 10);
  REQUIRE(rle_2.GetHeight() == 25);
  REQUIRE(rle_2.GetWidth() == 35);
  REQUIRE(rle_3.GetHeight() == 300);
  REQUIRE(rle_3.GetWidth() == 300);
  REQUIRE(rle_4.GetHeight() == 308);
  REQUIRE(rle_4.GetWidth() == 400);
}

TEST_CASE("Black and White Image Max Color Value", "[Max Color Value]") {
  RLEImagePPM rle("images/BlackWhiteAlternating10X5.ppm");
  REQUIRE(rle.GetMaxColorValue() == 255);
}

TEST_CASE("All Images Max Color Vlaue", "[Max Color Value]") {
  RLEImagePPM rle_1("images/BlackWhiteAlternating10X5.ppm");
  RLEImagePPM rle_2("images/AlternatingColors35x25.ppm");
  RLEImagePPM rle_3("images/Blue_Marble300x300.ppm");
  RLEImagePPM rle_4("images/CS128Logo400x308.ppm");
  REQUIRE(rle_1.GetMaxColorValue() == 255);
  REQUIRE(rle_2.GetMaxColorValue() == 255);
  REQUIRE(rle_3.GetMaxColorValue() == 255);
  // Hex for (0xffff)
  REQUIRE(rle_4.GetMaxColorValue() == 65535);
}

TEST_CASE("Test toPPM", "[PPM]") {
  std::string input = "images/AlternatingColors35x25.ppm";
  std::string output = "images/output/AlternatingColors35x25.ppm";
  std::string truth = "images/AlternatingColors35x25.ppm";
  RLEImagePPM rle(input);
  rle.ToPPM(output);
  REQUIRE(CompareFiles(output, truth));
}

TEST_CASE("Test Flip Vertical", "[Rotations]") {
  std::string input = "images/CS128Logo400x308.ppm";
  std::string output = "images/output/CS128Logo400x308FlipVertical.ppm";
  std::string truth = "images/CS128Logo400x308FlipVertical.ppm";
  RLEImagePPM rle(input);
  rle.FlipVertical();
  rle.ToPPM(output);
  REQUIRE(CompareFiles(output, truth));
}

TEST_CASE("Test Flip Horizontal", "[Rotations]") {
  std::string input = "images/AlternatingColors35x25.ppm";
  std::string output = "images/output/AlternatingColors35x25FlipHorizontal.ppm";
  std::string truth = "images/AlternatingColors35x25FlipHorizontal.ppm";
  RLEImagePPM rle(input);
  rle.FlipHorizontal();
  rle.ToPPM(output);
  REQUIRE(CompareFiles(output, truth));
}