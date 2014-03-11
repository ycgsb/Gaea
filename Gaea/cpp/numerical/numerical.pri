include(test/test.pri)
HEADERS += \
    cpp/numerical/Vector.h \
    cpp/numerical/MatrixInverseSmall.h \
    cpp/numerical/MatrixInverseLU.h \
    cpp/numerical/MatrixInverse.h \
    cpp/numerical/Matrix.h \
    cpp/numerical/LinearAlgebra.h \
    cpp/numerical/Exception.h \
    cpp/numerical/Common.h

SOURCES += \
    cpp/numerical/Vector.cpp \
    cpp/numerical/MatrixInverseSmall.cpp \
    cpp/numerical/MatrixInverseLU.cpp \
    cpp/numerical/MatrixInverse.cpp \
    cpp/numerical/Matrix.cpp
