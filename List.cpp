// List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
template<typename T>
struct Node {
    T val;
    Node* next;
};
template<typename T,typename Alloc=std::allocator<Node<T>>>

class flist {
private:
    Node<T>* first;
    Node<T>* last;
    size_t sz;
    Alloc alloc;
    class iterator {
        Node<T>* ptr;
       
    public:
        iterator& operator++() {
            ptr=ptr->next;
            return *this;
        }
        iterator& operator+=(size_t n) {
            for (int i = 0; i < n; ++i) {
                ptr = ptr->next;
            }
            return *this;
        }
        iterator(Node<T>* ptr) :ptr(ptr){}
        iterator(const iterator& a) :ptr(a.ptr){}
        ~iterator() {

        }
        T& operator*() {
            return ptr->val;
        }
        T operator*() const{
            return ptr->val;
        }
        iterator& operator++(int) {
            iterator copy = *this;
            *this++;
            return copy;
        }

        iterator& operator=(const iterator& a) {
            ptr = a.ptr;
            return *this;
        }
    };
    
public:
    //begin construct and destruct
    flist(const Alloc& alloc = Alloc()) :first(nullptr), last(nullptr), sz(0),alloc(alloc) {}
    flist(const flist& a) :flist() {
        Node<T>* p=a.first;
        while (p != nullptr) {
            this->push_back(p->val);
            p = p->next;
        }
    }
    flist(std::initializer_list<T> array) :flist() {
        auto it = array.begin();
        for (int i = 0; i < array.size(); ++i) {
            this->push_back(*it);
            ++it;
        }
    }
    ~flist() {
        clear();
    }
    void swap(flist& a) {
        this->first = a.first;
        a.first = nullptr;
        this->last = a.last;
        a.last = nullptr;
        this->sz = a.sz;
    }
    //end construxt and destruct


    //begin method
    iterator begin() {
        iterator it(first);
        
        return it;
    }
    iterator end() {
        iterator it(last);
    
        return it;
    }
    void clear() {
        Node<T>* p;
        while (first != nullptr) {
            p = first;
            first = first->next;
            alloc.destroy(p);
            alloc.deallocate(p, 1);

        }
        sz = 0;
        first = nullptr;
        last = nullptr;
    }
    void erase(size_t n) { // REALIZE WITH ITERATOR!!!!!
        Node<T>* p = first;
        if (n == 0) {
            first = p->next;
            alloc.destroy(p);
            alloc.deallocate(p,1);
            --sz;
            return;
        }
        for (int i = 0; i < n - 1; ++i) {

            p = p->next;

        }
        if (p->next == last) {
            alloc.destroy(p->next);
            alloc.deallocate(p->next, 1);
            last = p;
            last->next = nullptr;
            --sz;
            return;
        }
        Node<T>* cop = p->next->next;
        alloc.destroy(p->next);
        alloc.deallocate(p->next,1);
        p->next = cop;
        --sz;

    }
    bool empty() {
        return sz == 0;
    }
    void push_front(T val) {
        this->insert(0, val);
    }
    void pop_back() {
        this->erase(sz - 1);
    }
    void pop_front() {
        this->erase(0);
    }
   
    void insert(iterator& n,T val) { //   REALIZE WITH ITERATOR
        Node<T>* p = first;
        
        if (n == 0) {
            Node<T>* nw =alloc.allocate(1);
            nw->val=val;
            nw->next = first;
            first = nw;
            ++sz;
            return;
        }
        for (int i = 0; i < n-1; ++i) {
            
            p = p->next;
           
        }
        Node<T>* nw= alloc.allocate(1);
        nw->val = val;
        nw->next = p->next;
        p->next = nw;
        ++sz;
       
    }
    void push_back(T val) {
        Node<T>* p = alloc.allocate(1);
        alloc.construct(&(p->val), val);
        if (first == nullptr) {
            first = p;
            last = p;
            ++sz;
            return;
        }
        last->next = p;
        last = p;
        last->next = nullptr;
        ++sz;

    }
    size_t size() {
        return sz;
    }
    void print() const {
        Node<T>* p = first;
        while (p != last) {
            std::cout << p->val<<" ";
            p = p->next;
        }
        std::cout << p->val << "\n";
    }
    //end method
   
    //begin operator
    flist& operator=(const flist& a) {
        flist copy = a;
        swap(copy);
        return *this;
    }

    T& operator[](size_t n) {
        Node<T>* p = first;
        for (int i = 0; i < n; ++i) {
            p = p->next;
        }
        return p->val;
    }
    T operator[](size_t n) const{
        Node<T>* p = first;
        for (int i = 0; i < n; ++i) {
            p = p->next;
        }
        return p->val;
    }
    //end operator
    struct itraretor {
        T* val;
    };
};
int main()
{
    flist<int> a={1,2,4,5};
    auto it=a.end();

    std::cout << *(it);
  
    
 
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
