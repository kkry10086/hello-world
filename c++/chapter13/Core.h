#include<iostream>
#include<vector>
class Core{
    public:
    Core():midterm(0),final(0);
    Core(std::istream& in) {read(in);}
    std::string name() const;
    virtual double grade()const;//虚拟函数,可以被派生类继承
    virtual std::istream& read(std::istream&);

    protected:
    std::istream& read_common(std::istream& );
    double midterm,final;
    std::vector<double> homework;
    
    private:
    std::string n;
   

};

std::string Core::name() const{return n;}


double Core::grade()const {
    return ::grade(midterm,final,homework);
}

std::istream& Core::read_common(std::istream& in){
    in >> n >> midterm >> final;
    return in;
}
std::istream& Core::read(std::istream& in){
    read_common(in);
    ::read_hw(in,homework);
    return in;
}
