#include "bitmap.h"
//#include <HashMap.h>
//#include <SimpleMap.h>
#include "charDicts.h"

bool bitmap::generate_msg_v(const char* const &msg) {
  int msg_len;
  for (int i = 0; msg[i] != '\0'; ++i) {
    ++msg_len;
  }
  m_msg_len = msg_len*(m_height_char+1)*m_width_char;

  Serial.println(m_msg_len);

  bool* parr = new bool[m_msg_len]; // based on charDict35, each char takes 6
  char* bitmsg = new char[msg_len*(m_rows+1)*(m_columns+1)+1]; // based on charDict35, each char takes 6
  int index = 0, m_index = 0;

  if (parr == nullptr) {
    Serial.print("Error allocating msg vector.\n"); // add perror
    return false;
  } else {
    int h, w;
    for (int i = 0; i < msg_len; i++) {
      long encodedChar = charDict->get(msg[i]);
      for (h = 0; h < m_height_char; ++h) {
        for (w = 0; w < m_width_char; ++w) {
          if (encodedChar&0b1 == 1) {
            *(parr + index) = 1;
            *(bitmsg + m_index) = '#';
          } else {
            *(parr + index) = 0;
            *(bitmsg + m_index) = ' ';
          }
          encodedChar = encodedChar>>1;
          ++index;
          ++m_index;
        }
        *(bitmsg + m_index) = '\n';
        ++m_index;
      }
      // space after each line
      for (w = 0; w < m_width_char; ++w) {
        *(parr + index) = 0;
        ++index;

        *(bitmsg + m_index) = ' ';
        ++m_index;
      }

      *(bitmsg + m_index) = '\n';
      ++m_index;
    }

    *(bitmsg + m_index) = '\0';

  }

  m_msg_v = parr;

  Serial.println(bitmsg);
  Serial.println(m_seq_len);

  free(bitmsg);

	return true;
}

void bitmap::print_scroll() {
  bool*** output = new bool**[m_rows];
  for (int r = 0; r < m_rows; ++r) {
    output[r] = new bool*[m_columns];
    for (int c = 0; c < m_columns; c++) {
      output[r][c] = get_sequence_v(r, c);
    }
  }

  char* display = new char[(m_columns+1)*(m_rows+1)];

  for (int i = 0; i < m_seq_len; ++i) {
    int index = 0;
    for (int r = 0; r < m_rows; ++r) {
      for (int c = 0; c < m_columns; c++) {
        if (output[r][c][i] == 1) {
          display[index] = '#';
        }
        else {
          display[index] = ' ';
        }
        ++index;
      }
      display[index] = '\n';
      ++index;
    }
    display[index-1] = '\0';
    Serial.println(display);
    Serial.println("---------");
  }

  delete[] display;
  
  for (int r = 0; r < m_rows; ++r) {
    for (int c = 0; c < m_columns; ++c) {
            delete[] output[r][c];
    }
        delete[] output[r];
  }
    delete[] output;
  
}

bool* bitmap::get_sequence_v(const int r, const int c) {
  int len = m_msg_len / m_columns;
  m_seq_len = len + m_rows;
  Serial.println(m_seq_len+1);
  char* output = new char[m_seq_len+1];

  bool* parr = new bool[m_seq_len+1];

  int index = 0;
  for (int i = m_rows - r; i > 0; --i) {
    *(parr + index) = 0;
    *(output + index) = '0';
    ++index;
  }

  int v_index = c;
  while (index < m_seq_len) {
    *(parr + index) = *(m_msg_v + v_index);
    v_index += m_columns;
    if (*(parr + index)) {
      *(output + index) = '1';
    } else {
      *(output + index) = '0';
    }

    ++index;
  }

  for (int i = m_seq_len - r; i < m_seq_len; ++i) {
    *(parr + i) = 0;
  }

  *(output + index) = '\0';

  Serial.println(output);
  free(output);

  return parr;
}

void bitmap::do_something(const bool on, const uint32_t color) {
	if (on) {
		m_strip->fill(color);
		Serial.println("On!");
	} else {
		m_strip->fill(0);
		Serial.println("Off!");
	}
	m_strip->show();
}

bool bitmap::generate_sequence_v(const int r, const int c) {
  if (m_msg_v != nullptr) {
    m_seq_v = get_sequence_v(r, c);
    return true;
  }
  return false;
}

void bitmap::show_sequence_delay(const long interval_ms, const uint32_t color) {
	int i = 0;
	for (int i = 0; i < m_seq_len; ++i) {
		do_something(*(m_seq_v + i), color);
		delay(interval_ms);
	}
}

void bitmap::show_sequence_nodelay(const long interval_ms, const uint32_t color) {
  unsigned long current_ms = millis();
  unsigned long previous_ms = current_ms;

  int i = 0;
  current_ms = millis();
  if (current_ms - previous_ms >= interval_ms) {
    // save the last time you blinked the LED
    previous_ms = current_ms;
    do_something(*(m_seq_v + i), color);
    ++i;
    if (i == m_seq_len) {
      return;
    }
  }
}

bitmap::bitmap(const int num_rows, const int num_cols, Adafruit_NeoPixel* strip) {
  m_msg_v = nullptr;
	m_seq_v = nullptr;

	m_strip = strip;

	if (num_rows < num_cols) {
		m_columns = num_rows;
		m_rows = num_cols;
	} else {
		m_columns = num_cols;
		m_rows = num_rows;
	}

	if (m_columns == 3) {
    m_width_char = 3;
    m_height_char = 5;
    charDict = create_charMap35();
  } else if (m_columns == 4) {
    m_width_char = 4;
    m_height_char = 5;
    charDict = create_charMap45();
  } else if (m_columns == 5) {
    m_width_char = 5;
    m_height_char = 5;
    charDict = create_charMap55();
  }
}

bitmap::~bitmap() {
  if (m_msg_v != nullptr) {
    delete[] m_msg_v;
  }

  if (m_seq_v != nullptr) {
    delete[] m_seq_v;
  }
}
