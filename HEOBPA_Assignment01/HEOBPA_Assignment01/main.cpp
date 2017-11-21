#include <iostream>
#include <memory>
#include "Parent.h"

using namespace std;

int main() {

    cout << "#---Creation Parents---#" << endl;
    std::shared_ptr<Parent>p1 = std::shared_ptr<Parent> (new Parent("Parent1"));
    cout << "P1:" << *p1 << endl;
    cout << " # Reference count P1 na init: " << p1.use_count() << endl;

    std::shared_ptr<Parent> p2 = std::shared_ptr<Parent> (new Parent(*p1)); // roept de copy constructor aan
    cout << "P2:" << *p2 << endl;
    cout << " # Reference count P1 na copy constructor: " << p1.use_count() << endl;
    cout << " # Reference count P2 na copy constructor: " << p2.use_count() << endl;

    std::shared_ptr<Parent>p3 = std::shared_ptr<Parent> (new Parent("Parent3"));
    cout << "P3:" << *p3 << endl;

    *p3 = *p1; // roept de assignment operator aan
    cout << "P3:" << *p3 << endl;
    cout << " # Reference count P1 na dereferenced assignment operator: " << p1.use_count() << endl;
    
    std::shared_ptr<Parent> p4 = p1;
    cout << "P4:" << *p4 << endl;
    std::shared_ptr<Parent> p5 = p1;
    cout << "P5:" << *p5 << endl;
    cout << " # Reference count P1 na assignment operator op ptr: " << p1.use_count() << endl;

    cout << "P2:" << *p2 <<endl;
    std::shared_ptr<Parent> p6 = p2;
    cout << "P6:" << *p6 << endl;
    std::shared_ptr<Parent> p7 = p2;
    cout << "P7:" << *p7 << endl;
    cout << " # Reference count P2 na assignment operator op ptr: " << p2.use_count() << endl;
    p6.reset();
    p7.reset();
    cout << " # Reference count P2 na reset p6 en p7: " << p2.use_count() << endl;
    
    cout << "\n#---Deletion Parents---#" << endl;
    p1.reset();
    p2.reset();
    p3.reset();

    cout << "\n#---End Of Scope---#" << endl;
    return 0;
}
