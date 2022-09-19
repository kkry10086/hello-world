#include<memory>
using std::allocator;

template<class T>
class Vec{
	public:
		//重命名部分变量
		typedef size_t size_type;
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T value_type;

		//构造函数
		Vec(){create();}
		explicit Vec(size_type n,const T& a){create(n,a);}
		//复制构造函数
		Vec(const T& v){create(v.begin(),v.end());}
		//析构函数
		~Vec(){uncreate();}

		//大小
		size_type size(){return avail-data;}

		//运算符函数
		T& operator[](size_type i){return data[i];}
		const T& operator[](size_type i) const {return data[i];}
		//赋值运算符函数
		Vec& operator=(const Vec&);

		//获取首元素，与末元素后面一个元素
		const_iterator begin() const {return data;}
		iterator begin(){return data;}
		const_iterator end() const {return avail;}
		iterator end(){return avail;}

		//push_back函数
		void push_back(const T& t){
			if(avail==limit){
				grow();
			}
			unchecked_append(t);
		}

	private:
		//create函数
		void create();
		void create(size_type n,const T& t);
		void create(const_iterator,const_iterator);

		//uncreate函数
		void uncreate();
		
		//grow函数
		void grow();
		//unchecked_append函数
		void unchecked_append(const T&);

		//内存分配工具
		allocator<T> alloc;

		T* data;
		T* avail;
		T* limit;

};


template<class T>
void Vec<T>::create(){data=avail=limit=0;}

template<class T>
void Vec<T>::create(size_type n,const T& t){
	data=alloc.allocate(n);
	limit=avail=data+n;
	uninitialized_fill(data,limit,t);
}

template<class T>
void Vec<T>::create(const_iterator i,const_iterator j){
	data=alloc.allocate(j-i);
	uninitialized_copy(i,j,data);
}

template<class T>
void Vec<T>::uncreate(){
	if(data){
		iterator it=avail;
		while(it!=data)
			alloc.destroy(--it);
		
		alloc.deallocate(data,limit-data);
	}
	data=limit=avail=0;
}
template<class T>
void Vec<T>::grow(){
	size_type new_size=std::max(2*(limit-data),ptrdiff_t(1));
	iterator new_data=alloc.allocate(new_size);

	iterator new_avail=std::uninitialized_copy(data,avail,new_data);
	uncreate();
	data=new_data;
	avail=new_avail;
	limit=data+new_size;
}

template<class T>
void Vec<T>::unchecked_append(const T& val){
	alloc.construct(avail++,val);
}

template<class T>
Vec<T>& Vec<T>::operator=(cosnt Vec& rhs){
  if(&rhs !=this){
    uncreate();
    create(rhs.begin(),rhs.end());
  }
  return *this
}
