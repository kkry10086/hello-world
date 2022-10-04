//句柄类

#include"Core.h"
#include"Grad.h"

class Student_info{

    public:
    //构造函数与复制构造函数
    Student_info():cp(0){}
    Student_info(std::istream& is):cp(0){read(is);}
    Student_info(const Student_info&);
    Student_info& operatot=(cosnt Student_info&);
    ~Student_info(){delete cp;}

    //操作
    std::istream& read(std::istream&);

    std::string name() const{
        if(cp)return cp->name();
        else throw std::runtime_error("Uninitialized Student");
    }
    double grade() const{
        if(cp) return cp->grade();
        else throw std::runtime_error("uninitialized Student");
    }
    static bool compare(const Student_info& s1 , const Student_info& s2){
        return s1.name()<s2.name();
    }


    private:
    Core *cp;

};
std::istream& Student_info::read(std::istream& is){
    delete cp;
    char ch;
    is>>ch;

    if('U'==ch){
        cp=new Core(is);
    }
    else{
        cp=new Grad(is);
    }
    return is;
}