#include "cpp_argv.hpp"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>

#define DEFAULT_NAME "fraction"

using namespace std;

/**
 * @brief Fraction reducing.
 *
 * @param argc number of arguments in the command line.
 * @param argv arguments of the command line.
 * @return @c EXIT_SUCCESS if command succeeds else @c EXIT_FAILURE.
 */


void euclide_gcd(long int& a, long int& b);

int main(int argc, char *argv[]) {

  // Verifica a quantidade de argumentos
  CPP_ARGV_TEST_HELP_REQUEST(argc, argv[0], DEFAULT_NAME, "fraction.cpp");
  CPP_ARGV_TEST_ARG_NUM(argc, 3);

  char* end; 

  // Converter as entradas
  long a = strtol(argv[1], &end, 10);
  long b = strtol(argv[2], &end, 10);


  // Verifica se o denominador e nulo
  if (b == 0) {
    cerr << "O denominador nao pode ser nulo \n";
    return 0;
  }

  euclide_gcd(a, b);

  return 0;
}

void euclide_gcd(long int& a, long int& b)
{
  long int a_abs = abs(a);
  long int b_abs = abs(b);

  long int r = -1;
  long q = 0;

  while(1) {
    q = a_abs / b_abs;
    r = a_abs - b_abs * q;

    if(r == 0) break;

    a_abs = b_abs;
    b_abs = r;
  }

  // Fracao reduzida
  int a_min = a / b_abs;
  int b_min = b / b_abs;

  // Resposta
  cout << "--------- Resultado ---------\n";
  cout << a_min << "\n";
  cout << "---\n";
  cout << b_min << "\n";
  return;
}
