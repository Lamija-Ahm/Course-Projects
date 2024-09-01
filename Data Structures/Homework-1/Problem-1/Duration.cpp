#include "duration.hpp"
#include<stdexcept>
#include<iostream>


Duration::Duration(int secs){

  seconds_ = secs;

  hours_ = seconds_/ 3600;
  seconds_ %= 3600;

  minutes_ = seconds_ / 60;
  seconds_ %= 60;
  }

  Duration::Duration(int hours, int minutes, int seconds){
    if (hours < 0) throw std::out_of_range("Pogresan unos sati");
  hours_ = hours;
    
    if (minutes >= 60 || minutes < 0) throw std::out_of_range("Pogresan unos minuta");
  minutes_ = minutes;

    if (seconds >= 60 || seconds < 0) throw std::out_of_range("Pogresan unos sekundi");
  seconds_ = seconds;
  }


  Duration& Duration::set_h(int hours){
      if (hours < 0) throw std::out_of_range("Pogresan unos sati");
      hours_ = hours;
      return *this;
    }
  Duration& Duration::set_m(int minutes){
     if (minutes >= 60 || minutes < 0) throw std::out_of_range("Pogresan unos minuta");
     minutes_ = minutes;
     return *this;
    }
  Duration& Duration::set_s(int seconds){
   if (seconds >= 60 || seconds < 0) throw std::out_of_range("Pogresan unos sekundi");
   seconds_ = seconds;
   return *this;
  }

  bool Duration::operator==(const Duration& other) const {
  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
  return full_time1 == full_time2;
}

bool Duration::operator!=(const Duration& other) const {
  
  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
  return full_time1 != full_time2;
}


bool Duration::operator<(const Duration& other) const {

  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
  return full_time1 < full_time2;
}

bool Duration::operator>(const Duration& other) const {

  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
  return full_time1 > full_time2;
}

bool Duration::operator<=(const Duration& other) const {

  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
  return full_time1 <= full_time2;
}

bool Duration::operator>=(const Duration& other) const {

  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
  return full_time1 >= full_time2;
}

  Duration Duration::operator+(const Duration& other)
{
  
  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;

  return Duration(full_time1 + full_time2);

}

  Duration Duration::operator+(const Duration& other) const
{

  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
	return Duration(full_time1 + full_time2);
}

  Duration Duration::operator+=(const Duration& other){
    return *this = *this + other;
  }

  Duration Duration::operator-(const Duration& other) {

  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
  if(full_time1<full_time2) throw std::out_of_range("Oduzimanje veceg broja od manjeg");

	return Duration(full_time1 - full_time2);
}


  Duration Duration::operator-(const Duration& other) const{

  int full_time1 = this->seconds_ + this->minutes_ * 60 + this->hours_ * 3600;
  int full_time2 = other.seconds_ + other.minutes_ * 60 + other.hours_ * 3600;
  if(full_time1<full_time2) throw std::out_of_range("Oduzimanje veceg broja od manjeg");

	return Duration(full_time1 - full_time2);
  }


  Duration Duration::operator-=(const Duration& other){
  if(*this < other) throw std::out_of_range("Oduzimanje veceg od manjeg");

  return *this = *this - other;
  }

  Duration Duration::operator*(int x){
  if (x < 0) throw std::out_of_range("Mnozenje negativnim brojem");
  int full_time = get_s() + get_m() * 60 + get_h() * 3600;
  return Duration(full_time * x);
}

  Duration Duration::operator*(int x) const{
  if (x < 0) throw std::out_of_range("Mnozenje negativnim brojem");

  return Duration(full_time_ * x);
}

  Duration& Duration::operator*=(int x) {
  if (x < 0) throw std::out_of_range("Mnozenje negativnim brojem");

	return *this = *this * x;
}



  Duration Duration::operator/(int x){
  if (x <= 0) throw std::out_of_range("Dijeljenje negativnim brojem");
  int full_time = get_s() + get_m() * 60 + get_h() * 3600;
  return Duration(full_time / x);

}

  Duration Duration::operator/(int x) const{

  if (x <= 0) throw std::out_of_range("Dijeljenje negativnim brojem");

  return Duration(full_time_ / x);
}


  Duration& Duration::operator/=(int x) {

  if (x <= 0) throw std::out_of_range("Dijeljenje negativnim brojem");

	return *this = *this / x;
}


Duration::Duration(const std::string& input)
{
  int i = 0;
  for (char c : input)
    if (c == ':') ++i;

  if (i != 2) throw std::invalid_argument("Pogresan unos");

  std::string hours, minutes, seconds;

  i = 0;
  while (input[i] != ':') hours += input[i++];
  ++i;
  while (input[i] != ':') minutes += input[i++];
  ++i;
  while (input[i] != '\0') seconds += input[i++];

  set_h(std::stoi(hours));
  set_m(std::stoi(minutes));
  set_s(std::stoi(seconds));
}




std::ostream& operator<<(std::ostream& output, const Duration& duration)
{
  if (duration.get_h() < 10) output << "0";
  output << duration.get_h() << ":";
  if (duration.get_m() < 10) output << "0";
  output << unsigned(duration.get_m()) << ":";
  if (duration.get_s() < 10) output << "0";
  output << unsigned(duration.get_s());

  return output;
}

std::istream& operator>>(std::istream& input, Duration& duration)
{
  std::string input_data;

  input >> input_data;
  duration = input_data;

  return input;
}
