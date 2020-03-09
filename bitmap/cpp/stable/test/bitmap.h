// TODO: Add destructor!
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <SimpleMap.h>
#include "includes.h"

class bitmap {
private:
  SimpleMap<char, uint32_t> *charDict;

  void setupMap();
  bool* m_msg_v;
  bool* m_seq_v;
  int m_msg_len;
  int m_seq_len;
  int m_row_len;
  int m_rows;
  int m_width_char;
  int m_height_char;
  int m_columns;
  int m_msg_count;

  Adafruit_NeoPixel* m_strip;

  void do_something(const bool on, const uint32_t color);
public:
  bitmap(const int &num_rows, const int &num_cols, Adafruit_NeoPixel* strip);
  ~bitmap();
  #if defined(DEBUG)
  void print_scroll();
  #endif
  bool generate_msg_v(const char* const &msg);
  bool* get_sequence_v(const int &r, const int &c);
  bool generate_sequence_v(const int &r, const int &c);
  void show_location(const int &r, const int &c, const long &interval_ms, const uint32_t &color);
  void show_sequence_delay(const long &interval_ms, const uint32_t &color);
  void show_sequence_nodelay(const long &interval_ms, const uint32_t &color);
};
