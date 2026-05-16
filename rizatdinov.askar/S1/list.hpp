#ifndef LIST_HPP
#define LIST_HPP

namespace rizatdinov
{
  template< class Elem >
  struct Link
  {
    Elem val;
    Link* succ;
  };

  template< class Elem > class List;
  template< class Elem >
  class LIter {
    friend class List< Elem >;

    Link< Elem >* curr;
  public:
    LIter(): curr(nullptr) {}
    LIter(Link< Elem >* p): curr(p) {}

    LIter& operator++() { curr = curr->succ; return *this; }
    LIter operator++(int) {
      LIter temp = *this;
      curr = curr->succ;
      return temp;
    }
    Elem& operator*() { return curr->val; }
    bool operator==(const LIter& b) const { return curr == b.curr; }
    bool operator!=(const LIter& b) const { return curr != b.curr; }
  };

  template< class Elem >
  class LCIter {
    friend class List< Elem >;

    const Link< Elem >* curr;
  public:
    LCIter(): curr(nullptr) {}
    LCIter(const Link< Elem >* p): curr(p) {}

    LCIter& operator++() { curr = curr->succ; return *this; }
    LCIter operator++(int) {
      LCIter temp = *this;
      curr = curr->succ;
      return temp;
    }
    const Elem& operator*() const { return curr->val; }
    bool operator==(const LCIter& b) const { return curr == b.curr; }
    bool operator!=(const LCIter& b) const { return curr != b.curr; }
  };

  template< class Elem >
  class List {
    Link< Elem >* fake;
  public:
    using iterator = LIter< Elem >;
    using const_iterator = LCIter< Elem >;

    List();
    List(const List& other);
    List(List&& other) noexcept;
    ~List();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    iterator before_begin();
    const_iterator before_begin() const;
    const_iterator cbefore_begin() const;

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

    bool is_empty();
    void clear();
  };

  template< class Elem >
  List< Elem >::List() {
    fake = new Link< Elem >;
    fake->succ = nullptr;
  }

  template< class Elem >
  List< Elem >::List(const List& other) {
    fake = new Link< Elem >;
    fake->succ = nullptr;
    iterator ptr = iterator(fake);
    for (const_iterator bpr = other.begin(); bpr != other.end(); ++bpr) {
      ptr = insert_after(ptr, *bpr);
    }
  }

  template< class Elem >
  List<Elem>::List(List&& other) noexcept {
    fake = other.fake;
    other.fake = new Link< Elem >;
    other.fake->succ = nullptr;
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
    delete fake;
    fake = other.fake;
    other.fake = new Link< Elem >;
    other.fake->succ = nullptr;
    return *this;
  }

  template< class Elem >
  typename List<Elem>::iterator List<Elem>::before_begin() {
    return iterator(fake);
  }

  template< class Elem >
  typename List<Elem>::const_iterator List<Elem>::before_begin() const {
    return const_iterator(fake);
  }

  template< class Elem >
  typename List<Elem>::const_iterator List<Elem>::cbefore_begin() const {
    return const_iterator(fake);
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
  bool List<Elem>::is_empty() {
    return fake->succ == nullptr;
  }

  template< class Elem >
  void List<Elem>::clear() {
    while (fake->succ) {
      pop_front();
    }
  }
}

#endif
