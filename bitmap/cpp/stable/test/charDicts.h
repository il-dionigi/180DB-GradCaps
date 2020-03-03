SimpleMap<char, uint32_t> * create_charMap35() {

  SimpleMap<char, uint32_t> *charMap35 =
    new SimpleMap<char, uint32_t>([](char &a, char &b) -> int {
        if (a == b) return 0;      // a and b are equal
        else if (a > b) return 1;  // a is bigger than b
        else return -1;            // a is smaller than b
      });

  charMap35->put('A', 0b101101111101010);
	charMap35->put('B', 0b011101011101011);
	charMap35->put('C', 0b111001001001111);
	charMap35->put('D', 0b011101101101011);
	charMap35->put('E', 0b111001111001111);
	charMap35->put('F', 0b001001111001111);
	charMap35->put('G', 0b111101111001111);
	charMap35->put('H', 0b101101111101101);
	charMap35->put('I', 0b111010010010111);
	charMap35->put('J', 0b011010010010111);
	charMap35->put('K', 0b101011001011101);
	charMap35->put('L', 0b111001001001001);
	charMap35->put('M', 0b101101101111101);
	charMap35->put('N', 0b101101111101101);
	charMap35->put('O', 0b111101101101111);
	charMap35->put('P', 0b001001111101111);
	charMap35->put('Q', 0b100111101101111);
	charMap35->put('R', 0b101011111101111);
	charMap35->put('S', 0b111100111001111);
	charMap35->put('T', 0b010010010010111);
	charMap35->put('U', 0b111101101101101);
	charMap35->put('V', 0b010101101101101);
	charMap35->put('W', 0b101111101101101);
	charMap35->put('X', 0b101101010101101);
	charMap35->put('Y', 0b010010010101101);
	charMap35->put('Z', 0b111001010100111);
	charMap35->put('0', 0b111101101101111);
	charMap35->put('1', 0b111010010011010);
	charMap35->put('2', 0b111001010100111);
	charMap35->put('3', 0b111100111100111);
	charMap35->put('4', 0b100100111101101);
	charMap35->put('5', 0b111100111001111);
	charMap35->put('6', 0b111101111001111);
	charMap35->put('7', 0b001001010100111);
	charMap35->put('8', 0b111101111101111);
	charMap35->put('9', 0b100100111101111);
	charMap35->put(' ', 0b000000000000000);
	charMap35->put('\'', 0b000000000010100);
	charMap35->put('\"', 0b000000000011110);
	charMap35->put('!', 0b111000111111111); // fat!
	charMap35->put('?', 0b001001111100111);
	charMap35->put(',', 0b001010010000000);
	charMap35->put('.', 0b010000000000000);
	charMap35->put('#', 0b111101000000101); // smiley

  return charMap35;
}

SimpleMap<char, uint32_t> * create_charMap45() {

  SimpleMap<char, uint32_t> *charMap45 =
    new SimpleMap<char, uint32_t>([](char &a, char &b) -> int {
        if (a == b) return 0;      // a and b are equal
        else if (a > b) return 1;  // a is bigger than b
        else return -1;            // a is smaller than b
      });

	charMap45->put('A', 0b10011001111110010110);
	charMap45->put('B', 0b01111001011110010111);
	charMap45->put('C', 0b11110001000100011111);
	charMap45->put('D', 0b01111001100110010111);
	charMap45->put('E', 0b11110001011100011111);
	charMap45->put('F', 0b00010001111100011111);
	charMap45->put('G', 0b11111001110100011111);
	charMap45->put('H', 0b10011001111110011001);
	charMap45->put('I', 0b11110110011001101111);
	charMap45->put('J', 0b01110100010001001111);
	charMap45->put('K', 0b10010101001101011001);
	charMap45->put('L', 0b11110001000100010001);
	charMap45->put('M', 0b10011001100111111001);
	charMap45->put('N', 0b10011101100110111001);
	charMap45->put('O', 0b11111001100110011111);
	charMap45->put('P', 0b00010001111110011111);
	charMap45->put('Q', 0b01001111110110011111);
	charMap45->put('R', 0b10010101111110011111);
	charMap45->put('S', 0b11111000111100011111);
	charMap45->put('T', 0b01100110011001101111);
	charMap45->put('U', 0b11111001100110011001);
	charMap45->put('V', 0b01101001100110011001);
	charMap45->put('W', 0b10011111100110011001);
	charMap45->put('X', 0b10011001011010011001);
	charMap45->put('Y', 0b01100110011010011001);
	charMap45->put('Z', 0b11110001001001001111);
	charMap45->put('0', 0b11111001100110011111);
	charMap45->put('1', 0b11110100010001100100);
	charMap45->put('2', 0b11110010010010001111);
	charMap45->put('3', 0b11111000111110001111);
	charMap45->put('4', 0b10001000111110011001);
	charMap45->put('5', 0b01111000011100011111);
	charMap45->put('6', 0b11111001111100011111);
	charMap45->put('7', 0b00010010010010001111);
	charMap45->put('8', 0b11111001111110011111);
	charMap45->put('9', 0b10001000111110011111);
	charMap45->put(' ', 0b00000000000000000000);
	charMap45->put('\'', 0b00000000001001000100);
	charMap45->put('\"', 0b00000000010110101010);
	charMap45->put('!', 0b01100000011001100110);
	charMap45->put('?', 0b00100010111010001111);
	charMap45->put(',', 0b00100100010000000000);
	charMap45->put('.', 0b01100110000000000000);
	charMap45->put('#', 0b01101001000000001001); //smiley

  return charMap45;
}

SimpleMap<char, uint32_t> * create_charMap55() {

  SimpleMap<char, uint32_t> *charMap55 =
    new SimpleMap<char, uint32_t>([](char &a, char &b) -> int {
        if (a == b) return 0;      // a and b are equal
        else if (a > b) return 1;  // a is bigger than b
        else return -1;            // a is smaller than b
      });

	charMap55->put('A', 0b1000110001111111000101110);
	charMap55->put('B', 0b0111110001011111000101111);
	charMap55->put('C', 0b1111100001000010000111111);
	charMap55->put('D', 0b0111110001100011000101111);
	charMap55->put('E', 0b1111100001011110000111111);
	charMap55->put('F', 0b0000100001011110000111111);
	charMap55->put('G', 0b1111110001111010000111111);
	charMap55->put('H', 0b1000110001111111000110001);
	charMap55->put('I', 0b1111100100001000010011111);
	charMap55->put('J', 0b0111001010010000100011111);
	charMap55->put('K', 0b0100100101000110010101001);
	charMap55->put('L', 0b1111100001000010000100001);
	charMap55->put('M', 0b1000110001101011101110001);
	charMap55->put('N', 0b1000111001101011001110001);
	charMap55->put('O', 0b1111110001100011000111111);
	charMap55->put('P', 0b0000100001111111000111111);
	charMap55->put('Q', 0b0100011111101011000111111);
	charMap55->put('R', 0b0100100101111111000111111);
	charMap55->put('S', 0b1111110000111110000111111);
	charMap55->put('T', 0b0010000100001000010011111);
	charMap55->put('U', 0b1111110001100011000110001);
	charMap55->put('V', 0b0010001010100011000110001);
	charMap55->put('W', 0b1111110101101011000110001);
	charMap55->put('X', 0b1000101010001000101010001);
	charMap55->put('Y', 0b0010000100011101000110001);
	charMap55->put('Z', 0b1111100010001000100011111);
	charMap55->put('0', 0b1111110001100011000111111);
	charMap55->put('1', 0b1111100100001000011000100);
	charMap55->put('2', 0b1111100110010001000011111);
	charMap55->put('3', 0b0111110000011111000001111);
	charMap55->put('4', 0b0100001000111110100101001);
	charMap55->put('5', 0b0111110000011110000111111);
	charMap55->put('6', 0b1111110001111110000111111);
	charMap55->put('7', 0b0000100010001000100011111);
	charMap55->put('8', 0b0111010001011101000101110);
	charMap55->put('9', 0b1000010000111111000111111);
	charMap55->put(' ', 0b0000000000000000000000000);
	charMap55->put('\'', 0b0000000000000100010000100);
	charMap55->put('\"', 0b0000000000010011001010010);
	charMap55->put('!', 0b0111000000011100111001110);
	charMap55->put('?', 0b0010000100010001000101110);
	charMap55->put(',', 0b0011001000011000110000000);
	charMap55->put('.', 0b0011100111001110000000000);
	charMap55->put('~', 0b0010001010100011010101010); //heart
	charMap55->put('#', 0b0111010001001000000001010);//smiley

  return charMap55;
}

SimpleMap<char, uint32_t> * create_charMap65() {

  SimpleMap<char, uint32_t> *charMap65 =
    new SimpleMap<char, uint32_t>([](char &a, char &b) -> int {
        if (a == b) return 0;      // a and b are equal
        else if (a > b) return 1;  // a is bigger than b
        else return -1;            // a is smaller than b
      });

	charMap65->put('A', 0b100001100001111111100001011110);
	charMap65->put('B', 0b011111100001011111100001011111);
	charMap65->put('C', 0b111110000001000001000001111110);
	charMap65->put('D', 0b011111100001100001100001011111);
	charMap65->put('E', 0b111111000001011111000001111111);
	charMap65->put('F', 0b000001000001011111000001111111);
	charMap65->put('G', 0b111111100001111001000001111111);
	charMap65->put('H', 0b100001100001111111100001100001);
	charMap65->put('I', 0b111111001100001100001100111111);
	charMap65->put('J', 0b001111001001001000001000111111);
	charMap65->put('K', 0b110001001001000111001001110001);
	charMap65->put('L', 0b111111000001000001000001000001);
	charMap65->put('M', 0b100001100001101101110011100001);
	charMap65->put('N', 0b100001110001101001100101100011);
	charMap65->put('O', 0b011110100001100001100001011110);
	charMap65->put('P', 0b000001000001111111100001111111);
	charMap65->put('Q', 0b001000111111101001100001111111);
	charMap65->put('R', 0b011001000101011111100001011111);
	charMap65->put('S', 0b011110100000011110000001111110);
	charMap65->put('T', 0b001100001100001100001100111111);
	charMap65->put('U', 0b011110100001100001100001100001);
	charMap65->put('V', 0b001100010010100001100001100001);
	charMap65->put('W', 0b010010101101100001100001100001);
	charMap65->put('X', 0b100001010010001100010010100001);
	charMap65->put('Y', 0b001100001100011110100001100001);
	charMap65->put('Z', 0b111111000110001100011000111111);
	charMap65->put('0', 0b011110100001100001100001011110);
	charMap65->put('1', 0b111111001000001000001010001100);
	charMap65->put('2', 0b111111000010011100100001111110);
	charMap65->put('3', 0b011111100000011110100000011111);
	charMap65->put('4', 0b010000010000111111010001010001);
	charMap65->put('5', 0b011111100000011111000001111111);
	charMap65->put('6', 0b111111100001111111000001111111);
	charMap65->put('7', 0b000010000100001000010000111111);
	charMap65->put('8', 0b011110100001011110100001011110);
	charMap65->put('9', 0b100000100000111111100001111111);
	charMap65->put(' ', 0b000000000000000000000000000000);
	charMap65->put('\'', 0b000000000000000010000100000100);
	charMap65->put('\"', 0b000000000000010010100100100100);
	charMap65->put('!', 0b001100000000001100001100001100);
	charMap65->put('?', 0b000100000100111100100001111111);
	charMap65->put(',', 0b000010000100001000001100001100);
	charMap65->put('.', 0b000000001110001110001110000000);
	charMap65->put('~', 0b001100010010100001101101110011); //heart
	charMap65->put('#', 0b011110100001001100000000110011); //smiley

  return charMap65;
}

SimpleMap<char, uint32_t> * create_charMap56() {

  SimpleMap<char, uint32_t> *charMap56 =
    new SimpleMap<char, uint32_t>([](char &a, char &b) -> int {
        if (a == b) return 0;      // a and b are equal
        else if (a > b) return 1;  // a is bigger than b
        else return -1;            // a is smaller than b
      });

	charMap56->put('A', 0b100011000110001111111000101110);
	charMap56->put('B', 0b011111000110001011111000101111);
	charMap56->put('C', 0b111110000100001000010000111110);
	charMap56->put('D', 0b011111000110001100011000101111);
	charMap56->put('E', 0b111110000100001011110000111111);
	charMap56->put('F', 0b000010000100001011110000111111);
	charMap56->put('G', 0b111111000111101000010000111111);
	charMap56->put('H', 0b100011000110001111111000110001);
	charMap56->put('I', 0b111110010000100001000010011111);
	charMap56->put('J', 0b011100101001010010000100011111);
	charMap56->put('K', 0b100010100100111001110100110001);
	charMap56->put('L', 0b111110000100001000010000100001);
	charMap56->put('M', 0b100011000110001101011101110001);
	charMap56->put('N', 0b100011100110101101011001110001);
	charMap56->put('O', 0b111111000110001100011000111111);
	charMap56->put('P', 0b000010000100001111111000111111);
	charMap56->put('Q', 0b010001111110101100011000111111);
	charMap56->put('R', 0b100010100100101111111000111111);
	charMap56->put('S', 0b111111000010000111110000111111);
	charMap56->put('T', 0b001000010000100001000010011111);
	charMap56->put('U', 0b111111000110001100011000110001);
	charMap56->put('V', 0b001000101010001100011000110001);
	charMap56->put('W', 0b100011101110101100011000110001);
	charMap56->put('X', 0b100011000101010001000101010001);
	charMap56->put('Y', 0b001000010000100001000101010001);
	charMap56->put('Z', 0b111110000100010001000100011111);
	charMap56->put('0', 0b111111000110001100011000111111);
	charMap56->put('1', 0b111110010000100001000010100110);
	charMap56->put('2', 0b111110001000100010001000101110);
	charMap56->put('3', 0b011111000010000011111000001111);
	charMap56->put('4', 0b010000100001000111110100101001);
	charMap56->put('5', 0b011111000010000011110000111111);
	charMap56->put('6', 0b111111000111111000010000111110);
	charMap56->put('7', 0b000010001000100010001000011111);
	charMap56->put('8', 0b011101000110001011101000101110);
	charMap56->put('9', 0b100001000010000111111000111111);
	charMap56->put(' ', 0b000000000000000000000000000000);
	charMap56->put('\'', 0b000000000000000000100010000100);
	charMap56->put('\"', 0b000000000000000010011001010010);
	charMap56->put('!', 0b011100000001110011100111001110);
	charMap56->put('?', 0b001000010000100011001000101110);
	charMap56->put(',', 0b000100010000110001100000000000);
	charMap56->put('.', 0b011100111001110000000000000000);
	charMap56->put('~', 0b001000101010001100011010101010);
	charMap56->put('#', 0b011101000110001001000000001010);

  return charMap56;
}