// TODO: Add destructor!
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <SimpleMap.h>

class bitmap {
private:
  enum ORIENTATION { HORIZONTAL = 0, VERTICAL = 1 };
  SimpleMap<char, uint32_t> *charDict;

  void setupMap();
  bool* m_msg_v;
  bool* m_seq_v;
  int m_msg_len;
  int m_seq_len;
  int m_rows;
  int m_columns;
  ORIENTATION m_orientation;
  int m_msg_count;

  Adafruit_NeoPixel* m_strip;

  void do_something(bool on, uint32_t color);
public:
  bitmap(int length, int width, Adafruit_NeoPixel* strip);
  ~bitmap();
  void print_char(char c);
  bool generate_msg_v(char* msg);
  bool generate_sequence_v(int iterations, int x, int y);
  void show_sequence(long interval_ms, uint32_t color);
  // can't think of good name, like the OG but lights up by column during interval
  void show_sequence_v2(long interval_ms, uint32_t color);
};
