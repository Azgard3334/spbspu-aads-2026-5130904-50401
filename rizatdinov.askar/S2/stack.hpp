#ifndef STACK_HPP
#define STACK_HPP

#include <utility>
#include <stdexcept>

namespace rizatdinov {
  template< class T, class Container >
  class Stack {
    private:
      Container data;
    public:
      explicit Stack(const Container& cont = Container());
      Stack(const Stack& other);
      Stack(Stack&& other);

      void push(const T& value);
      void push(T&& value);

      void pop();
      T drop();

      T& top();
      const T& top() const;

      bool empty() const;
  };

  template< class T, class Container >
  Stack< T, Container >::Stack(const Container& cont) : data(cont) {}

  template< class T, class Container >
  Stack< T, Container >::Stack(const Stack& other) : data(other.data) {}

  template< class T, class Container >
  Stack< T, Container >::Stack(Stack&& other) : data(std::move(other.data)) {}

  template< class T, class Container >
  void Stack< T, Container >::push(const T& value) {
    data.push_front(value);
  }

  template< class T, class Container >
  void Stack< T, Container >::push(T&& value) {
    data.push_front(std::move(value));
  }

  template< class T, class Container >
  void Stack< T, Container >::pop() {
    data.pop_front();
  }

  template< class T, class Container >
  T Stack< T, Container >::drop() {
    T val = std::move(this->top());
    data.pop_front();
    return val;
  }

  template< class T, class Container >
  T& Stack< T, Container >::top() {
    if (data.is_empty()) {
      throw std::out_of_range("error: stack is empty");
    }
    return *data.begin();
  }

  template< class T, class Container >
  const T& Stack< T, Container >::top() const {
    if (data.is_empty()) {
      throw std::out_of_range("error: stack is empty");
    }
    return *data.cbegin();
  }

  template< class T, class Container >
  bool Stack< T, Container >::empty() const {
    return data.is_empty();
  }
}

#endif
