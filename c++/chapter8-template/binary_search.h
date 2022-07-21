#ifndef GUARD_BS_H
#define GUARD_BS_H

template <class Ran,class X>
bool binary_search(Ran begin,Ran end,const X& x)
{
	while(begin<end){
		Ran mid=begin+(end-begin)/2;

		if(x<*mid)
			end=mid;
		else if(*mid<x)
			begin=mid;
		else return true;
	}
	return false;
}



#endif
