#include<vector>
#include<iostream>
using std::cout;
using std::vector;

int main(){
  //构造一个vector
  vector<Student_info> vs ;//一个空的vector
  vector<double> v(100);//有100个元素的vector

  //获得vector使用的类型的名字
  vector<Student_info>::const_iterator b,e;
  vector<Student_info>::size_type i=0;

  //用size函数与索引值查看vector中的元素
  for(i=0;i!=vs.size();++i)
    {
      cout<<vs[i].name();
    }

  //返回指向第一个元素的迭代器与指向最后一个元素后面那个元素的迭代器
  b=vs.begin();e=vs.end();
  
}
//上面的只是vector的一小部分功能/接口。但可以简单实现一次。


