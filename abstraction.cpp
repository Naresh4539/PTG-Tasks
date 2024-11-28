#include<iostream>
using namespace std;
class Animal {
public:
    virtual void makeSound() = 0;
};

class Cat : public Animal {
public:
    void makeSound(){
        cout << "Meow" << endl;
    }
};