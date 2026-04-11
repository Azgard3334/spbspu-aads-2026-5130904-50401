#ifndef LIST_HPP
#define LIST_HPP

namespace rizatdinov
{
  template< class elem > 
  struct Link
  {
    elem val;
    Link* succ;
  };

  template< class Elem >
  class Iterator
  {
    Link<Elem>* curr;
  public:
    template<class> friend class List;

    Iterator(Link<Elem>* p) :curr(p) {}

    Iterator& operator++() { curr = curr->succ; return *this; }
    Elem& operator*() const { return curr->val; }
    bool operator==(const  Iterator& b) const { return curr == b.curr; }
    bool operator!=(const Iterator& b) const { return curr != b.curr; }
  };

  template< class Elem >
  class ConstIterator
  {
    const Link<Elem>* curr;
  public:
    template<class> friend class List;

    ConstIterator(const Link<Elem>* p) :curr(p) {}

    ConstIterator& operator++() { curr = curr->succ; return *this; }
    const Elem& operator*() const { return curr->val; }
    bool operator==(const  ConstIterator& b) const { return curr == b.curr; }
    bool operator!=(const ConstIterator& b) const { return curr != b.curr; }
  };

  template< class Elem >
  class List
  {
    Link<Elem>* fake;
  public:
    List();
    List(const List& other);
    List(List&& list) noexcept;
    ~List();

    using iterator = Iterator<Elem>;
    using const_iterator = ConstIterator<Elem>;

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    iterator insert_after(iterator p, const Elem& v);
    iterator erase_after(iterator p);

    void push_front(const Elem& v);
    void pop_front();

    void clear();
  };

  template< class Elem >
  List<Elem>::List() {
    fake = new Link<Elem>;
    fake->succ = nullptr;
  }

  template< class Elem >
  List<Elem>::List(const List& other) {
    fake = new Link<Elem>;
    fake->succ = nullptr;
    *this = other;
  }

  template< class Elem >
  List<Elem>::List(List&& other) noexcept {
    fake = other.fake;
    other.fake = nullptr;
  }

  template< class Elem >
  List<Elem>::~List() {
    clear();
    delete fake;
  }

  template< class Elem >
  List<Elem>& List<Elem>::operator=(const List& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    iterator ptr = iterator(fake);
    for (iterator bpr = other.begin(); bpr != other.end(); ++bpr) {
      ptr = insert_after(ptr, *bpr);
    }
    return *this;
  }

  template< class Elem >
  List<Elem>& List<Elem>::operator=(List&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    clear();
    if (fake) {
      delete fake;
    }
    fake = other.fake;
    other.fake = nullptr;
    return *this;
  }

  template< class Elem >
  typename List<Elem>::iterator List<Elem>::begin() {
    return iterator(fake->succ);
  }

  template< class Elem >
  typename List<Elem>::const_iterator List<Elem>::begin() const {
    return const_iterator(fake->succ);
  }

  template< class Elem >
  typename List<Elem>::const_iterator List<Elem>::cbegin() const {
    return const_iterator(fake->succ);
  }

  template< class Elem >
  typename List<Elem>::iterator List<Elem>::end() {
    return iterator(nullptr);
  }

  template< class Elem >
  typename List<Elem>::const_iterator List<Elem>::end() const {
    return const_iterator(nullptr);
  }

  template< class Elem >
  typename List<Elem>::const_iterator List<Elem>::cend() const {
    return const_iterator(nullptr);
  }

  template< class Elem >
  typename List<Elem>::iterator List<Elem>::insert_after(iterator p, const Elem& v) {
    if (p == end()) {
      return p;
    }
    Link<Elem>* s = new Link<Elem>{v, p.curr->succ};
    p.curr->succ = s;
    return iterator(s);
  }

  template< class Elem >
  typename List<Elem>::iterator List<Elem>::erase_after(iterator p) {
    if (p == end() || p.curr->succ == nullptr) {
      return p;
    }
    Link<Elem>* s = p.curr->succ;
    p.curr->succ = s->succ;
    delete s;
    return iterator(p.curr->succ);
  }

  template< class Elem >
  void List<Elem>::push_front(const Elem& v) {
    insert_after(iterator(fake), v);
  }

  template< class Elem >
  void List<Elem>::pop_front() {
    erase_after(iterator(fake));
  }

  template< class Elem >
  void List<Elem>::clear() {
    while (begin() != end()) {
      pop_front();
    }
  }
}

#endif
