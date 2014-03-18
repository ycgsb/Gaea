#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>

namespace ycg {

class SingularMatrixException : public std::exception { };

class UnsupportMethodException : public std::exception { };

}  // namespace ycg



#endif // EXCEPTION_H
