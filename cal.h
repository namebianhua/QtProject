#ifndef CAL_H
#define CAL_H


class Cal
{
private:
    Cal(){};
    ~Cal(){};
    Cal(const Cal&);
    Cal& operator=(const Cal&);
    int saveValue = 0;

public:
    static Cal& getinstance(){
        static Cal instance;
        return instance;
    }
    //整数乘法器
    int mult(int par1, int par2);
    int div();

};

class Dev{
public:
    Dev(){};
    ~Dev(){};
    //整数乘法器
    int mult_s(int par1, int par2);
private:
    int saveValue1 = 0;
};

//Cal::saveValue = 0;
#endif // CAL_H
