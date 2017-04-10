using namespace std;
template<typename E>
class Dnode
{
    public:
        Dnode<E>* next;
        Dnode<E>* previous;
        E element;

        Dnode(E pElement, Dnode<E>* pNext = NULL, Dnode<E>*pPrevious = NULL){
            element = pElement;
            next = pNext;
            previous = pPrevious;
        }
        Dnode(Dnode<E>* pNext = NULL, Dnode<E>*pPrevious = NULL){
            next = pNext;
            previous = pPrevious;

        }

};
