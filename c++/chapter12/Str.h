class Str{

    //友员函数
  friend std::istream& operator >>(std::istream&,Str&);
  

  public:
  Str& operator +=(cosnt Str& s){
    std::copy(s.data.begin(),s.data.end(),std::back_inserter(data));
    return *this;
  }
  
  
  typedef Vec<char>::size_type size_type;
  //默认构造函数，创建一个空的Str
  Str(){}
  //生成一个Str对象，包含c的n个复件
  Str(size_type n,char c):data(n,c){}
  //生成一个Str对象并用一个空字符结尾的字符数组来初始化
  Str(const char* cp){
    std::copy(cp,cp+std::strlen(cp),std::back_inserter(data));
  }

  //生成一个Str对象并使用迭代器b和e之间的内容对它进行初始化
  template<class In> Str(In b,In e){
    std::copy(b,e,std::back_inserter(data));
  }

  char& operator[](size_type i){
    return data[i];}

  const char& operator[](size_type i) const {
    return data[i];}
  

  size_type size(){
    return data.size();}

  
  private:

  Vec<char> data;
     
};

std::ostream& operator <<(std::ostream& os,const Str& s){

  for(Str::size_type i=0;i!=s.size();++i){

    os<<s[i];
  }
  return os;
}

 istream& operator >>(istream& is,Str& s){
   s.data.clear();
   char c;
   while(is.get(c)&&isspace(c)){}
   if(is){
     do s.data.push_back(c); //产生一个编译错误，因为data是私有成员数据
     while(is.get(c)&&!isspace(c));
   }
   return is;
  }



