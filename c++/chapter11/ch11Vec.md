                                         定义抽象数据类型

加深对于类的了解。

11.1 Vec类
  开始设计类的时候，一般来说，要先确定在类中要提供什么样的接口。正确的确定接口的一种途径就是研究一下类的使用者门将会用我们写的类来编写什么样的程序。
  我们要让Vec类实现与标准库中的向量类相同的功能，就要先研究向量类。
  example_vector.cpp


11.2 实现Vec类
一旦确定了要在Vec类中实现的操作后，我们就要考虑如何写出来。
先写一个模板类，我们希望Vec类来存储集中不同类型的数据成员。

template <class T> class Vec{
public:
    //接口
private:
    //实现
}；

上面的代码声明Vec是一个具有一个类型参数T的模板类。接下来的问题是，数据类型，数量，动态生成new,还是静态的static等等。
这里建议使用new的形式。

Vec.cpp

  11.2.1内存分配
  我们要为数组动态分配内存，所以我们希望使用new T[n]为Vec分配空间。但是new T[n]不仅分配内存空间，还会运行T的构造函数来为元素进行默认初始化。那么这样的一个分配空间，要满足一个需求，只有在T具有默认的构造函数时，才能创建一个Vec<T>.标准的向量类没有这样的限制。所以我们在模仿向量类的Vec也不希望有限制。
  所以现在我们要解决上面的问题。库函数中提供了一个内存分配类，在内存分配的方面提供了更为详尽的操作。所以可以使用这个来代替new和delete。当然现在不会这么做11.5。

  11.2.2构造函数
  我们知道，一个类需要构造函数来分配空间等。
  在Vec类中我们可以定义两个构造函数：
  Vec<T> vs; //默认的构造函数
  Vec<T> vs(100);
  标准的向量类还提供了一个相关的第三种构造函数，除了一个大小参数，还带有一个初始值的参数，用来把向量中的元素全部初始化为改制的一个复件。这个构造函数与只带一个大小参数的构造函数十分类似。
  所有构造函数具有一个共同的目标，就是确保对象被正确的初始化。对于Vec中的对象，我们要对data与limit进行初始化。这包括给Vec中的对象分配内存空间并给它们一个初始值。在默认构造函数中，我们想创建一个空的Vec，所以不需要分配人年和空间。对于带一个大小参数的构造函数，就要为该参数给定数目的对象分配内存空间。如果用户在给出大小参数的同时还提供了初始值，就可以使用这个初始值对分配了空间的元素设置初始值。
  此时可以修改了：
  template<class T> class Vec{
  public:
    Vec(){create();}
    explicit Vec(size_type n,const T& val=T()){create(n,val);}

  private:
    T* data;
    T* limit;
  };

  默认构造函数不带任何参数，它首先清空Vec类的对象，这是通过调用create成员函数来实现的，create函数也是我们必须要编码实现的函数之一。调用create函数返回后，data与limit会被置零。
  第二个构造函数中我们用到一个新的关键词explicit，首先这个构造函数使用了一个默认的变量作为第二个参数。因此这个构造函数事实上定义了两个构造函数，一个使用size_t类型的变量作参数，另一个则用的是两个参数——一个size_t类型与一个const T&类型的变量。在这两种情况里我们都调用带一个大小和一个值共两个参数的create函数。


  11.2.3类型定义
  按造标准类模板的管理，我们要提供用户能使用的类型名称，这可以隐藏实现该类的具体细节。特别是：我们必须为常量(const)与非常量(nonconst)迭代器类型以及我们用来表示Vec的大小的类型提供类型定义(typedef)。
  在标准的库容器里还定义了另一个名为value_type的类型，这是容器中存储的对象的类ixing的另一个同义词。现在要往Vec类中加入push_back函数，利用该函数，用户可以动态地增加他们的Vec对象。如果我们也定义了value_type，那么用户就可以用back_inserter来生成一个使Vec大小增加的输出迭代器。
  template <class T> class Vec
{
public:
  //11.2.3
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef size_t size_type;
  typedef T value_type;
  //......
  Vec(){create();}
  explicit Vec(size_type n ,const T& val=T()){create(n,val);}
  //其他保留接口
private:
  T* data;//Vec中的首元素
  T* limit;//Vec中的末元素

};


  11.2.4索引与大小：
  由于Vec类是模仿vector类型的，所以我们也要有Vec.size()还有类似数组的索引能力。这里来实现：
  size()返回一个Vec::size_type类型的数。在定义索引运算符之前，先学习重载运算符。！！！这里是运算符，不是函数！！！。
  定义重载运算符函数与定义任何一个其他的函数基本上是一样的：必须要有一个函数名，带几个参数，并指定其返回类型。
  重载一个运算符时，要把运算符放在关键字operator后面。也就是说，这里要写成operator[]。因为索引就是a[]。当a++即使operator++。
  运算符的种类一定程度上决定了函数要带多少个参数。如果运算符是一个函数而不是一个成员，那么函数的参数个数与运算符的操作数一样多。第一个参数是左操作数，第二个参数一定是右操作数。如果运算符被定义成一个成员函数，那么它的左操作数必须是调用该运算符的对象。可见，成员运算符比简单的运算符函数要少带一个参数。
  一般来说，运算符既可以是成员函数，也可以不是。但是索引运算符必须是成员函数。当用户写出vs[i]的表达式时，将调用vs对象的[]运算符函数，并传递i作为参数。
  而操作数是一个整形值，它必须足够大以用来表示任何大小的Vec类型对象的最后一个元素，这个类型就是Vec::size_type。剩下的就是决定索引运算符要返回的类型。

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
  //.......
  Vec(){create();}
  explicit Vec(size_type n ,const T& val=T()){create(n,val);}
  //其他保留接口
private:
  T* data;//Vec中的首元素
  T* limit;//Vec中的末元素

};
  ptrdiff_t：两个指针相减生成的一个ptrdiff_t类型的值，表示两个指针的距离（以元素为单位）。
  Vec类的size函数不能改变Vec类型对象本身，所以要声明为const成员函数。
  索引运算符在数组中定位到正确的元素位置并返回该元素的一个引用。


  11.2.5返回迭代器的操作
  要实现begin与end操作，分别返回一个定位在Vec首元素及莫元素后一个元素的迭代器。
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
  
  Vec(){create();}
  explicit Vec(size_type n ,const T& val=T()){create(n,val);}
  //其他保留接口
private:
  T* data;//Vec中的首元素
  T* limit;//Vec中的末元素

};

11.3 复制控制
  类的作者可以控制在对象被创建、复制以及被销毁时程序的行为。我们介绍了如何创建对象，但还没谈到当对象被复制、复制以及销毁时，会发生什么。

  11.3.1复制构造函数
  隐式的复制操作：把一个对象的值作为参数传递给函数（参数），或者从函数中通过传值返回一个对象（返回值），这就是在对对象进行隐式的复制操作。
  vector<int> vi;
  double d;
  d=median(vi);//把vi作为参数传递给median函数

  string line;
  vector<string> words= split(line);//把split函数的返回值赋给words

  显式的复制操作：通过使用一个对象来初始化另一个对象，从而显式的复制对象。
  vector<Student_info> vs;
  vecotr<Student_info> v2=vs;

  无论是显式的还是隐式的，都是由copy constructor（复制构造函数）的特殊的构造函数进行的。像其他的构造函数一样，复制构造函数也是与类名同名的一个成员函数。因为它是用来复制一个一存在的同类型对象，以此来初始化一个新的对象，所以复制构造函数只带一个参数，该参数与类本身具有相同的类型。因为我们定义了复制所带来的效果，包括产生函数参数的复件，所以当参数是引用类型时就有了问题。此外，由于复制对象不会改变原对象的值，所以复制构造函数的参数使用了一个常量引用类型。
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
  Vec(const Vec& v){create()v.begin(),v.end();};//复制构造函数
  Vec(){create();}
  explicit Vec(size_type n ,const T& val=T()){create(n,val);}
  //其他保留接口
private:
  T* data;//Vec中的首元素
  T* limit;//Vec中的末元素

};


  11.3.2赋值运算符
  在一个类的定义中必须详细描述在类被复制时要进行什么操作，类似的，在类的定义中还必须描述赋值(assignment)的具体操作。一个类中可以定义几种不同的赋值运算符，其中以一个指向类自身的常量引用作为参数的版本比较特殊：
  它定义了在把一个自定义类型值赋给另一个自定义类型的操作。像指引运算符一样，赋值运算符也必须是类的一个成员函数，赋值运算符也必须返回一个值。
  为了与c++自带的赋值运算符一致，我们让它返回左操作数的引用。
  
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
  Vec(const Vec& v){create()v.begin(),v.end();};//复制构造函数
  Vec(){create();}
  explicit Vec(size_type n ,const T& val=T()){create(n,val);}

  //11.3.2
  Vec& operator=(const Vec&);
  
  //其他保留接口
private:
  T* data;//Vec中的首元素
  T* limit;//Vec中的末元素

};
  我们在对指针数据成员赋值时也要把运算符右操作数对象的每一个元素都复制过去。指针数据成员在进行复制操作时也遵从同样的规律。
  这里是赋值操作：
  template <class T>
  Vec<T>& Vec<T>::operator=(const Vec& rhs)
  {
  //判断是否自我赋值
  if(&rhs !=this)
    {
    uncreate();
    create(rhs.begin(),rhs.end());
    }
    return *this;
  }
  这里有一个新概念：在除了类的头文件以外的地方定义一个模板成员函数的语法。对于一个模板，我们都在一开始就告诉编译器我们要启动一个模板，并且马上给出模板的参数。在这里用的是Vec<T>&的类型。
  在头文件中定义时用的是Vec&类型，不需要显式地声明类型名称。因为在模板文件的范围内，c++允许我们忽略其具体类型名称。在头文件里，因为模板参数是隐式的，所以不需要重复写<T>。而在头文件外面，我们必须声明返回类型，所以要在必要的地方显式地写出模板参数。不过一旦前面指定我们的定义是一个Vec<T>类型的成员函数，后面就不需要重复使用这个定语了。

  在本函数中还用到了另一个新的关键词：this。this只在成员函数内部才有效，代表指向函数操作的对象的指针。例如，在Vec::operator=函数中，this的类型为Vec*，这是因为operator=函数是类Vec的一个成员函数，所以this是指向一个Vec类型对象的指针。

  而这里的if判断是非常重要的，当这两个指针指向同一个对象时，uncreate会将左操作数对象删掉，那么此时，右操作数也会被删掉，那么是谁赋值给谁？我们访问了一个没有分配的内存地址。
  这里还有一个return语句，他对this间接引用，以此得到它指向的对象。然后返回一个该对象的引用。如果返回的是一个局域量对象，
  ！！！！！这里看不懂，以后再说。这是书籍本身写的就不太容易懂。

  11.3.3赋值不是初始化