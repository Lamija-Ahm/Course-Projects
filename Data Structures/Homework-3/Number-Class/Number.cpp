#include"Number.hpp"


Number::Number(): negative_{false}{}


Number::Number(int value){
    if(value < 0){
      negative_ = true;
      value = -value;
    } else { negative_ = false; }

    if(value == 0) digits_.push_back(0);

    while(value > 0){
      digits_.push_front(value % 10);
      value /= 10;
    }
  }

Number::Number(Number&& other) noexcept {
  negative_ = other.negative_;
  digits_ = std::move(other.digits_);
  other.negative_ = false;
}


Number& Number::operator=(const Number& other){
  if(this != &other){
    digits_ = other.digits_;
    negative_ = other.negative_;
  }
  return *this;
}


Number& Number::operator=(Number&& other){
  if(this != &other){
    digits_.clear();
    digits_ = std::move(other.digits_);
    negative_ = other.negative_;
    other.negative_ = false;
  }
  return *this;
}


Number::Number(Number& other): digits_{other.digits_}, negative_{other.negative_}{}

Number Number::add(const Number& other, bool res_sign) const{
  Number res;
  res.negative_ = res_sign;
  auto it1 = digits_.rbegin();
  auto it2 = other.digits_.rbegin();
  int pamti = 0;

  while(it1 != digits_.rend() || it2 != other.digits_.rend() || pamti != 0){
    int sum = pamti;

    if(it1 != digits_.rend()){
      sum += *it1;
      ++it1;
    }
    if(it2!= other.digits_.rend()){
      sum += *it2;
      ++it2;
    }
    res.digits_.push_front(sum % 10);
    pamti = sum/10;
  }   
  res.absolute();
  return res;
}

void Number::absolute() {
    auto it = digits_.begin();
    while (it != digits_.end() && *it == 0) {
        it = digits_.erase(it);
    }

    if (digits_.empty()) {
        digits_.push_back(0);
    }
    
    if (digits_.size() == 1 && digits_.front() == 0) {
        negative_ = false;
    }
}
Number Number::operator+(const Number& other) const{
  if(negative_ == other.negative_){
    return add(other, negative_);
  } else {return subtract(other);}
}

Number Number::operator-(const Number& other) const{
 if(negative_ != other.negative_){
  return add(other, negative_);
 } else { return subtract(other, *this<other);}
}

Number& Number::operator+=(const Number& other){
 *this = *this + other;
  return *this;
}


Number& Number::operator-=(const Number& other) {
  *this = *this - other;
  return *this;
}

bool Number::operator==(const Number& other) const {
        if (negative_ != other.negative_ || digits_.size() != other.digits_.size()) {
            return false;
        }
        auto it1 = digits_.begin();
        auto it2 = other.digits_.begin();
        while (it1 != digits_.end() && it2 != other.digits_.end()) {
            if (*it1 != *it2) {
                return false;
            }
            ++it1;
            ++it2;
        }
        return true;
    }


bool Number::operator!=(const Number& other) const {
        return !(*this == other);
    }

bool Number::operator<(const Number& other) const {
        if (negative_ && !other.negative_) {
            return true;
        } else if (!negative_ && other.negative_) {
            return false;
        } else if (negative_ && other.negative_) {
            if (digits_.size() != other.digits_.size()) {
                return digits_.size() > other.digits_.size();
            }
            auto it1 = digits_.begin();
            auto it2 = other.digits_.begin();
            while (it1 != digits_.end() && it2 != other.digits_.end()) {
                if (*it1 != *it2) {
                    return *it1 < *it2;
                }
                ++it1;
                ++it2;
            }
            return false;
        } else {
            if (digits_.size() != other.digits_.size()) {
                return digits_.size() < other.digits_.size();
            }
            auto it1 = digits_.begin();
            auto it2 = other.digits_.begin();
            while (it1 != digits_.end() && it2 != other.digits_.end()) {
                if (*it1 != *it2) {
                    return *it1 < *it2;
                }
                ++it1;
                ++it2;
            }
            return false;
        }
    }


bool Number::operator<=(const Number& other) const {
        return (*this < other) || (*this == other);
    }

    bool Number::operator>(const Number& other) const {
        return !(*this <= other);
    }

    bool Number::operator>=(const Number& other) const {
        return !(*this < other);
    }
