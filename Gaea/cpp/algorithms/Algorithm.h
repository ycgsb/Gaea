#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace ycg {

namespace Algo {

template<class _InIt, 	class _Fn1> inline
void _For_each(_InIt _First, _InIt _Last, _Fn1& _Func) {
	for (; _First != _Last; ++_First)
		_Func(*_First);
}

}

} //~ namespace ycg

#endif /* ALGORITHM_H */
