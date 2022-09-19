class Grad :public Core{
    public:
    Grade();
    Grade(std::istream& in){read(in);}
    double grade() const;
    std::istream& read(std::istream&);

    private:
    double thesis;
};
istream& Grad::read(istream& in){
    read_common(in);
    in>>thesis;
    read_hw(in,homework);
    return in;
}

double Grad::grade()const{
    return min(Core::grade(),thesis);
}