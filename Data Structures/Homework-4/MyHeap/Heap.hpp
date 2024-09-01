#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class Heap {
private:
    
    size_t capacity_;
    size_t size_;
    T* array_;
    void balanceDown(size_t ind){
      if (ind < size_)
        {
            size_t left = (2 * ind) + 1;
            size_t right = (2 * ind + 2);
            if (left < size_ && right < size_)
            {
                size_t maxA = array_[left] < array_[right]
                                    ? right
                                    : left;
                std::swap(array_[ind], array_[maxA]);
                balanceDown(maxA);
            }
            else if (left < size_ && right >= size_)
            {
                std::swap(array_[ind], array_[left]);
                balanceDown(left);
            }
            else if (left >= size_ && right < size_)
            {
                std::swap(array_[ind], array_[right]);
                balanceDown(right);
            }
        }
    }

    void balanceUp()
    {
        size_t ind = size_ - 1;
        while (ind > 0)
        {
            size_t parent = (ind - 1) / 2;
            if (array_[ind] > array_[parent])
            {
                std::swap(array_[ind], array_[parent]);
                ind = (ind - 1) / 2;
            }
            else
            {
                break;
            }
        }
    }

public:
        Heap() : capacity_{10}, size_{0}, array_{new T[capacity_]} {}
     
        ~Heap()
    {
        delete[] array_;
    }

         Heap(const Heap &other) : capacity_{other.capacity_}, size_{other.size_}, array_{new T[capacity_]}
    {
        std::copy(other.array_, other.array_ + size_, array_);
    }
    Heap(Heap&& other) : capacity_{other.capacity_}, size_{other.size_}, array_{other.array_}
    {
        other.size_ = 0;
        other.array_ = nullptr;
    }
    Heap& operator=(const Heap& other)
    {
        delete[] array_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = new T[capacity_];
        std::copy(other.array_, other.array_ + size_, array_);
        return *this;
    }
    Heap& operator=(Heap&& other)
    {
        delete[] array_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = other.array_;
        other.size_ = 0;
        other.array_ = nullptr;
        return *this;
    }
        bool full()const {return size_ == capacity_;}
    
        
        template<typename U>
        Heap& insert(U&& value) {
        if(full()){
           T *newA = array_;
        capacity_ *= 2;
        array_ = new T[capacity_];
        std::copy(newA, newA + size_, array_);
        delete[] newA;
        }
        array_[size_++]=std::forward<U>(value);
    }

        bool empty()const {return size_ == 0;}

        T& max() {
          if (empty()) {
            throw std::runtime_error("Empty");
          }
          return array_[0];
        }

    Heap& removeMax() {
        if (empty()) {
            throw std::runtime_error("Heap is empty");
        }

        array_[0]=array_[--size_];
        balanceDown(0);
        return *this;
    }

     T& min()
    {
        if (empty()) throw std::out_of_range {"Empty"};
        size_t minE = 0;
        for (auto i  = 1; i < size_; i++)
        {
            if (array_[i] < array_[minE])
            {
                minE = i;
            }
        }
        return array_[minE];
    }
    Heap& removeMin()
    {
        if (empty()) throw std::out_of_range {"Empty"};
       size_t minE=0;
        for(size_t i=1; i<size_; ++i){
          if(array_[i]<array_[minE]){
            minE = i;
          }
        }
        std::swap(array_[--size_], array_[minE]);
        balanceDown(minE);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream& out, const Heap& heap) {

      out<<"["; 
      for(auto i=0; i<heap.size_; ++i){
        if(i<heap.size_-1){
          out<<heap.array_[i]<<",";
        } else {
          out<<heap.array_[i];
        }
      }
      out<<"]";
      return out;
    }
      
