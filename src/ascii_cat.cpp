#include <cstdlib>

#include <cstring>
#include <fstream>

#include "cpp_argv.hpp"

#define DEFAULT_NAME "ascii_cat"

/**
 * @brief Unix command cat for ascii files.
 *
 * @param argc number of arguments in the command line.
 * @param argv arguments of the command line.
 * @return @c EXIT_SUCCESS if command succeeds else @c EXIT_FAILURE.
 */
int main(int argc, char *argv[]) {

  // User expects help.

  CPP_ARGV_TEST_HELP_REQUEST(argc, argv[0], DEFAULT_NAME,"ascii_filename");
  
  // Bad argument number.
  CPP_ARGV_TEST_ARG_NUM(argc, 2);

  // Retrieves the filename.
  const char *const filename = argv[1];

  // Tries to open it.
  std::ifstream stream(filename);
  if (not stream) {
    std::cerr << std::strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  // Let's go.
  std::string line;
  while (std::getline(stream, line)) {
    std::cout << line << std::endl;
  }

  // It's over.
  return EXIT_SUCCESS;
}
