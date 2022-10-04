#include"./Core.h"
#include<iostream>
#include<vector>
#include<algorithm>

class Grad :public Core{
    public:
    Grad():thesis(0);
    Grad(std::istream& in){read(in);}
    std::istream& read(std::istream&);
    double grade() const;
    
    protected:
    Grad* clone()const {
        return new Grad(*this);
    }

    private:
    double thesis;
};
std::istream& Grad::read(std::istream& in){
    Core::read_common(in);
    in >> thesis;
    ::read_hw(in,homework);
    return in;
}

double Grad::grade()const{
    return std::min(Core::grade(),thesis);
}