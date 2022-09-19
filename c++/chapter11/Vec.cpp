
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
  size_type size() const {return avail-data;}
  const T& operator[](size_type i) const {return data[i]}
  T& operator[](size_type i){return data[i];}

  //11.2.5
  iterator begin(){return data;}
  const_iterator begin() const {return data;}
  iterator end(){return avail;}
  const_iterator end() const {return avail;}

  //11.3.1
  Vec(const Vec& v){create(v.begin(),v.end());};//复制构造函数
  Vec& operator=(const Vec&);
  ~Vec(){uncreate();}

  void push_back(const T& t){
    if(avail==limit)
      grow();

    unchecked_append(t);
  }
  

  
  Vec(){create();}
  explicit Vec(size_type n ,const T& val=T()){create(n,val);}
  //其他保留接口
private:
  iterator* data;//Vec中的首元素
  iterator* avail;//Vec中的末元素后面一个元素
  iterator* limit;//新分配内存中元元素后面一个元素

  //内存分配工具
  allocator<T> alloc; //控制内存分配的对象

  //为底层的数组分配空间并对它进行初始化
  void create();
  void create(size_type,const &T);
  void create(const_iterator,const_iterator);

  //删除数组中的元素并释放其占用的内存
  void uncreate();

  //支持push_back的函数
  void grow();
  void unchecked_append(const T&);

};
