#include "bitmap.h"
//#include <HashMap.h>
//#include <SimpleMap.h>
#include "charDicts.h"

bool bitmap::generate_msg_v(char* msg) {
  if (m_orientation) { // vertical
    int msg_len;
    for (int i = 0; msg[i] != '\0'; ++i) {
      ++msg_len;
    }
    m_msg_len = msg_len*(m_rows+1)*m_columns;
    
    Serial.println(m_msg_len);

    bool* parr = new bool[m_msg_len]; // based on charDict35, each char takes 6
    char* bitmsg = new char[msg_len*(m_rows+1)*(m_columns+1)+1]; // based on charDict35, each char takes 6
    int index = 0, m_index = 0;
    
    if (parr == nullptr) {
      Serial.print("Error allocating msg vector.\n"); // add perror
      return false;
    } else {
      int r, c;
      for (int i = 0; i < msg_len; i++) {
        long encodedChar = charDict->get(msg[i]);
        for (r = 0; r < m_rows; ++r) {
          for (c = 0; c < m_columns; ++c) {
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
        for (c = 0; c < m_columns; ++c) {
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
    
    free(bitmsg);
  } else { // horizontal
    int msg_len;
    for (int i = 0; msg[i] != '\0'; ++i) {
      ++msg_len;
    }
    m_msg_len = msg_len*(m_rows+1)*(m_columns+1);
    m_row_len = msg_len*(m_columns + 1);

    Serial.println(m_msg_len);

    bool* parr = new bool[m_msg_len+1];
    char* bitmsg = new char[m_msg_len+1];
    bitmsg[m_msg_len] = '\0';
    int index = 0, m_index = 0;
    
    if (parr == nullptr) {
      Serial.print("Error allocating msg vector.\n"); // add perror
      return false;
    } else {
      int r, c;
      for (r = 0; r < m_rows; ++r) {
        for (int i = 0; i < msg_len; i++) {
          long encodedChar = charDict->get(msg[i])>>(r*m_columns);
          for (c = 0; c < m_columns; ++c) {
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
          *(parr + index) = 0;
          *(bitmsg + m_index) = ' ';
          ++index;
          ++m_index;
        }
        // newline after each line
        *(parr + index) = 0;
        *(bitmsg + m_index) = '\n';
        ++index;
        ++m_index;
      }
    }
    
    m_msg_v = parr;
    
    Serial.println(bitmsg);
    
    free(bitmsg);
  }



	return true;
}

void bitmap::print_char(char c) {
	char* bitChar = new char[m_rows*m_columns+m_rows+1];
	uint32_t encodedChar = charDict->get(c);
	int index = 0;
	for (int c = 0; c < m_rows; ++c) {
		for (int r = 0; r < m_columns; ++r) {
			if (encodedChar&0b1 == 1) {
				*(bitChar + index) = '#';
			} else {
				*(bitChar + index) = ' ';
			}
			++index;
			encodedChar = encodedChar>>1;
		}
		*(bitChar + index) = '\n';
		++index;
	}
	*(bitChar + index) = '\0';
	Serial.println(bitChar);
	free(bitChar);
	return;
}

void bitmap::print_scroll() {
  if (m_orientation == VERTICAL) {
    bool*** output = new bool**[m_columns];
    for (int r = 0; r < m_rows; ++r) {
      output[r] = new bool*[m_rows];
      for (int c = 0; c < m_columns; c++) {
        output[r][c] = get_sequence_v(5, r, c);
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
    delete display;
    
    for (int r = 0; r < m_rows; ++r) {
      for (int c = 0; c < m_columns; c++) {
        delete[] output[r][c];
      }
    }
  } else {
    bool*** output = new bool**[m_columns];
    for (int r = 0; r < m_rows; ++r) {
      output[r] = new bool*[m_rows];
      for (int c = 0; c < m_columns; c++) {
        output[r][c] = get_sequence_v(5, r, c);
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
  }
  /*
  free(display);
  for (int r = 0; r < m_rows; ++r) {
    free(output[r]);
  }
  free(output);
  */
}

bool* bitmap::get_sequence_v(int iterations, int r, int c) {
	if (m_orientation) { // vertical
    int len = m_msg_len / m_columns;
    Serial.println(len);
    m_seq_len = len + iterations;
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
	} else { // horizontal
    int len = m_msg_len / (m_rows+1);
    m_seq_len = len + iterations;
    char* output = new char[m_seq_len+1];

		bool* parr = new bool[m_seq_len];

		int index = 0;
		for (int i = m_columns - c; i > 0; --i) {
			*(parr + index) = 0;
			*(output + index) = '0';
			++index;
		}

    int v_index = r*(m_row_len+1);
    Serial.println(v_index);
		while (index < m_row_len+iterations) {
			*(parr + index) = *(m_msg_v + v_index);
			++v_index;
			if (*(parr + index)) {
				*(output + index) = '1';
			} else {
				*(output + index) = '0';
			}

			++index;
		}

    for (int i = m_seq_len - c; i < m_seq_len; ++i) {
      *(parr + i) = 0;
    }

    *(output + index) = '\0';

		Serial.println(output);
    free(output);

    return parr;
  }
}

void bitmap::do_something(bool on, uint32_t color) {
	if (on) {
		m_strip->fill(color);
		Serial.println("On!");
	} else {
		m_strip->fill(0);
		Serial.println("Off!");
	}
	m_strip->show();
}

bool bitmap::generate_sequence_v(int iterations, int r, int c) {
  if (m_msg_v != nullptr) {
    m_seq_v = get_sequence_v(iterations, r, c);
    return true;
  }
  return false;
}

void bitmap::show_sequence_delay(long interval_ms, uint32_t color) {
	int i = 0;
	for (int i = 0; i < m_seq_len; ++i) {
		do_something(*(m_seq_v + i), color);
		delay(interval_ms);
	}
}

void bitmap::show_sequence_nodelay(long interval_ms, uint32_t color) {
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

void bitmap::show_sequence_scroll_delay(long interval_ms, uint32_t color) {
	int i = 0;
  bool previouslyOn = false;
	for (int i = 0; i < m_seq_len; ++i) {
		if (*(m_seq_v + i)) {
      if (!previouslyOn) {
        delay(interval_ms/4);
        m_strip->setPixelColor(0, color);
        m_strip->setPixelColor(1, color);
        m_strip->setPixelColor(2, color);
        m_strip->setPixelColor(3, color);
        m_strip->show();
        delay(interval_ms/4);
        m_strip->setPixelColor(4, color);
        m_strip->setPixelColor(11, color);
        m_strip->show();
        delay(interval_ms/4);
        m_strip->setPixelColor(5, color);
        m_strip->setPixelColor(10, color);
        m_strip->show();
        delay(interval_ms/4);
        m_strip->setPixelColor(6, color);
        m_strip->setPixelColor(7, color);
        m_strip->setPixelColor(8, color);
        m_strip->setPixelColor(9, color);
        m_strip->show();
      } else {
        m_strip->fill(color);
        m_strip->show();
      }
      previouslyOn = true;
		} else {
			m_strip->clear();
      m_strip->show();
      previouslyOn = false;
		}
		delay(interval_ms);
	}
  m_strip->clear();
  m_strip->show();
}
void bitmap::set_orientation(ORIENTATION orientation){
  m_orientation = orientation;
}
void bitmap::show_sequence_scroll_nodelay(long interval_ms, uint32_t color) {
  /*
	int i = 0;
  bool previouslyOn = false;

  unsigned long scroll_ms = current_ms;

  for (int i = 0; i < m_seq_len; ++i) {
  //  if (current_ms - previous_ms >= interval_ms)
    if (!(*(m_seq_v + i)) && (i+1 < m_seq_len) && (*(m_seq_v + i + 1))) {
      unsigned long current_ms = millis();
      unsigned long previous_ms = current_ms;
      
      int scroll = 0;
      while (scroll < 4) {
        current_ms = millis();
        if (current_ms - previous_ms >= interval_ms / 4) {
          previous_ms = current_ms;
          ++scroll;
          if (scroll == 1) {
            m_strip->setPixelColor(0, color);
            m_strip->setPixelColor(1, color);
            m_strip->setPixelColor(2, color);
            m_strip->setPixelColor(3, color);
            m_strip->show();
          } else if (scroll == 2) {
            m_strip->setPixelColor(4, color);
            m_strip->setPixelColor(11, color);
            m_strip->show();
          } else if (scroll == 3) {
            m_strip->setPixelColor(5, color);
            m_strip->setPixelColor(10, color);
            m_strip->show();
          } else if (scroll == 4) {
            m_strip->setPixelColor(6, color);
            m_strip->setPixelColor(7, color);
            m_strip->setPixelColor(8, color);
            m_strip->setPixelColor(9, color);
            m_strip->show();
          }
        }
      }
    } else if (*(m_seq_v + i)){
			m_strip->clear();
      m_strip->show();
      previouslyOn = false;
		}
		delay(interval_ms);
  } else {
    
  }
  m_strip->clear();
  m_strip->show(); */
}

bitmap::bitmap(int length, int width, Adafruit_NeoPixel* strip, ORIENTATION orientation) {
  m_orientation = orientation;

  m_msg_v = nullptr;
	m_seq_v = nullptr;

	m_strip = strip;

	if (length < width) {
		m_columns = length;
		m_rows = width;
	} else {
		m_columns = width;
		m_rows = length;
	}

	if (m_columns == 3 & m_rows == 5) {
    charDict = create_charMap35();
  } else if (m_columns == 4 & m_rows == 5) {
    charDict = create_charMap45();
  } else if (m_columns == 5 & m_rows == 5) {
    charDict = create_charMap55();
  }
}

bitmap::~bitmap() {
  if (m_msg_v != nullptr) {
    free (m_msg_v);
  }

  if (m_seq_v != nullptr) {
    free (m_seq_v);
  }
}
