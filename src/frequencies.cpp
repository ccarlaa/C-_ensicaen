#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>

#include "cpp_argv.hpp"

#define DEFAULT_NAME "frequencies"

int main(int argc, char *argv[]) {
  // User expects help.
  CPP_ARGV_TEST_HELP_REQUEST(argc, argv[0], DEFAULT_NAME, "binary_filename");

  // Bad argument number (expects executable + 1 filename = 2 arguments).
  CPP_ARGV_TEST_ARG_NUM(argc, 2);

  // Retrieves the filename.
  const char *const filename = argv[1];

  // 5.1: Opens the file in binary mode.
  std::ifstream stream(filename, std::ios::binary);
  if (not stream) {
    std::cerr << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  // 5.2: Frequency table for 2^8 = 256 possible byte values, initialized to 0.
  unsigned long frequency_table[256] = {0};

  // 5.3 & 5.4: Byte buffer as unsigned char and char* pointer via reinterpret_cast.
  unsigned char c = 0;
  char *const c_address = reinterpret_cast<char *>(&c);

  // 5.5: Reads byte by byte and updates frequency_table.
  while (stream.read(c_address, 1)) {
    ++frequency_table[c];
  }

  // 5.6: Prints (symbol code, occurrence count) for non-zero frequencies.
  for (unsigned int i = 0; i < 256; ++i) {
    if (frequency_table[i] > 0) {
      std::cout << i << ' ' << frequency_table[i] << '\n';
    }
  }

  return EXIT_SUCCESS;
}