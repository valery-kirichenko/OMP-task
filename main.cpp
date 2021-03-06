#include <iostream>
#include <random>
#include <chrono>
#include "omp.h"

void randomize_matrix(int** matrix, int size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> gen(1, 100);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = gen(mt);
        }
    }
}

int main() {
    int size = 1500;
    auto a = new int*[size];
    auto b = new int*[size];
    auto result = new int*[size];
    for (int i = 0; i < size; ++i) {
        a[i] = new int[size];
        b[i] = new int[size];
        result[i] = new int[size];
    }

    randomize_matrix(a, size);
    randomize_matrix(b, size);

    int max_threads = omp_get_max_threads();

    for (int threads = 1; threads <= max_threads; ++threads) {
        omp_set_num_threads(threads);

        auto start = std::chrono::high_resolution_clock::now();

        #pragma omp parallel for
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration = stop - start;

        std::cout << threads << " threads " << duration.count() << "ms" << std::endl;
    }

    return 0;
}
