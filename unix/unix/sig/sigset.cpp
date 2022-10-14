#include<iostream>
#include<stdlib.h>
#include<signal.h>

using std::cout;
using std::endl;

//显示信号集（阻塞信号集）
void show_set(sigset_t& set){
  int i=0;
    for(i=1;i<32;i++){

      //某个信号是否有在该信号集中
    if(sigismember(&set,i)){
      cout<<1;
    }
    else{
      cout<<0;
    }
    
  }

  cout<<endl;
}

//信号集处理函数
int main(){

  int i =0;
  //信号集合
  sigset_t set;

  //清空集合
  sigemptyset(&set);
  cout<<"清空集合"<<endl;
  show_set(set);

  //将所有的信号都加入set
  sigfillset(&set);
  cout<<"fillset"<<endl;
  show_set(set);

  //删除了9和19
  sigdelset(&set,SIGKILL);
  sigdelset(&set,SIGSTOP);
  cout<<"delete"<<endl;
  show_set(set);

  //增加回来
  sigaddset(&set,SIGKILL);
  sigaddset(&set,SIGSTOP);
  cout<<"add"<<endl;
  show_set(set);
  return 0;
}
