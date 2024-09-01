#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Queue {
public:
  Queue(): capacity_{10}, size_{0}, arr_{new T[capacity_]}, front_{0}, back_{0}{}
  
  Queue(const Queue& other);

  Queue(Queue && other){
    
    capacity_=other.capacity_;
    size_= other.size_;
    arr_ = other.arr_;
    front_ = other.front_;
    back_ = other.back_;
    
    other.arr_ = nullptr;
    other.size_ = 0;
  }

  Queue &operator=(const Queue& other){
   if(this == &other)
     return *this;


    capacity_=other.capacity_;
    size_= other.size_;
    back_ = other.back_;
    front_ = other.front_;
    T* temp = arr_;
    arr_ = new T[capacity_];
    std::copy(other.arr_, other.arr_ + size_ + 1, arr_);
    delete[] temp;
  return *this;
  }


  Queue &operator=(Queue&& other) {
    if(this == &other)
      return *this;

    capacity_= other.capacity_;
    size_= other.size_;
    arr_ = other.arr_;
    front_ = other.front_;
    back_ = other.back_;
    
    other.arr_ = nullptr;
    other.size_ = 0;
    return *this;
    }
  
  
  ~Queue(){
    delete [] arr_;
    capacity_ = size_ = 0;

  }
  // Add new element at the end of the queue
  template <typename U> Queue& push(U&& value){
    if(size_ == 0){
      arr_[back_] = std::forward<U>(value);
    } else {
      back_ = (back_ + 1)%capacity_;
      arr_[back_] = std::forward<U>(value);
    }
    ++size_;
    return *this;
  }
  // Pop an element from the begin
  T pop(){
    if(empty())
      throw std::out_of_range("");

    auto value = std::move(arr_[front_]);
    front_ = (front_+1)%capacity_;
    --size_;
    return value;
  }
  T &front(){
    if(empty())
      throw std::out_of_range("empty");
    return arr_[front_];
  }
  size_t size() const {return size_;}
  size_t capacity() const{return capacity_;}
  bool empty() const{return size_ == 0;}
  bool full() const{return size_ == capacity_;}
  void clear(){
    delete [] arr_;
    arr_ = nullptr;
    capacity_ = size_ = front_ = 0;
  }

private:
  void copyQueue(const Queue& other){
	 other.capacity_ = this->capacity_;
	 other.size_ = this->size_;
   other.arr_ = new T[other.capacity_];
   other.front_ = this->front_;
   other.back_ = this->back_;
   for (int i = 0; i < this->size_; ++i) {
   other.arr_[i] = this->arr_[(this->front_ + i) % this->capacity_];
  }
}

  size_t capacity_{0};
  size_t size_{0};
  T *arr_{nullptr};
  // Index sa koje strane se dodaje
  size_t back_{0};
  // Index sa koje strane se uklanja
  size_t front_{0};
};


template<typename T>
  Queue<T>::Queue(const Queue& other): capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]}, back_{other.back_}, front_{other.front_}{
    std::copy(other.arr_, other.arr_ + size_ +1, arr_);
  }
