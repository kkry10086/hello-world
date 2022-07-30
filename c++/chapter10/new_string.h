#ifndef NEW_STRING_H
#define NEW_STRING_H

#include<string>
using std::string;
class node{
	private:
		string name;

	public:
		node(){};
		node(string n){name=n;}
		void set(string n){name=n;}
		string get_string(){return name;}
		node *prev;
		node *next;
};


class string_list
{

	public:
		string_list();
		node *head;
		node *tail;
		node *begin();
		node *end();
		void add(string );
//      	void remove(string );
		int size();
		bool isEmpty();
		void show();
};
//构造函数
string_list::string_list(){
	head=new node;
	tail=new node;
	tail->next=nullptr;
	tail->prev=nullptr;
	head=tail;
}
bool string_list::isEmpty(){
	if(head==tail)
		return true;
	return false;
}

int string_list::size()
{
	int x=0;
	node *temp=head;
	while(temp!=tail){
		++x;
		temp=temp->next;
	}
	return x;
}

void string_list::add(string a){
	if(isEmpty()){
		node *temp=new node(a);
		head=temp;
		head->next=tail;
		head->prev=nullptr;
		tail->prev=head;
	}
	else
	{
		node *temp=new node(a);
		tail->prev->next=temp;
		temp->prev=tail->prev;
		temp->next=tail;
		tail->prev=temp;
	}
}

node *string_list::begin()
{
	return head;
}
node *string_list::end()
{
	return tail;
}

void string_list::show()
{
	node *temp=head;
	while(temp!=tail){
		std::cout<<temp->get_string()<<std::endl;
		temp=temp->next;
	}
}

#endif
