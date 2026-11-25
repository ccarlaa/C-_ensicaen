#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "cpp_argv.hpp"

#define DEFAULT_NAME "ascii_wc"

/**
 * @brief Simplified Unix wc command for ASCII-ANSI text files.
 *
 * @param argc number of arguments in the command line.
 * @param argv arguments of the command line.
 * @return @c EXIT_SUCCESS if command succeeds else @c EXIT_FAILURE.
 */
int main(int argc, char *argv[]) {

  // User expects help.
  CPP_ARGV_TEST_HELP_REQUEST(argc, argv[0], DEFAULT_NAME, "filename");

  // Bad argument number (expects executable + 1 filename = 2 arguments).
  CPP_ARGV_TEST_ARG_NUM(argc,2);

  // Retrieves the filename.
  const char *const filename = argv[1];

  // Tries to open it.
  std::ifstream stream(filename);
  if (not stream) {
    std::cerr << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  // Counters required by exercise 3.1.
  unsigned long lines = 0;
  unsigned long words = 0;
  unsigned long chars = 0;

  // Reads line by line and counts lines, words, and characters.
  std::string line;
  while (std::getline(stream, line)) {
    ++lines;
    chars += line.size() + 1; // +1 for the '\n' delimiter consumed by std::getline

    std::istringstream line_stream(line);
    std::string word;
    while (line_stream >> word) {
      ++words;
    }
  }

  // Prints result in the expected format: lines words chars filename
  std::cout << lines << ' ' << words << ' ' << chars << ' ' << filename
            << std::endl;

  // It's over.
  return EXIT_SUCCESS;
}