#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Stack {
public:
  Stack():capacity_{10}, size_{0}, arr_{new T[capacity_]}{}
  Stack(const Stack& other):capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]}{
    std::copy(other.arr_, other.arr_ + size_ + 1, arr_);
  }
  Stack(Stack&& other): capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_}{
    other.arr_ = nullptr;
    other.size_ = 0;
  }
  Stack &operator=(const Stack& other){
    if(this != &other){
      capacity_ = other.capacity_;
      size_ = other.size_;
      T* newarr = arr_;
      arr_ = new T[capacity_];
      std::copy(other.arr_, other.arr_ + size_ + 1, arr_);
      delete[] newarr;
    }
    return *this;
  
  }
  Stack &operator=(Stack&& other){
    if(this != &other){
      capacity_ = other.capacity_;
      size_ = other.size_;
      arr_ = other.arr_;
      other.arr_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }
  T pop(){
    if(empty()) throw std::out_of_range("Empty List");

    auto temp = arr_[size_ - 1];
    --size_;
    return temp;
  }
  T &top() const{ return arr_[size_ - 1];}
  // Savrseno proslijedjivane (forward referenca)
  template <typename U> Stack<T> &push(U&& value){
    if(full()) realoc();

    arr_[size_++]=std::forward<U>(value);
    return *this;
  }
  size_t size() const{ return size_;}
  size_t capacity() const{ return capacity_;}
  bool empty() const{ return size_ == 0;}
  bool full() const{ return size_ == capacity_;}
  ~Stack(){
    delete[] arr_;
    size_ = capacity_ = 0;
  }
  void clear(){ size_ = 0;}
  void resize(size_t newSize){ size_ = newSize;}
  bool operator==(const Stack& other){
    if(size_ != other.size_)
      return false;

    for(auto i = 0; i<size_; ++i){
      if(arr_[i] != other.arr_[i])
        return false;
    }
    return true;
  }
  bool operator!=(const Stack& other){
    return !(*this==other);
  }

private:
  void realoc(){
    capacity_ = capacity_ * 2;
    T* newarr = new T[capacity_];
    std::copy(arr_, arr_ + size_ + 1, newarr);
    delete[] arr_;
    arr_ = newarr;
  }
  size_t capacity_{0};
  size_t size_{0};
  T *arr_{nullptr};
};
