#include <stdexcept>
#include <iostream>
#include "Dnode.h"
using namespace std;
template <typename E>
class LinkedList
{
private:
    Dnode<E>* head;
    Dnode<E>* tail;
    Dnode<E>* current;
    int size;

public:
    void init() {
        head = new Dnode<E>();
        tail = new Dnode<E>();
        head->next = tail;
        tail->previous = head;
        current = head;
        size = 0;}

    LinkedList(){
        init();
    }
    ~LinkedList(){
        clear();
        delete head;
        delete tail;
    }
    void insert(E element){
        current -> next = current -> next ->previous = new Dnode<E>(element, current->next, current);
        size ++;
    }
    void append(E element){
        tail -> previous = tail -> previous-> next = new Dnode<E>(element, tail, tail-> previous);
        size ++;
    }
    E remove() throw (runtime_error){
        if (current->next == tail) {
            throw runtime_error("Error");
        }
        E res = current->next->element;
        Dnode<E>* temp = current->next;
        current->next = current->next->next;
        current->next->previous = current;
        delete temp;
        size--;
        return res;

    }
    void clear(){
        while (head!=NULL){
            current = head;
            head = head->next;
            delete current;

        }
        init();
    }
    E getElement() throw (runtime_error){
        if (current->next == tail) {
            throw runtime_error("No element to get.");
        }
        return current->next->element;

    }
    void goToStart(){
        current = head;
    }
    void goToEnd()
    {
        current = tail->previous;
    }
    void goToPos(int pPos) throw (runtime_error)
    {
        if((pPos < 0) || (pPos >= size)){
            throw runtime_error("Index out of bounds.");
        }
        current = head;
        for (int i = 0; i < pPos; i++)
        {
            current = current -> next;
        }
    }
    void next()
    {
        if (current != tail-> previous)
        {
            current = current ->next;
        }
    }
    void previous()
    {
        if (current != head)
        {
            current = current -> previous;
        }
    }
    int getPos()
    {
        int pos = 0;
        Dnode<E>* temp = head;
        while(temp != current)
        {
            temp = temp -> next;
            pos++;
        }
        return pos;
    }
    int getSize()
    {
        return size;
    }

};
