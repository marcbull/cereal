#include <cassert>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/cereal.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>

class MyType {
public:
  MyType() = default;

  template <class Archive>
  void serialize(Archive &ar, const std::uint32_t version) {
    (void)version;
    ar(val_);
  }

  uint8_t val_ = 1;
};

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " -r|-w <filename>" << std::endl;
    return EXIT_FAILURE;
  }
  std::string filename(argv[2]);
  if (std::string(argv[1]) == "-w") {
    std::ofstream os(filename, std::ios::binary);
    MyType m;

    {
      cereal::PortableBinaryOutputArchive ar(os);
      ar(m);
    }
  } else {
    assert(std::string(argv[1]) == "-r");
    std::ifstream is(filename, std::ios::binary);
    MyType m;

    {
      cereal::PortableBinaryInputArchive ar(is);
      ar(m);
    }
    assert(m.val_ == 1);
    if (m.val_ != 1) {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
