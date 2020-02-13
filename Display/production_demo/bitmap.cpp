#include "bitmap.h"
//#include <HashMap.h>
//#include <SimpleMap.h>
#include "charDicts.h"

bool bitmap::generate_msg_v(char* msg) {
	int msg_len;
	for (int i = 0; msg[i] != '\0'; ++i) {
		++msg_len;
	}
	m_msg_len = msg_len*(m_rows+1)*m_columns;

	Serial.println(msg_len);

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

bool bitmap::generate_sequence_v(int iterations, int r, int c) {
	int len = m_msg_len / m_columns;
	m_seq_len = len + iterations;
	char* output = new char[m_seq_len+1];

	if (m_orientation) { // vertical
		bool* parr = new bool[m_seq_len];

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
		*(output + index) = '\0';

		Serial.println(output);

		m_seq_v = parr;
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

void bitmap::show_sequence(long interval_ms, uint32_t color) {
	int i = 0;
	for (int i = 0; i < m_seq_len; ++i) {
		do_something(*(m_seq_v + i), color);
		delay(interval_ms);
	}
}

void bitmap::show_sequence_v2(long interval_ms, uint32_t color) {
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

bitmap::bitmap(int length, int width, Adafruit_NeoPixel* strip) {
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
		m_orientation = VERTICAL;
    charDict = create_charMap35();
  } else if (m_columns == 5 & m_rows == 5) {
    m_orientation = VERTICAL;
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
