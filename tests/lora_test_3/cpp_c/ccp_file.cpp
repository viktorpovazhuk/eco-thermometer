class C {
public:
    // ...
    virtual double f(int);
};

extern "C" double call_C_f(C* p, int i) // wrapper function
{
    return p->f(i);
}
