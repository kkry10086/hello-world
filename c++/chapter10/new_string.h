#include<string>

class name{
	private:
		std::string name;
	        class *next;
	public:
		std::string get(){
			return name;
		}
		void set(std::string n){
			name=n;
		}
		void set_next(class *p){
			next=p;
		}

}
