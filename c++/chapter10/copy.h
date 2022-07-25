#ifndef GUARD_COPY_H
#define GUARD_COPY_H

template <class A,class B>
A copy(A begin,A end,B res){
	while(begin!=end){
		*res++=*begin++;
	}
	return begin;

}
#endif
