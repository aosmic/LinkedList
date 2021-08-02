#include <iostream>
#include <string>

class Element {
    Element* previous = nullptr, * next = nullptr;

public:
    Element* getPrevious() {
        return previous;
    }
    Element* getNext() {
        return next;
    }
    void setNext(Element* _next) {
        next = _next;
    }
    void setPrevious(Element* _previous) {
        previous = _previous;
    }
    virtual void print() = 0;
};

class List {
    Element* head, * tail;

public:
    List():head(nullptr), tail(nullptr){}


    void insertElement(Element* elem, Element* behind = nullptr) {

        if (behind == nullptr) {
            if (head == nullptr) {
                head = elem;
                tail = elem;
            }
            else {
                elem->setNext(tail);
                tail->setPrevious(elem);
                tail = elem;
                elem->setPrevious(nullptr);
            }
        }
        else {
            if (behind == tail) {
                elem->setNext(tail);
                tail->setPrevious(elem);
                tail = elem;
                elem->setPrevious(nullptr);
            }
            else {
                elem->setNext(behind);
                elem->setPrevious(behind->getPrevious());
                behind->getPrevious()->setNext(elem);
                behind->setPrevious(elem);
            }
        }
    }

    /*void removeElement(Element* elem)
    {
        if (elem->getNext() != nullptr)
            elem->getNext()->setPrevious(elem->getPrevious());
        else
            tail = elem->getPrevious();
        if (elem->getPrevious() != nullptr)
            elem->getPrevious()->setNext(elem->getNext());
        else
            head = elem->getNext();
    }*/
    Element* getHead() {
        return head;
    }
    Element* getTail() {
        return tail;
    }
};

class StringElement :public Element {
    std::string message;
public:
    StringElement() :message("") {};
    StringElement(std::string _message) :message(_message) {};

    void print() {
        std::cout << "------------------------\n";
        std::cout << message << "\n";
        std::cout << "------------------------\n";
    }
};

class VectorElement : public Element {
    float x, y;

public:
    VectorElement() :x(0), y(0) {};
    VectorElement(float _x, float _y) :x(_x), y(_y) {};

    void setVectorElement(float _x, float _y) {
        x = _x;
        y = _y;
    }

    float getX() {
        return x;
    }
    float getY() {
        return y;
    }

    void print() {
        std::cout << "------------------------\n";
        std::cout << "x = " <<getX() << "\n";
        std::cout << "y = " << getY() << "\n";
        std::cout << "------------------------\n";
    }
};

int main()
{
    Element* str1 = new StringElement("Prvi string element");
    Element* str2 = new StringElement("Drugi string element");
    Element* str3 = new StringElement("Treci string element");

    Element* vec1 = new VectorElement(3, 5.5);
    Element* vec2 = new VectorElement(1, 1.2);



    List l;

    l.insertElement(str1);
    l.insertElement(str2);
    l.insertElement(vec1);
    l.insertElement(vec2, str1);
    l.insertElement(str3, l.getTail());


    Element* elem = static_cast<Element*>(l.getHead());
    while (elem)
    {
        elem->print();
        elem = static_cast<Element*>(elem->getPrevious());
    }

    std::cout <<"Head: " << str1 << " == " << l.getHead() << "\n";
    std::cout <<"Tail: " << str3 << " == " << l.getTail() << "\n";
    

    delete str1, str2, vec1, vec2, str3;
    
    return 0;
}