#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cstdio>
#include "../lang/Array1D.h"

namespace ycg {

class Polynomial {
public:
    static void format(const IntArray &coefficients, char *output);
};

void Polynomial::format(const IntArray &coefficients, char *output) {
    bool first_term = true;
    for(int i = coefficients.len; i >= 0; --i) {
        if(coefficients[i] == 0)
            continue;
        if(first_term) {
            if(coefficients[i] > 0 && coefficients[i] != 1) {
                sprintf(output, "%d", coefficients[i]);
                while(*output++);--output;
            }
            if(coefficients[i] < 0) {
                if(coefficients[i] == -1) {
                    sprintf(output, "-");
                    while(*output++);--output;
                }
                else {
                    sprintf(output, "%d", coefficients[i]);
                    while(*output++);--output;
                }
            }
            first_term = false;
        } else {
            if(coefficients[i] > 0) {
                if(coefficients[i] == 1) {
                    sprintf(output, " + ");
                    while(*output++);--output;
                    if(i == 0) {
                        sprintf(output, "1");
                        while(*output++);--output;
                    }
                } else {
                    sprintf(output, " + %d", coefficients[i]);
                    while(*output++);--output;
                }
            } else {
                if(coefficients[i] == -1) {
                    sprintf(output, " - ");
                    while(*output++);--output;
                    if(i == 0) {
                        sprintf(output, "1");
                        while(*output++);--output;
                    }
                } else {
                    sprintf(output, " - %d",-coefficients[i]);
                    while(*output++);--output;
                }
            }
        }
        if(i == 1) {
            sprintf(output, "x");
            while(*output++);--output;
        }
        else if(i != 0) {
            sprintf(output, "x^%d", i);
            while(*output++);--output;
        }
    }
    if(first_term) {
        sprintf(output, "0");
        while(*output++);--output;
    }
}

} //~ namespace ycg

#endif // POLYNOMIAL_H
