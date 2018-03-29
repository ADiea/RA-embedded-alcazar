/*
 * max7219_font.h
 *
 * Modified from source: https://github.com/nickgammon/MAX7219/blob/master/MAX7219_font.h
 *
 */

#ifndef MAX7219_FONT_H
#define MAX7219_FONT_H


#define MAX7219_HYPHEN 0b0000001

const unsigned char MAX7219_font[91]= {
   0b0000000, // ' '
   MAX7219_HYPHEN, // '!'
   MAX7219_HYPHEN, // '"'
   MAX7219_HYPHEN, // '#'
   MAX7219_HYPHEN, // '$'
   MAX7219_HYPHEN, // '%'
   MAX7219_HYPHEN, // '&'
   MAX7219_HYPHEN, // '''
   0b1001110,       // '('   - same as [
   0b1111000,       // ')'   - same as ]
   MAX7219_HYPHEN, // '*'
   MAX7219_HYPHEN, // '+'
   MAX7219_HYPHEN, // ','
   MAX7219_HYPHEN, // '-'
   0b0000000,       // '.'  (done by turning DP on)
   MAX7219_HYPHEN, // '/'
   0b1111110,       // '0'
   0b0110000,       // '1'
   0b1101101,       // '2'
   0b1111001,       // '3'
   0b0110011,       // '4'
   0b1011011,       // '5'
   0b1011111,       // '6'
   0b1110000,       // '7'
   0b1111111,       // '8'
   0b1111011,       // '9'
   MAX7219_HYPHEN, // ':'
   MAX7219_HYPHEN, // ';'
   MAX7219_HYPHEN, // '<'
   0b0001001, // '='
   MAX7219_HYPHEN, // '>'
   MAX7219_HYPHEN, // '?'
   MAX7219_HYPHEN, // '@'
   0b1110111,       // 'A'
   0b0011111,       // 'B'
   0b1001110,       // 'C'
   0b0111101,       // 'D'
   0b1001111,       // 'E'
   0b1000111,       // 'F'
   0b1011110,       // 'G'
   0b0110111,       // 'H'
   0b0110000,       // 'I' - same as 1
   0b0111100,       // 'J'
   MAX7219_HYPHEN, // 'K'
   0b0001110,       // 'L'
   MAX7219_HYPHEN, // 'M'
   0b0010101,       // 'N'
   0b1111110,       // 'O' - same as 0
   0b1100111,       // 'P'
   MAX7219_HYPHEN, // 'Q'
   0b0000101,       // 'R'
   0b1011011,       // 'S'
   0b0000111,       // 'T'
   0b0111110,       // 'U'
   MAX7219_HYPHEN, // 'V'
   MAX7219_HYPHEN, // 'W'
   MAX7219_HYPHEN, // 'X'
   0b0100111,       // 'Y'
   MAX7219_HYPHEN, // 'Z'
   0b1001110,       // '['  - same as C
   MAX7219_HYPHEN, // backslash
   0b1111000,       // ']'
   MAX7219_HYPHEN, // '^'
   0b0001000,       // '_'
   MAX7219_HYPHEN, // '`'
   0b1110111,       // 'a'
   0b0011111,       // 'b'
   0b0001101,       // 'c'
   0b0111101,       // 'd'
   0b1001111,       // 'e'
   0b1000111,       // 'f'
   0b1011110,       // 'g'
   0b0010111,       // 'h'
   0b0010000,       // 'i'
   0b0111100,       // 'j'
   MAX7219_HYPHEN, // 'k'
   0b0001110,       // 'l'
   MAX7219_HYPHEN, // 'm'
   0b0010101,       // 'n'
   0b1111110,       // 'o' - same as 0
   0b1100111,       // 'p'
   MAX7219_HYPHEN, // 'q'
   0b0000101,       // 'r'
   0b1011011,       // 's'
   0b0000111,       // 't'
   0b0011100,       // 'u'
   MAX7219_HYPHEN, // 'v'
   MAX7219_HYPHEN, // 'w'
   MAX7219_HYPHEN, // 'x'
   0b0100111,       // 'y'
   MAX7219_HYPHEN, // 'z'
}; //  end of MAX7219_font


#endif /* MAX7219_FONT_H_ */
