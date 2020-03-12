#include "bitmap.h"
//#include <HashMap.h>
//#include <SimpleMap.h>
#include "charDicts.h"

bool bitmap::generate_msg_v(char* const &msg) {

  // count length of input msg
  int msg_len;
  for (int i = 0; msg[i] != '\0'; ++i) {
      // lowercase to uppercase
      if(msg[i]>='a' && msg[i]<='z') {
         msg[i] -= 32;
      }
    ++msg_len;
  }
  // +1 is added to account for spaces
  m_msg_len = msg_len*(m_height_char+1)*m_width_char;

  #if defined(DEBUG)
  Serial.println(m_msg_len);
  #endif
  
  bool* parr = new bool[m_msg_len]; // based on charDict35, each char takes 6
  int index = 0;

  #if defined(DEBUG)
  char* bitmsg = new char[msg_len*(m_rows+1)*(m_columns+1)+1]; // based on charDict35, each char takes 6
  int m_index = 0;
  #endif

  if (parr == nullptr) {
    #if defined(DEBUG)
    Serial.print("Error allocating msg vector.\n"); // add perror
    #endif
    return false;
  } else {
    int h, w;
    // construct message row by row
    for (h = 0; h < m_height_char; ++h) {
      for (int i = 0; i < msg_len; i++) {
        long encodedChar = charDict->get(msg[i])>>(h*m_width_char);
        for (w = 0; w < m_width_char; ++w) {
          if (encodedChar&0b1 == 1) {
            *(parr + index) = 1;
            #if defined(DEBUG)
            *(bitmsg + m_index) = '#';
            #endif
          } else {
            *(parr + index) = 0;
            #if defined(DEBUG)
            *(bitmsg + m_index) = ' ';
            #endif
          }
          encodedChar = encodedChar>>1;
          ++index;
          #if defined(DEBUG)
          ++m_index;
          #endif
        }
        // space betwee letters
        *(parr + index) = 0;
        ++index;
        #if defined(DEBUG)
        *(bitmsg + m_index) = ' ';
        ++m_index;
        #endif
      }
      // space/newline after each line
      *(parr + index) = 0;
      ++index;
      #if defined(DEBUG)
      *(bitmsg + m_index) = '\n';
      ++m_index;
      #endif
    }
    #if defined(DEBUG)
    // nullchar for string
    *(bitmsg + m_index) = '\0';
    #endif
  }

  m_msg_v = parr;
  #if defined(DEBUG)
  Serial.println(bitmsg);
  free(bitmsg);
  #endif

	return true;
}

#if defined(DEBUG)
void bitmap::print_scroll() {
  // get sequence for each m_rows, m_columns combination
  bool*** output = new bool**[m_rows];
  for (int r = 0; r < m_rows; ++r) {
    output[r] = new bool*[m_columns];
    for (int c = 0; c < m_columns; c++) {
      output[r][c] = get_sequence_v(r, c);
    }
  }

  char* display = new char[(m_columns+1)*(m_rows+1)];

  // show iteration for each sequence
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

  // delete variables
  delete[] display;
  for (int r = 0; r < m_rows; ++r) {
    for (int c = 0; c < m_columns; ++c) {
            delete[] output[r][c];
    }
        delete[] output[r];
  }
    delete[] output;  
}
#endif

bool* bitmap::get_sequence_v(const int &r, const int &c) {
  int len = m_msg_len / m_rows;
  m_seq_len = len + m_columns;
  bool* parr = new bool[m_seq_len+1];
  #if defined(DEBUG)
  char* output = new char[m_seq_len+1];
  #endif

  // time needed for sequence to reach column
  int index = 0;
  for (int i = m_columns - c; i > 0; --i) {
    #if defined(DEBUG)
    *(output + index) = '0';
    #endif
    *(parr + index) = 0;
    ++index;
  }

  // sequence starts at beginning of row
  int v_index = (len+1)*r;
  while (index < m_seq_len) {
    *(parr + index) = *(m_msg_v + v_index);
    ++v_index;
    #if defined(DEBUG)
    if (*(parr + index)) {
      *(output + index) = '1';
    } else {
      *(output + index) = '0';
    }
    #endif
    ++index;
  }

  // time needed for sequence to finish
  for (int i = m_seq_len - c; i < m_seq_len; ++i) {
    *(parr + i) = 0;
  }
  #if defined(DEBUG)
  *(output + index) = '\0';
  Serial.println(output);
  free(output);
  #endif

  return parr;
}

void bitmap::do_something(const bool on, const uint32_t color) {
	if (on) {
		m_strip->fill(color);
   #if defined(DEBUG)
		Serial.println("On!");
    #endif
	} else {
		m_strip->fill(0);
   #if defined(DEBUG)
		Serial.println("Off!");
   #endif
	}
	m_strip->show();
}

bool bitmap::generate_sequence_v(const int &r, const int &c) {
  if (m_msg_v != nullptr) {
    m_seq_v = get_sequence_v(r, c);
    return true;
  }
  return false;
}

void bitmap::show_sequence_delay(const long &interval_ms, const uint32_t &color) {
	int i = 0;
	for (int i = 0; i < m_seq_len; ++i) {
		do_something(*(m_seq_v + i), color);
		delay(interval_ms);
	}
}

void bitmap::show_sequence_nodelay(const long &interval_ms, const uint32_t &color) {
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

void bitmap::show_location(const int &r, const int &c, const long &interval_ms, const uint32_t &color) {
  m_strip->clear();
  m_strip->show();

  delay(interval_ms*(r*m_columns+c));

  m_strip->fill(color);
  m_strip->show();

  delay(interval_ms);

  m_strip->clear();
  m_strip->show();
}

bitmap::bitmap(const int &num_rows, const int &num_cols, Adafruit_NeoPixel* strip) {
  m_msg_v = nullptr;
	m_seq_v = nullptr;

	m_strip = strip;

	if (num_rows > num_cols) {
		m_columns = num_rows;
		m_rows = num_cols;
	} else {
		m_columns = num_cols;
		m_rows = num_rows;
	}

	if (m_rows == 3) {
    m_width_char = 5;
    m_height_char = 3;
    charDict = create_charMap35();
  } else if (m_rows == 4) {
    m_width_char = 5;
    m_height_char = 4;
    charDict = create_charMap45();
  } else if (m_rows == 5) {
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
