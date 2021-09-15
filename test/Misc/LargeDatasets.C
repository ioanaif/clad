// RUN: %cladclang %s -x c++ -lm -lstdc++ -I%S/../../include -oLargeDatasets.out 2>&1
// RUN: ./LargeDatasets.out
// CHECK-NOT: {{.*error|warning|note:.*}}

#include "clad/Differentiator/Differentiator.h"
#include <cmath>

double f(double* y, double* yh, int dim) {
     double loss = 0.0;
     for (int i = 0; i < dim; i++)
        loss += -1 * (y[i] * std::log(yh[i])) + (1 - y[i]) * std::log(1 - yh[i]);
     return loss;
}

void time_clad(double* y, double* yh, int dim) {
    auto result_y = new double[dim]{};
    auto result_yh = new double[dim]{};
    auto f_grad = clad::gradient(f);
    f_grad.execute(y, yh, dim, result_y, result_yh);
}

int main() {
    int dims[25] = {5, 10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20480, 40960, 81920, 163840, 327680, 655360, 1310720, 2621440, 5242880, 10485760, 20971520, 41943040, 83886080};
    for (int i = 0; i < 25; i++) {
        int dim = dims[i];
        double p[dim], pp[dim];
        for (int i = 0; i < dim; i++) {
            p[i] = i;
            pp[i] = i;
        }
	time_clad(p, pp, dim);
    }
}
