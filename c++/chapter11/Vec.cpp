template <class T> class Vec
{
public:
  //11.2.3
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef size_t size_type;
  typedef T value_type;
  //......
  //11.2.4
  size_type size() const {return limit-data;}
  const T& operrator[](size_type i) const {return data[i]}

  //11.2.5
  iterator begin(){return data;}
  const_iterator begin() const {return data;}
  iterator end(){return limit;}
  const_iterator end() const {return limit;}

  //11.3.1
  Vec(const Vec& v);//复制构造函数

  
  Vec(){create();}
  explicit Vec(size_type n ,const T& val=T()){create(n,val);}
  //其他保留接口
private:
  T* data;//Vec中的首元素
  T* limit;//Vec中的末元素

};
