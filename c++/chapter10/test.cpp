#include<iostream>
#include"new_string.h"
using std::endl;
using std::cout;

int main()
{
       string_list *lll=new string_list();
       lll->add("fuck");
       lll->add("you");
       lll->add("酸萝卜别吃");
       lll->show();
       delete lll;
       return 0;
}
