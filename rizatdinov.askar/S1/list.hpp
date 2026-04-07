#ifndef LIST_HPP
#define LIST_HPP

namespace rizatdinov
{
  template<class Elem> struct Link
  {
    Elem val;
    Link* succ;
  };

  template<class Elem> class List
  {
    Link<Elem>* fake;
  public:
    List();
    ~List();

    class iterator;

    iterator begin();
    iterator end();

    iterator insert_after(iterator p, const Elem& v);
    iterator erase_after(iterator p);

    void push_front(const Elem& v);
    void pop_front();
  };

  template<class Elem> List<Elem>::List() {
    fake = new Link<Elem>;
    fake->succ = nullptr;
  }

  template<class Elem> List<Elem>::~List() {
    Link<Elem>* ptr = fake->succ;
    while (ptr != nullptr) {
      Link<Elem>* succ = ptr->succ;
      delete ptr;
      ptr = succ;
    }
    delete fake;
  }

  template<class Elem> class List<Elem>::iterator
  {
    Link<Elem>* curr;
  public:
    iterator(Link<Elem>* p) :curr(p) {}

    iterator& operator++() { curr = curr->succ; return *this; }
    Elem& operator*() { return curr->val; }
    bool operator==(const  iterator& b) const { return curr == b.curr; }
    bool operator!=(const iterator& b) const { return curr != b.curr; }
  };

  template<class Elem> iterator List<Elem>::begin() {
    return iterator(fake->succ);
  }
  template<class Elem> iterator List<Elem>::end() {
    return iterator(nullptr);
  }
  template<class Elem> iterator List<Elem>::insert_after(iterator p, const Elem& v) {
    if (p == end()) {
      return p;
    }
    Link<Elem>* s = new Link<Elem>{v, p.curr->succ};
    p.curr->succ = s;
    return iterator(s);
  }
  template<class Elem> iterator List<Elem>::erase_after(iterator p) {
    if (p == end() || p.curr->succ == nullptr) {
      return p;
    }
    Link<Elem>* s = p.curr->succ;
    p.curr->succ = s->succ;
    delete s;
    return iterator(p.curr->succ);
  }
  template<class Elem> void List<Elem>::push_front(const Elem& v) {
    insert_after(iterator(fake), v);
  }
  template<class Elem> void List<Elem>::pop_front() {
    if (begin() == end()) {
      return;
    }
    erase_after(iterator(fake));
  }
}

#endif
