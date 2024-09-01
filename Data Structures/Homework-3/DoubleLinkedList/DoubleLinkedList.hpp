#pragma once

#include <cstddef>
#include <functional>
#include<stdexcept>
template <typename T> struct Node {
  Node *prev{nullptr};
  Node *next{nullptr};
  T data;
  Node(const T &element) : data{element}, next{nullptr}, prev{nullptr} {}
};

template <typename T> class DoubleLinkedList {
public:
  class Iterator;
  DoubleLinkedList():head_(nullptr), tail_(nullptr), size_(0){}
  DoubleLinkedList(const DoubleLinkedList& other): head_(nullptr), tail_(nullptr), size_(0){
    Node<T>* current = other.head_;
    while(current != nullptr){
      push_back(current->data);
      current = current->next;
    }
  }
  DoubleLinkedList(DoubleLinkedList&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {    
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  DoubleLinkedList &operator=(const DoubleLinkedList& other){   
    if(this!=&other){
      dealoc();
    Node<T>* current = other.head_;
    while(current != nullptr){
      push_back(current->data);
      current = current->next;
      }
    }
   return *this;
  }


  DoubleLinkedList &operator=(DoubleLinkedList&& other){  
    if(this != &other){
      dealoc();
    head_=other.head_;
    tail_=other.tail_;
    size_=other.size_;
    other.head_= other.tail_ = nullptr;
    other.size_ = 0;
    }
    return *this;
  }


  ~DoubleLinkedList(){
    dealoc();
  }

  DoubleLinkedList &push_back(const T& element){
    Node<T>* node = new Node<T>(element);
    if(tail_ == nullptr){
      head_ = tail_ = node;
    } else {
      node->prev = tail_;
      tail_->next = node;
      tail_ = node;
    }
    size_++;
    return *this;
  }


  DoubleLinkedList &push_front(const T& element){  
    Node<T>* node = new Node<T>(element);
    if(head_ == nullptr){
      head_ = tail_ = node;
    } else {
      node->prev = head_;
      head_->next = node;
      head_ = node;
    }
    size_++;
    return *this;
  }


  DoubleLinkedList &push_back(T&& element){  
    Node<T>* node = new Node<T>(std::move(element));
    if(tail_==nullptr){
      head_ = tail_ = node;
    } else {
      node->prev = tail_;
      tail_->next = node;
      tail_ = node;
    }
    size_++;
    return *this;
  }


  DoubleLinkedList &push_front(T&& element){ 
    Node<T>* node = new Node<T>(std::move(element));
    if(head_ == nullptr){
      head_ = tail_ = node;
    } else {
      node->next = head_;
      head_->prev = node;
      head_ = node;
    }
    size_++;
    return *this;
  }


  DoubleLinkedList &pop_front(){ 
    if(head_ == nullptr){
      throw std::out_of_range("Empty List");
      return *this;
    }

    if(head_==tail_){
      head_ = tail_ = nullptr;
    } else {
      head_ = head_->next;
      head_->prev = nullptr;
    }
    size_--;
    return *this;
  }


  DoubleLinkedList &pop_back(){
    if(tail_ == nullptr){
      throw std::out_of_range("Empty LIst");
      return *this;
    }

    if(head_==tail_){
      head_ = tail_ = nullptr;
    } else {
      tail_ = tail_->prev;
      tail_->next = nullptr;
    }
    size_--;
    return *this;
  }


  bool empty() const{
    return size_==0;
  }

  size_t size() const{
    return size_;
  }



  T &front(){
    if(head_ == nullptr){
      throw std::out_of_range("Empty List");
    }
    return head_->data;
  }


  T &back(){
    if(tail_ == nullptr){
      throw std::out_of_range("Empty List");
    }
    return tail_->data;
  }


  Iterator begin() const{ return Iterator(head_);}
  Iterator end() const{ return Iterator(nullptr);}
  const Iterator cbegin() const{ return Iterator(head_);}
  const Iterator cend() const { return Iterator(nullptr);}
  Iterator rbegin() const { return Iterator(tail_);}
  Iterator rend() const{ return Iterator(nullptr);}
  const Iterator rcbegin() const{ return Iterator (tail_);}
  const Iterator rcend() const{ return Iterator(nullptr);}



  void clear(){
    Node<T>* current = head_;
    while(current != nullptr){
      Node<T>* next = current->next;
      delete current;
      current = next;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
  }

  Iterator insert(Iterator& pos, const T& value){
    if(empty()) {
    Node<T>* newN = new Node<T>(value);
     head_ = tail_ = newN;
     ++size_;
     return Iterator(newN);
    }
    if(pos == begin())
      push_front(value);

   else if(pos == end())
      push_back(value);

  
   else {
     Node<T>* newN = new Node<T>(value);
    (pos.current)->prev->next = newN;
    newN->prev = pos.current->prev;
    newN->next = pos.current;
    pos.current->prev = newN;
    ++size_;
  }
      return --pos;
  }


  Iterator erase(Iterator& pos){
    if(empty()) throw std::out_of_range("empty");

      if(pos == begin())
        pop_front();

    else if(pos == end())
      pop_back();

    else{
      pos.current->prev->next = pos.current->next;
      pos.current->next->prev = pos.current->prev;
      delete pos.current;
      --size_;
    }
    return ++pos;
  }


Iterator erase(Iterator& beginIt, Iterator& endIt){
  if(empty()) throw std::out_of_range("empty");


    beginIt.current->prev->next = endIt.current;
    endIt.current->prev = beginIt.current->prev;

    while(beginIt.current != endIt.current){
  
    Node<T>* temp = beginIt.current->next;
    delete beginIt.current;
    beginIt.current = temp;
    --size_;
    }
  return endIt;
}



  void remove_if(std::function<bool(const T& element)> &&p){
    Node<T>* current = head_;
    while(current != nullptr){
      if(p(current->data)){
        if(current==head_){
          pop_front();
          current = head_;
        } 
        else if(current == tail_) { 
          pop_back();
          current == nullptr;
        }
        else {
          current->prev->next = current->next;
          current->next->prev = current->prev;
          Node<T>* temp = current->next;
          delete current;
          current = temp;
          --size_;
        }
    }
      else 
        current = current->next;
  }
  }

  void reverse(){
    Node<T>* current = head_;
    while(current){
      Node<T>* temp = current->next;
      current->next = current->prev;
      current->prev = temp;
      current = temp;
    }
    Node<T>* temp = head_;
    head_ = tail_;
    tail_ = temp;
  }
  Iterator find(const T &element) const{
    Node<T>* current = head_;
    while(current){
      if(current->data == element){
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

private:
  void dealoc();
  Node<T> *head_{nullptr};
  Node<T> *tail_{nullptr};
  size_t size_{0};
};


template<typename T>
void DoubleLinkedList<T>::dealoc(){
  Node<T>* current = head_;
  while(current != nullptr){
    Node<T>* next = current->next;
    delete current;
    current = next;
  }
  head_ = tail_ = nullptr;
  size_ = 0;
}
////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class DoubleLinkedList<T>::Iterator{
  public:

    using value_type = T;
    using reference  = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;




    Iterator(): current(nullptr){}
    Iterator(Node<T>* node): current(node){}
    Iterator(const Iterator& other): current(other.current){}
    Iterator(Iterator&& other) noexcept : current(other.current){other.current = nullptr;}
    Iterator& operator=(const Iterator& other){
      if(this != &other){
        current = other.current;
      }
      return *this;
    }
    Iterator& operator=(Iterator&& other){
      if(this != &other){
        current = other.current;
        other.current = nullptr;
      }
      return *this;
    }
    T& operator*(){ return current->data; }
    const T& operator*() const {return current->data;}
    T* operator->(){ return &(current->data); }
    const T* operator->() const {return &(current->data);}

    Iterator& operator++(){
      if(current){
        current=current->next;
      }
      return *this;
    }


    Iterator operator++(int){
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    Iterator& operator--(){
      if(current){
        current = current->prev;
      }
      return *this;
    }

    Iterator operator--(int){
      Iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const Iterator& other) const { return current == other.current;}
    bool operator!=(const Iterator& other) const { return current != other.current;}

    Node<T>* node() const { return current; }

  private:
    Node<T>* current;
    friend class DoubleLinkedList;
};
