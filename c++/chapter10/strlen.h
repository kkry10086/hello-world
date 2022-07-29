#ifndef GUARD_STRLEN_H
#define GUARD_STRLEN_H
template<class IN>
int strlen(IN begin){
	int size=0;
	while(*begin++!='\0'){
		size++;
	}
	return size;
}


#endif
