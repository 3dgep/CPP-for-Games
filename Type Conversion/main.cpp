#include <iostream>

class Base
{
public:
    virtual ~Base() = default;
};

class Base2
{
public:
    virtual ~Base2() = default;
};

class Derived : public Base
{
public:
    ~Derived() override = default;
};

class Derived2 : public Base
{
public:
    ~Derived2() override = default;
};

int main()
{
    unsigned char c = 'A';
    int i = c; // Widening conversion.

    c = static_cast<unsigned char>( i ); // Narrowing conversion.

    unsigned int ui = 3;
    i = static_cast<int>( ui ); // Narrowing conversion.

    ui = static_cast<unsigned int>( i ); // Result in unintentional behaviour.

    //float f = 3.14f;
    //double d = f;
    //f = static_cast<float>( d ); // Narrowing conversion.

    //f = static_cast<float>(i);
    //d = i;

    //i = static_cast<int>( f );

    //f = static_cast<float>(i);
    //i = static_cast<int>(f);

    const float cf = 3.14f;
    float* pf = const_cast<float*>(&cf);
    *pf = 6.28f;

    //Base* b = new Derived();

    //Derived* d = new Derived();
    //Derived2* d2 = dynamic_cast<Derived2*>(b);

    //b = d;

    //if (d != nullptr)
    //{
    //    std::cout << "b is Derived" << std::endl;
    //}

    //if (d2 == nullptr)
    //{
    //    std::cout << "b is not Devived2" << std::endl;
    //}

    Base* b = new Base();
    Base2* b2 = reinterpret_cast<Base2*>(b);

    return 0;
}