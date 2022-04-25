#ifndef GUARD_copy_h
#define  GUARD_copy_h


template<class in,class out> out copy(in begin,in end,out dest){
  while(begin!=end)
    *dest++=*begin++;
  return dest;
}


#endif
