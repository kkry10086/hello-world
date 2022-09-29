class Core{
    public:
    Core();
    Core(std::istream& in) {read(in);}
    std::string name() const;
    double grade()const;
    std::istream& read(std::istream&);

    protected:
    std::istream& read_common(std::istream&);
    double midterm,final;
    std::vector<double> homework;
    
    private:
    std::string n;
   

};

string Core::name() const{return n;}

double Core::grade()const {
    return ::grade(midtern,final,homework);
}

istream& Core::read_common(istream& in){
    in>>n>>midterm>>final;
    return in;
}
istream& Core::read(istream& in){
    read_common(in);
    read_hw(in,homework);
    return in;
}
