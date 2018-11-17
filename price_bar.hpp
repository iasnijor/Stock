#ifndef __CDS_PRICE_BAR_H
#define __CDS_PRICE_BAR_H
#include <string>

namespace csis3700 {
  class price_bar {
  public:
    price_bar(std::string date_time, double open, double high,
	      double low, double close, double adjusted_close, double volume) {
      this->date_time = date_time;
      this->open = open;
      this->high = high;
      this->low = low;
      this->close = close;
      this->adjusted_close = adjusted_close;
      this->volume = volume;
    }
    
    std::string get_date_time() const { return date_time; }
    
    double get_open() const { return open; }
    
    double get_high() const { return high; }
    
    double get_low() const { return low; }

    double get_close() const { return close; }

    double get_adjusted_close() const { return adjusted_close; } 

  private:
    std::string date_time;
    double open;
    double high;
    double low;
    double close;
    double adjusted_close;
    double volume;
  };
}


#endif
