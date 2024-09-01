#pragma once
#include <initializer_list>
#include <iterator>

template <typename T>
class MojVektor {
  public:
  class Iterator;//
  MojVektor();//
  MojVektor(const std::initializer_list<T>&);//
  MojVektor(const MojVektor&);//
  MojVektor& operator=(const MojVektor&);//
  MojVektor(MojVektor&&);//
  MojVektor& operator=(MojVektor&&);//
  ~MojVektor();//
  MojVektor& push_back(const T&);//
  MojVektor& push_front(const T&);//
  MojVektor& push_back(T&&);//
  MojVektor& push_front(T&&);//
  size_t size() const {return size_; }//
  T& at(size_t) const;//
  T& operator[](size_t index) const {return arr_[index];}//
  void clear();//
  void resize(size_t newSize, const T& difference_value);//
  MojVektor& pop_back();//
  MojVektor& pop_front();//
  T& back() const;//
  T& front() const;//
  bool empty() const {return size_==0;}//
  size_t capacity() const { return capacity_;}//
  bool operator==(const MojVektor&) const;//
  bool operator!=(const MojVektor&) const;//
  bool full() const {return size_==capacity_;}//
  MojVektor subvector(Iterator begin, Iterator end);//
  Iterator begin() const{ return Iterator(arr_);}//
  Iterator end() const {return Iterator(arr_+ size_);}//
  Iterator find(const T&) const;//
  Iterator erase(Iterator pos);//
  Iterator insert(Iterator, const T&);
  Iterator insert(Iterator, T&&);
  Iterator rbegin() const{return Iterator(arr_+size_-1);}//
  Iterator rend() const{return Iterator(arr_-1);}//
  Iterator erase(Iterator beginIt, Iterator endIt);
  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);

  T* data(){return arr_;}

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

// Implementacija ovdje
template<typename T>
void MojVektor<T>::realoc(){
  auto temp=new T[capacity_];
  std::move(arr_, arr_+size_, temp);
  delete[] arr_;
  arr_ = temp;
}

template<typename T>
MojVektor<T>::MojVektor() :
  size_{0},
  capacity_{10},
  arr_{new T[capacity_]} {}

template<typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& list){
  size_=list.size();
  capacity_=list.size();
  arr_=new T[capacity_];
  std::copy(list.begin(),list.end(), arr_);
}

template<typename T>
  MojVektor<T>::MojVektor(const MojVektor& other){
  size_=other.size_;
  capacity_=other.capacity_;
  arr_=new T[capacity_];
  std::copy(other.arr_, other.arr_ + other.size_, arr_);
  }

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& other){
if(this != &other){
  delete[] arr_;
  size_=other.size_;
  capacity_=other.capacity_;
  arr_=new T[capacity_];
  std::copy(other.arr_, other.arr_ + other.size_, arr_);
  }
  return *this;
}

template<typename T>
MojVektor<T>::MojVektor(MojVektor&& other){
  size_=other.size_;
  capacity_=other.capacity_;
  arr_=other.arr_;
  other.arr_=nullptr;
  other.size_ = other.capacity_ = 0;
}


template<typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& other){
  if(this != &other){
    delete[] arr_;
    size_=other.size_;
    capacity_=other.capacity_;
    arr_=other.arr_;
    other.arr_=nullptr;
    other.size_=other.capacity_=0;
  
  }
 return *this;
}

template<typename T>
MojVektor<T>::~MojVektor() {
	delete[] arr_;
	arr_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& elem){
  if (arr_==nullptr){
  arr_=new T[capacity_];}
  if (size_==capacity_){
    capacity_ = capacity_*2;
    auto temp = new T[capacity_];
    std::move(arr_, arr_+size_, temp);
    delete[] arr_;
    arr_=temp;
  }
  arr_[size_++]=elem;
    return *this;

  
}
template<typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& elem){
  if(arr_ == nullptr){
    arr_= new T[capacity_];
  }

  if(capacity_> (size_+1)){
    std::move(arr_, arr_+size_, arr_+1);
    arr_[0]=elem;
    ++size_;
    return *this;
  }
  capacity_ *= 2;
  auto temp = new T[capacity_];
  std::move(arr_, arr_+size_, temp+1);
  temp[0]=elem;
  delete[] arr_;
  arr_=temp;
  ++size_;
  return *this;
}


template<typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& elem){
  if(arr_==nullptr){
  arr_= new T[capacity_];}

  if(capacity_<size_+1){
  capacity_ *= 2;
  auto temp = new T[capacity_];
  std::move(arr_, arr_+size_, temp);
  temp[0]=elem;
  delete[] arr_;
  arr_=temp;
  }
  arr_[size_++]=std::move(elem);
  return *this;
}


template<typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& elem){
  if (arr_ == nullptr) {
		arr_ = new T[capacity_];
	}
	if (size_ < capacity_) {
		std::move(arr_, arr_ + size_, arr_ + 1);
		arr_[0] = std::move(elem);
		++size_;
		return *this;
	}
	capacity_ *= 2;
	auto temp = new T[capacity_];
	std::move(arr_, arr_ + size_,temp + 1);
	delete[] arr_;  
  arr_ = temp;
  arr_[0]=std::move(elem);
  return *this;
}


template<typename T>
  T& MojVektor<T>::at(size_t num) const {
	if (num >= size_)
		throw std::out_of_range{
		"Van granica."
	};
	return arr_[num];
  }

template<typename T>
void MojVektor<T>::clear() {
	delete[] arr_;
	size_ = 0;
	arr_ = nullptr;
}

template<typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value) {
	if (newSize <= size_) {
		size_ = newSize;
		return;
	}
	if (newSize >= capacity_) {
		capacity_ = 2 * newSize;
    auto temp = new T[capacity_];
    std::move(arr_, arr_+size_, temp);
    delete[] arr_;
    arr_=temp;
	}
	for (auto i = size_; i < newSize; ++i) {
		arr_[i] = difference_value;
	}
  size_=newSize;
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_back() {
	if (empty())
		throw std::out_of_range{"Vektor je prazan."};
	--size_;
	return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_front() {
	if (empty())
		throw std::out_of_range{"Vektor je prazan."};
	std::move(arr_ + 1, arr_ + size_, arr_);
	--size_;
	return *this;
}

template<typename T>
T& MojVektor<T>::back() const {
	if (empty())
		throw std::out_of_range{"Vektor je prazan."};
	return arr_[size_ - 1];
}

template<typename T>
T& MojVektor<T>::front() const {
	if (empty())
		throw std::out_of_range{"Vektor je prazan."};
	return arr_[0];
}
template<typename T>
bool MojVektor<T>::operator==(const MojVektor& other) const {
	if (size_ != other.size_)
		return false;
  int br=0;
	for (auto i = 0; i < size_; ++i) {
		if (arr_[i] == other.arr_[i])
			br++;
	}
	return br==size_;
}

template<typename T>
bool MojVektor<T>::operator!=(const MojVektor& other) const {
  return !(this==other);
}

///////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class MojVektor<T>::Iterator {
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using difference_type = std::ptrdiff_t;

	Iterator() : ptr_{nullptr} {}
	Iterator(T* ptr) : ptr_{ptr} {}
	Iterator(const Iterator& other) : ptr_{other.ptr_} {}
	Iterator(Iterator&& other) : ptr_{other.ptr_} {
		other.ptr_ = nullptr;
	}

	Iterator& operator=(const Iterator& other) {
		ptr_ = other.ptr_;
		return *this;
	}

	Iterator& operator=(Iterator&& other) {
		ptr_ = other.ptr_;
		other.ptr_ = nullptr;
		return *this;
	}

	Iterator& operator++() {
		++ptr_;
		return *this;
	}

	Iterator operator++(int) {
		auto temp = *this;
		++ptr_;
		return temp;
	}

	Iterator& operator--() {
		--ptr_;
		return *this;
	}

	Iterator operator--(int) {
		auto temp = *this;
		--ptr_;
		return temp;
	}

	T* operator->() { return ptr_; }
	T* operator->() const { return ptr_; }

	T& operator*() { return *ptr_; }
	T& operator*() const { return *ptr_; }

	T* operator[](size_t index) { return ptr_ + index; }
	T* operator[](size_t index) const { return ptr_ + index; }

	bool operator==(const Iterator& other) const {
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator& other) const {
		return ptr_ != other.ptr_;
	}

	bool operator<(const Iterator& other) const {
		return ptr_ < other.ptr_;
	}

	Iterator operator+(int n) const {
		return Iterator{ptr_ + n};
	}

	Iterator operator-(int n) const {
		return Iterator{ptr_ - n};
	}

	int operator-(const Iterator& other) const {
		return ptr_ - other.ptr_;
	}

	T* data() const { return ptr_; }
private:
	T* ptr_;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
MojVektor<T> MojVektor<T>::subvector(typename MojVektor<T>::Iterator begin, typename MojVektor<T>::Iterator end){
MojVektor<T> res;
if((end-begin)<0) throw std::out_of_range("Invalid");
res.capacity_=end-begin+1;
res.arr_=new T[res.capacity_];
res.size_=end-begin;
std::copy(begin.data(), end.data(), res.arr_);

return res;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& value) const {
	for (auto it = begin(); it != end(); ++it) {
		if (*it == value)
			return it;
	}
	return end();
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(typename MojVektor<T>::Iterator pos) {
if (pos < begin()) {
			throw std::out_of_range("Invalid");
		}
		if (pos == end()) {
			return end();
		}
		Iterator it{ pos };
		while (it != end()) {
			*(it) = std::move(*(it + 1));
			++it;
		}
		--size_;
		return pos;
}


template<typename T>
 typename MojVektor<T>::Iterator MojVektor<T>::insert(typename MojVektor<T>::Iterator pos, const T& value) {
	if (pos == end())
		throw std::out_of_range{"Invalid"};

  if (pos == begin()) {
		push_front(value);
		return Iterator{arr_};
	}

  if(capacity_ == size_)
  realoc();

  auto temp=0;
  for(auto i=0; i<size_; ++i){
  if(arr_[i]==*pos) temp=i;
  }

  for(auto j=size_; j>temp; --j){
  arr_[j]=arr_[j-1];}

  arr_[temp]=value;
  Iterator it=arr_+temp;
  ++size_;
  return it;
  
  

	}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(typename MojVektor<T>::Iterator pos, T&& value) {
	if (pos == end())	throw std::out_of_range{"Van granica."};
  if (empty()) push_back(value);
  if(size_==capacity_) realoc();

  auto temp=0;
  for(auto i=0;i<size_;++size_){
  if(arr_[i]==*pos) temp = i;
  }
  for(auto i=size_; i>temp; --i )
  arr_[i]=arr_[i-1];

  arr_[temp]=std::move(value);
  Iterator it=arr_+temp;
  ++size_;

  return it;
  

}

template<typename T>
void MojVektor<T>::rotate() {
  auto it1 = rbegin(); 
  auto it2 = begin();
	while (it2 < it1) {
		std::swap(*it2, *it1);
		++it2;
		--it1;
	}
}

template<typename T>
void MojVektor<T>::rotate(typename MojVektor<T>::Iterator beginIt, typename MojVektor<T>::Iterator endIt) {
	auto it1 = endIt - 1;
	auto it2 = beginIt;
	while (it2 < it1) {
		std::swap(*it2, *it1);
		++it2;
		--it1;
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MojVektor<T>& vec) {
	if (vec.empty()) {
		os << "{}";
		return os;
	}
	os << '{';
	for (auto i = 0; i < vec.size(); ++i) {
		if (vec[i] == vec.back()) {
			os << vec[i];
			continue;
		}
		os << vec[i] << ", ";
	}
	os << '}';
	return os;
}


template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(typename MojVektor<T>::Iterator beginIt, typename MojVektor<T>::Iterator endIt) {
	if ((endIt - beginIt) < 0) throw std::out_of_range("Invalid range");
	std::move(endIt.data(), arr_ + size_,	beginIt.data());
	size_ = size_ - (endIt - beginIt);
	return Iterator(arr_ + (beginIt.data() - arr_));
}
