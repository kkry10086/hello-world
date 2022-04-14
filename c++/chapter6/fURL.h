#ifndef GUARD_fURL_h
#define GUARD_fURL_h

#include<vector>
#include<string>
#include<algorithm>
#include<cctype>

using std::vector;
using std::string;
using std::find;
using std::find_if;
using std::isalnum;
using std::isalpha;




bool not_url_char(char c){
  //any char would be in url except digit and letter
  static const string url_ch="~;/?:@=&$-_.+!*'(),";

  return !(isalnum(c)||
	   find(url_ch.begin(),url_ch.end(),c)!=url_ch.end());
  
}


string::const_iterator url_end(string::const_iterator b,
				 string::const_iterator e){
  return find_if(b,e,not_url_char);
}

string::const_iterator url_beg(string::const_iterator b,
			 string::const_iterator e){

  static const string sep="://";
  typedef string::const_iterator iter;
  iter i=b;

  while((i=search(i,e,sep.begin(),sep.end()))!=e){
    //make sure str not only has "://"
 
    if(i!=b&&i+sep.size()!=e){
      //beg sign the begin of protocol
      iter beg=i;
      while(beg!=b&&isalpha(beg[-1]))beg--;

      //make sure there is a char that can be in url after "://"
      if(beg!=i&&!not_url_char(i[sep.size()]))
	return beg;
    }
    if(i!=e)i+=sep.size();
    
  }
  return e;
  
}


vector<string> URL(string s){
  vector<string> ret;
typedef string::const_iterator iter;  

  iter b=s.begin(),e=s.end();

  while(b!=e){
    //get the begin of a url
    b=url_beg(b,e);
    
    if(b!=e){
      //get the end of a url
      iter after=url_end(b,e);
      std::cout<<"push_back"<<std::endl;
      ret.push_back(string(b,after));
       b=after;
    }
    
   
  }
  return ret;
}

#endif
