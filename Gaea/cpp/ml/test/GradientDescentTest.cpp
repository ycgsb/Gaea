#include "GradientDescentTest.h"
#include "../util/GradientDescent.h"
#include "../../math/Math.h"
#include <cstdio>

namespace ycg {

void GradientDescentTest::run() {
	Vector optPoint = GradientDescent(GradientDescentConfig(0.01, 1000, 1e-15, true)).compute(
		Vector(2),
		[](const Vector& vec) -> double {
			return 3*Math::sqr(vec[0]-2)
				  + 4*Math::sqr(vec[1]-3);
		},
		[](const Vector& vec) -> Vector{
			Vector g(2);
			g[0] = 6*(vec[0]-2);
			g[1] = 8*(vec[1]-3);
			return g;
		});
	CHECK(optPoint[0] == 2 && optPoint[1] == 3);
	printf("GradientDescentTest passed.\n");
}

} //~ namespace ycg
