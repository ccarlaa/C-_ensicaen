#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "cpp_argv.hpp"

#define DEFAULT_NAME "ascii_diff"

/**
 * @brief Simplified Unix diff command for two ASCII-ANSI text files.
 *
 * @param argc number of arguments in the command line.
 * @param argv arguments of the command line.
 * @return @c EXIT_SUCCESS if command succeeds else @c EXIT_FAILURE.
 */
int main(int argc, char *argv[]) {

  // User expects help.
  CPP_ARGV_TEST_HELP_REQUEST(argc, argv[0], DEFAULT_NAME,
                             "ascii_filename1 ascii_filename2");

  // Bad argument number (expects executable + 2 filenames = 3 arguments).
  CPP_ARGV_TEST_ARG_NUM(argc, 3);

  // Retrieves the two filenames.
  const char *const filename1 = argv[1];
  const char *const filename2 = argv[2];

  // Tries to open both files.
  std::ifstream stream1(filename1);
  if (not stream1) {
    std::cerr << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  std::ifstream stream2(filename2);
  if (not stream2) {
    std::cerr << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  // Compares line by line (1-based line numbers).
  unsigned long line_number = 0;
  std::string line1;
  std::string line2;

  while (true) {
    const bool has_line1 = static_cast<bool>(std::getline(stream1, line1));
    const bool has_line2 = static_cast<bool>(std::getline(stream2, line2));

    if (not has_line1 && not has_line2) {
      break;
    }

    ++line_number;

    if (has_line1 && has_line2) {
      if (line1 != line2) {
        std::cout << line_number << '\n'
                  << "< " << line1 << '\n'
                  << "---\n"
                  << "> " << line2 << '\n';
      }
    } else if (has_line1) {
      std::cout << line_number << '\n'
                << "< " << line1 << '\n';
    } else {
      std::cout << line_number << '\n'
                << "> " << line2 << '\n';
    }
  }

  // It's over.
  return EXIT_SUCCESS;
}