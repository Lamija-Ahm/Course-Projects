#pragma once

#include<istream>
#include<ostream>
#include<string>


class Duration {

  public:

   Duration() : hours_(0), minutes_(0), seconds_(0) { }
   Duration(int secs);
   Duration(int hours, int minutes, int seconds);


   int get_s() const { return seconds_; }
   int get_m() const { return minutes_; }
   int get_h() const { return hours_; }
   Duration& set_s(int seconds);
   Duration& set_m(int minutes);
   Duration& set_h(int hours);

   bool operator==(const Duration& other) const;
   bool operator!=(const Duration& other) const;
   bool operator>=(const Duration& other) const;
   bool operator<=(const Duration& other) const;
   bool operator>(const Duration& other) const;
   bool operator<(const Duration& other) const;

	 explicit operator bool() const { return hours_ && minutes_ && seconds_; }
   bool operator!() const { return !(hours_ && minutes_ && seconds_); }

   Duration operator+(const Duration& other);
   Duration operator+(const Duration& other) const;
   Duration operator+=(const Duration& other);

   Duration operator-(const Duration& other);
   Duration operator-(const Duration& other) const;
   Duration operator-=(const Duration& other);

   Duration operator*(int x);
   Duration operator/(int x);
   Duration operator*(int x) const;
   Duration operator/(int x) const;
   Duration& operator*=(int x);
   Duration& operator/=(int x);

   Duration(const std::string& input);

  private:
    int hours_ = 0;
    int minutes_ =0;
    int seconds_ = 0;
    int full_time_ = seconds_ + minutes_ * 60 + hours_ * 3600;
};
