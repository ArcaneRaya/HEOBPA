#include <iostream>
#include "Parent.h"

Parent::Parent(string name) {
    this->name = name;
    string childName = "ChildOf" + name;
    this->child = std::unique_ptr<Child> (new Child(childName));
}

Parent::Parent(Parent& other) {
    cout << "Parent cctor" << endl;
    this->name = other.name;
    this->child = std::move (other.child);
}

Parent::~Parent() {
    this->child.reset();
}

Parent& Parent::operator=(Parent& other) {
    cout << "Parent assignment" << endl;

    if (this == &other) {
        return *this;
    }

    this->name = other.name;
    this->child.reset();
    string childName = "ChildOf" + this->name;
    this->child = std::unique_ptr<Child> (new Child(childName));

    return *this;
}

ostream& operator<<(ostream& os, const Parent& parent) {
    if (parent.child){
        os << "name: " << parent.name << " child: " << *parent.child;
    } else {
        os << "name: " << parent.name << " child: " << "none";
    }
    return os;
}
