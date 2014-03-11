#include "IO.h"

namespace ycg {

void redirectStdin(const char *fileName) {
    freopen(fileName, "r", stdin);
}

void redirectStdout(const char *fileName) {
    freopen(fileName, "w", stdout);
}

} //~ namespace ycg
