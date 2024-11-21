#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
#include <iomanip>

using namespace std;
using namespace boost::multiprecision;

// Función que calcula el Coeficiente Binomial usando el enfoque iterativo
cpp_int binomialCoefficient(const cpp_int n, const cpp_int k) {
    cpp_int result = 1;
    if (k > n - k) {
        return 0; // Invalid case
    }
    for (cpp_int i = 1; i <= k; ++i) {
        result *= (n - k + i);
        result /= i;
    }
    return result;
}

// Función que calcula el coeficiente de Narayana
cpp_int narayana(cpp_int n, cpp_int k) {
    cpp_int binom1 = binomialCoefficient(n, k);
    cpp_int binom2 = binomialCoefficient(n, k - 1);
    return (binom1 * binom2) / n;
}

// Función que calcula el tribonacci de forma iterativa
cpp_int tribonacciIterative(cpp_int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    cpp_int a = 0, b = 1, c = 2, next_value;
    for (cpp_int i = 3; i <= n; ++i) {
        next_value = a + b + c;
        a = b;
        b = c;
        c = next_value;
    }

    return c;
}

// Cálculo iterativo del logaritmo en base 2 de un cpp_int
cpp_int log2cpp(const cpp_int& value) {
    cpp_int result = 0;
    cpp_int temp = value;
    
    while (temp > 1) {
        temp >>= 1;  // Shift right by 1 bit (equivalent to dividing by 2)
        result++;
    }
    
    return result;
}

// La función principal que calcula maldad(n)
cpp_int maldad(cpp_int n) {
    cpp_int k = log2cpp(n); // Utilizamos el cálculo iterativo para log2
    cpp_int N_n_k = narayana(n, k);
    cpp_int log_value = log2cpp(N_n_k); // Calcular log2 de N_n_k de forma iterativa

    return tribonacciIterative(log_value + 1);
}

int main(int argc, char* argv[]) {
    cpp_int n;

    if (argc > 1) {
        n = stoll(argv[1]);
    } else {
        cin >> n; // Solicitar al usuario el valor de n
    }

    auto start_time = chrono::high_resolution_clock::now();
    cpp_int result = maldad(n);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> execution_time = end_time - start_time;

    cout << "maldad(" << n << ") = " << result << endl;
    cout << fixed << setprecision(10);
    cout << "Tiempo de ejecución = " << execution_time.count() << " segundos" << endl;

    return 0;
}
