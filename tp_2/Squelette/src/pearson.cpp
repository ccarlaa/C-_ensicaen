#include "cpp_argv.hpp"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <list>
#include <cstdlib>
#include <fstream>

#define DEFAULT_NAME "pearson"

using namespace std;

/**
 * @brief Correlation.
 *
 * @param argc number of arguments in the command line.
 * @param argv arguments of the command line.
 * @return @c EXIT_SUCCESS if command succeeds else @c EXIT_FAILURE.
 */

typedef struct {
    double x;
    double y;
} observation_t;

typedef list<observation_t> Observations;


void read_observations(istream &stream, Observations &set);

void calculate_correlation(Observations& set, double& a, double& b, double& r);

int main(int argc, char *argv[]) {

    // Verifica a quantidade de argumentos
    CPP_ARGV_TEST_HELP_REQUEST(argc, argv[0], DEFAULT_NAME, "file");
    CPP_ARGV_TEST_ARG_NUM(argc, 2);

    // Le o arquivo
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << argv[1] << "\n";
        return EXIT_FAILURE;
    }

    // Inicializa as variaveis
    double a = 0;
    double b = 0;
    double r = 0;

    Observations set;

    // Salva os dados em um lista
    read_observations(file, set);

    // Calcula a, b e r
    calculate_correlation(set, a, b, r);

    // Printa o resultado 
    cout << "----- Resultados -----\n";
    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "r = " << r << "\n";

    return EXIT_SUCCESS;
}

void read_observations(istream &stream, Observations &set) {
    observation_t obs;

    while(stream >> obs.x >> obs.y) {
        set.push_back(obs);
    }

    return;
}

void calculate_correlation(Observations& set, double& a, double& b, double& r)
{
    double moy_x_sum = 0;
    double moy_y_sum = 0;
    int size = 0;

    for (const observation_t& obs : set) {
        moy_x_sum += obs.x;
        moy_y_sum += obs.y;
        size++;
    }

    double moy_x = moy_x_sum / size;
    double moy_y = moy_y_sum / size;

    double tot_xy = 0;
    double tot_xx = 0;
    double tot_yy = 0;

    for (const observation_t& obs : set) {
        tot_xy += (obs.x - moy_x) * (obs.y - moy_y);
        tot_xx += sqrt(obs.x - moy_x);
        tot_yy += sqrt(obs.y - moy_y);
    }


}
