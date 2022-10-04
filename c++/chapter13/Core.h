#include<iostream>
#include<vector>
class Core{

    friend class Student_info;

    public:
    Core():midterm(0),final(0);
    Core(std::istream& in) {read(in);}
    std::string name() const;
    virtual double grade()const;//虚拟函数,可以被派生类继承
    virtual std::istream& read(std::istream&);

    //虚拟析构函数
    virtual ~Core();

    protected:
    std::istream& read_common(std::istream& );
    double midterm,final;
    std::vector<double> homework;
    //这里是用于Student_info复制构造函数用的，因为Student_info的复制构造函数
    //的参数仅仅是一个指针，谁知道是谁的。
    //但是有虚拟函数，所以我们可以通过生成一个虚拟函数，然后由这个函数返回本身的类型
    //这样就行了。
    //这里的Core(*this)就是一个复制构造函数，是由编译器自动生成给我们的
    virtual Core* clone() const {
        return new Core(*this);
    }

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
