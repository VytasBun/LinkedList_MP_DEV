#include <iostream>
#include <map>

int main() {
  // constexpr char kConsonants[] = {'p', 'k', 'h', 'l', 'm', 'n', 'w'};
  std::map<int, char> example = {{1, 'a'}, {2, 'b'}};

  for (int x : {2, 5}) {
    if (example.contains(x)) {
      std::cout << x << ": Found\n";
    } else {
      std::cout << x << ": Not found\n";
    }
  }
}
