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
  赋值操作与初始化操作的区别是c++语言学习中的一个难点。因为“=”可以用来初始化又可以用来赋值。在使用“=”为一个变量赋一个初始值的时候，程序自动调用复制构造函数。而在赋值表达式中，程序调用operator=赋值操作函数。
  赋值与初始化有两个主要的区别：赋值（operator=函数）总是删除一个旧的值；而在初始化则没有这步操作。确切的说，初始化包括创造一个新的对象并同时给它一个初始的值。在下面的情况会发生初始化：
    。声明一个变量的时候
    。在一个函数的入口处用到函数参数的时候
    。函数返回中使用函数返回值的时候
    。在构造初始化的时候

  而赋值只有在表达式中使用“=”运算符的时候会被调用。


  11.3.4 析构函数
  我们还必须提供另一种操作来定义在Vec对象被删除时编译器应该做些什么工作。一个在局域范围里被创建的对象在它的生存范围以外就会被自动删除；而一个动态分配内存的对象则只有在我们使用delete来删除它时才会被删除。
  就像复制与赋值函数一样，我们在类中定义当一个对象被删除的时候要进行一些什么操作。在构造函数中定义了如何创建一个对象，类似的，类中有一个特殊的成员函数叫做destructor（析沟函数），由它来定义如何删除该类的一个对象实例。析构函数的函数名是在类的名字前加一个波浪线前缀(~)。析构函数不带任何参数，而且没有返回值。
  析构函数的任务是做好一个对象被删除时的一切大扫除工作。
  template<class T> class Vec{
  public:
    ~Vec(){unceate();}
    //同上
  };


  11.3.5 默认操作
  在编写类的时候如果没有显式地定义构造函数，析构函数等，编译器将自动为类生成相应的默认版本的函数，进行一些默认的操作。


  11.3.6“三位一体”规则（rule of three）
  在写一个管理资源的类时因该特别注意对复制函数的控制。一般来说，默认的操作对于这种类是不够用的。如果不能很好地控制每个复制操作将会让使用者感到迷惑，并最终导致运行时的错误。
  复制构造函数、析构函数、赋值运算符函数相互之间关系十分密切，他们之间构成了“三位一体”规则：如果类需要一个析构函数，那么它同时可能也需要一个复制构造函数与一个赋值运算符函数。





11.4动态的Vec类型对象
  在写内存管理函数之前，我们必须认识到现在Vec类型对象在某个重要的方面还比不上标准的向两类：因为我们没有在Vec类型对象中提供push_back操作，所以它的大小是固定的。
  现在我们要在Vec类中加入一个push_back函数，它为Vec类的对象分配新的内存，它能够比当前对象所占的空间多容纳一个元素（因为这个Vec类是类似数组的类型，而不是链表的类型）。因此我们要分配新的内存空间，复制当前对象所容纳的所有元素，并用push_back的参数来构造一个新的末端元素，然后将原来的内存释放掉。
  但是这样的行为是有问题的。假设这是一个需要不断push_back的程序，那么这样的行为会耗掉大量的计算。因为有一个经典的方法来解决：当我们需要push_back时，我们为程序分配当前使用的空间的两倍的内存空间。
  这种方式表明：我们需要多一个指针，指向最后一个元素的指针。



11.5灵活的内存管理
  在开始学习之前，我们不打算使用c++内建的new运算符与delte运算符来管理内存。因为如果使用了new与delete运算符，我们写出来的Vec类使用起来就要受到诸多限制，就不如标准向量类的使用范围那么广了。而且c++内建的new运算符要做许多工作：既要分配新的内存空间，又要对新内存进行初始化。在为一个类型为T的数组分配空间时，它需要去调用T的默认构造函数。而这有悖于我们想为用户提供尽可能大的弹性的初衷。
  使用new还可能会给程序带来许多的资源开销。如果我们使用new，它就会使用T:T()构造函数为一个类型为T的数组中的每一个元素都进行初始化。如果我们想用自己提供的数据来初始化Vec类型对象的元素的话，实现上要进行两次初始化——一次是new自动进行的，另一次是在把用户提供的数值赋给Vec类型对象的元素时进行的。更为糟糕的是，我们通过push_back分配我们实际需要的内存的两倍的空间来获得内存空间，我们没有理由要为这些额外的元素进行初始化。这些空间只会在把一个新的数据放进一个元素空间时才会被push_back函数使用。除了使用自带的new和delete来管理内存之外，还使用c++专门设计以支持灵活的内存管理的一些类来管理内存。语言核心本身没有提供直接的内存分配管理的语法。
  只提供了统一的内存管理接口，在<memory>头文件中提供了一个名为allocator<T>的类，它可以分配一块预备用来储存T对象但是尚未被初始化的内存块，并返回一个指向这块内存的头元素的指针。这样的指针是非常危险的，因为指针的类型表明它们指向类型对象，但实际上这些内存块却并没有储存实际的对象。对象库提供了一种途径来为这种内存块进行初始化，也提供了删除对象的方法——仅仅是删除对象，而没有释放空间。有程序员们来使用allocator类得到这些被指定用来存放类型对象但实际上没有被初始化的内存空间的地址。
  在allocator类中，我们只对与我们的实现目的相关的部分感兴趣，这一部分包括四个成员函数和两个相关的非成员函数：
  template<class T> class allocator{
  public:
    T* allocate(size_t);
    void deallocate(T*,size_t);
    void construct (T*,T);
    void destroy(T*);
    //...
  };
  void uninitialized_fill(T*,T*,const T&);
  T*uninitialized_copy(T*,T&*,T*);

  allocate成员函数用来分配一块被制定了类型但未被初始化的内存块，它足以储存相应类型对象的元素。被指定了类型的内存，意思是这块内存块将用来储存类型为T的值，我们可以通过使用一个T*类型的指针来得到它的地址。未被初始化的内存，意思是这块内存是原始的，在这块内存中没有储存任何实际的对象。deallocate成员函数则是用来释放未被初始化的内存，它带有两个参数：一个是allocate函数返回的指针；另一个是该指针指向的内存块的大小。construct成员函数是用来在allocate申请分配但尚未被初始化的内存区域上进行初始化，生成单个的对象，destroy成员函数则是用来删除这个对象。construct构造函数带有两个参数：一个是allocate函数返回的指针；另一个是用来复制到指针指向的内存块的对象值。destory函数调用析构函数，删除它的参数所指向对象的元素。
  另外两个相关函数：uninitialized_copy和uninitialized_fill函数。这两个函数对allocate所分配的内存进行初始化。uninitialized_fill函数向内存块中填充一个指定的值。在函数调用结束后，前两个参数指针指向的内存区间中的元素都被初始化成第三个参数所值对象的内容。uninitialized_copy函数的工作机理类似标准库的copy函数，它用来把前两个参数指针所指向的内存区间中的值复制到第三个参数指针所指向的目标内存块中。这两个数据的流向是相反的。当然与uninitialized_fill函数一样，它假定目标内存块尚未被初始化，它将在目标内存块中构造新的对象。
  我们将在Vec类中加入allocator<T>成员函数，用来正确的为T类的对象分配内存。


  11.5.1最后的Vec类
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
  Vec(const Vec& v){create(v.begin(),v.end());};//复制构造函数
  Vec& operator=(const Vec&);

  
  Vec(){create();}
  explicit Vec(size_type n ,const T& val=T()){create(n,val);}
  //其他保留接口
private:
  iterator* data;//Vec中的首元素
  iterator* avail;
  iterator* limit;//Vec中的末元素

};

  
  
  
  
  
  