#ifndef BLOCKFONT_H
#define BLOCKFONT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define FONT_WIDTH 6
#define FONT_HEIGHT 5
#define FONT_CHARS 128
#define SCALE_MIN 1

typedef struct {
  int value;
  char text[8192];
} fontized;

// 6x5 font stored as bitmasks (each row is 5 bits)
static const unsigned char font[FONT_CHARS][FONT_HEIGHT] = {
    // CATEGORY | {6-bit binary per line} | character | ascii
    //
    // NUMBERS
    {0x3F, 0x33, 0x33, 0x33, 0x3F}, // zero 48
    {0x0C, 0x3C, 0x0C, 0x0C, 0x3F}, // one 49
    {0x3F, 0x03, 0x3F, 0x30, 0x3F}, // two 50
    {0x3F, 0x03, 0x0F, 0x03, 0x3F}, // three 51
    {0x33, 0x33, 0x3F, 0x03, 0x03}, // four 52
    {0x3F, 0x30, 0x3F, 0x03, 0x3F}, // five 53
    {0x3F, 0x30, 0x3F, 0x33, 0x3F}, // six 54
    {0x3F, 0x03, 0x03, 0x03, 0x03}, // seven 55
    {0x3F, 0x33, 0x3F, 0x33, 0x3F}, // eight 56
    {0x3F, 0x33, 0x3F, 0x03, 0x3F}, // nine 57
    // WHITESPACE
    {0x00, 0x00, 0x00, 0x00, 0x00}, // space 32
    // LETTERS
    {0x3F, 0x33, 0x3F, 0x33, 0x33}, // A 65
    {0x3C, 0x33, 0x3C, 0x33, 0x3C}, // B 66
    {0x3F, 0x30, 0x30, 0x30, 0x3F}, // C 67
    {0x3C, 0x33, 0x33, 0x33, 0x3C}, // D 68
    {0x3F, 0x30, 0x3C, 0x30, 0x3F}, // E 69
    {0x3F, 0x30, 0x3C, 0x30, 0x30}, // F 70
    {0x3F, 0x30, 0x37, 0x33, 0x3F}, // G 71
    {0x33, 0x33, 0x3F, 0x33, 0x33}, // H 72
    {0x3F, 0x0C, 0x0C, 0x0C, 0x3F}, // I 73
    {0x03, 0x03, 0x03, 0x33, 0x3F}, // J 74
    {0x33, 0x36, 0x3C, 0x36, 0x33}, // K 75
    {0x30, 0x30, 0x30, 0x30, 0x3F}, // L 76
    {0x21, 0x33, 0x2D, 0x21, 0x21}, // M 77
    {0x21, 0x31, 0x2D, 0x23, 0x21}, // N 78
    {0x1E, 0x33, 0x33, 0x33, 0x1E}, // O 79
    {0x3F, 0x33, 0x3F, 0x30, 0x30}, // P 80
    {0x1E, 0x33, 0x33, 0x37, 0x1D}, // Q 81
    {0x3F, 0x33, 0x3C, 0x33, 0x33}, // R 82
    {0x0F, 0x30, 0x0C, 0x03, 0x3C}, // S 83
    {0x3F, 0x0C, 0x0C, 0x0C, 0x0C}, // T 84
    {0x33, 0x33, 0x33, 0x33, 0x3F}, // U 85
    {0x33, 0x33, 0x33, 0x33, 0x0C}, // V 86
    {0x21, 0x21, 0x2D, 0x33, 0x21}, // W 87
    {0x21, 0x12, 0x0C, 0x12, 0x21}, // X 88
    {0x33, 0x33, 0x3F, 0x0C, 0x0C}, // Y 89
    {0x3F, 0x03, 0x0C, 0x30, 0x3F}, // Z 90
    {0x3C, 0x03, 0x0F, 0x33, 0x0F}, // a 97
    {0x30, 0x30, 0x3F, 0x33, 0x3F}, // b 98
    {0x00, 0x00, 0x3F, 0x30, 0x3F}, // c 99
    {0x03, 0x03, 0x3F, 0x33, 0x3F}, // d 100
    {0x0C, 0x33, 0x3C, 0x30, 0x0F}, // e 101
    {0x0C, 0x30, 0x3C, 0x30, 0x30}, // f 102
    {0x0C, 0x33, 0x0F, 0x23, 0x1C}, // g 103
    {0x30, 0x30, 0x3F, 0x33, 0x33}, // h 104
    {0x00, 0x0C, 0x00, 0x0C, 0x0C}, // i 105
    {0x03, 0x00, 0x03, 0x33, 0x3F}, // j 106
    {0x30, 0x30, 0x33, 0x3C, 0x33}, // k 107
    {0x3C, 0x0C, 0x0C, 0x0C, 0x3F}, // l 108
    {0x00, 0x00, 0x34, 0x2A, 0x2A}, // m 109
    {0x00, 0x00, 0x3C, 0x22, 0x22}, // n 110
    {0x00, 0x00, 0x3F, 0x33, 0x3F}, // o 111
    {0x00, 0x3C, 0x33, 0x3C, 0x30}, // p 112
    {0x00, 0x0F, 0x33, 0x0F, 0x03}, // q 113
    {0x00, 0x33, 0x3C, 0x30, 0x30}, // r 114
    {0x00, 0x0F, 0x38, 0x07, 0x3C}, // s 115
    {0x00, 0x0C, 0x3F, 0x0C, 0x0C}, // t 116
    {0x00, 0x00, 0x33, 0x33, 0x3F}, // u 117
    {0x00, 0x00, 0x33, 0x33, 0x0C}, // v 118
    {0x00, 0x00, 0x22, 0x22, 0x14}, // w 119
    {0x00, 0x00, 0x33, 0x0C, 0x33}, // x 120
    {0x00, 0x33, 0x33, 0x0C, 0x30}, // y 121
    {0x00, 0x3F, 0x06, 0x18, 0x3F}, // z 122
    // SYMBOLS
    {0x3F, 0x3F, 0x3F, 0x3F, 0x3F}, // unknown default
    {0x00, 0x00, 0x00, 0x00, 0x0C}, // dot 46
    {0x00, 0x00, 0x00, 0x0C, 0x18}, // comma 44
    {0x00, 0x0C, 0x00, 0x0C, 0x00}, // colon 58
    {0x03, 0x06, 0x0C, 0x18, 0x30}, // slash 47
    {0x30, 0x18, 0x0C, 0x06, 0x03}, // backslash 92
    {0x03, 0x0C, 0x0C, 0x0C, 0x03}, // left_round_bracket 40
    {0x30, 0x0C, 0x0C, 0x0C, 0x30}, // right_round_bracket 41
    {0x3C, 0x0C, 0x0C, 0x0C, 0x3C}, // left_square_bracket 91
    {0x0F, 0x0C, 0x0C, 0x0C, 0x0F}, // right_square_bracket 93
    {0x03, 0x06, 0x0C, 0x06, 0x03}, // left_curly_bracket 123
    {0x30, 0x18, 0x0C, 0x18, 0x30}, // right_curly_bracket 125
    {0x0C, 0x0C, 0x00, 0x00, 0x00}, // single_quote 39
    {0x33, 0x33, 0x00, 0x00, 0x00}, // double_quotes 34
    {0x00, 0x0C, 0x00, 0x0C, 0x18}, // semicolon 59
    {0x18, 0x06, 0x00, 0x00, 0x00}, // grave_backtick 96
    {0x00, 0x10, 0x2A, 0x20, 0x00}, // tilde 126
    {0x3C, 0x03, 0x0C, 0x00, 0x0C}, // question_mark 63
    {0x0C, 0x0C, 0x0C, 0x00, 0x0C}, // exclamation_mark 33
    {0x1E, 0x21, 0x2D, 0x26, 0x10}, // at_sign 64
    {0x12, 0x3F, 0x12, 0x3F, 0x12}, // hashtag 35
    {0x1F, 0x32, 0x1E, 0x13, 0x3E}, // dollar_sign 36
    {0x33, 0x06, 0x0C, 0x18, 0x33}, // percent 37
    {0x0C, 0x12, 0x21, 0x00, 0x00}, // caret 94
    {0x03, 0x0C, 0x30, 0x0C, 0x03}, // less_than 60
    {0x30, 0x0C, 0x03, 0x0C, 0x30}, // more_than 62
    {0x1C, 0x2A, 0x1C, 0x24, 0x1E}, // ampersand 38
    {0x2A, 0x1C, 0x2A, 0x00, 0x00}, // asterisk 42
    {0x00, 0x00, 0x3F, 0x00, 0x00}, // dash 45
    {0x00, 0x00, 0x00, 0x00, 0x3F}, // underscore 95
    {0x00, 0x0C, 0x3F, 0x0C, 0x00}, // plus 43
    {0x00, 0x3F, 0x00, 0x3F, 0x00}, // equals 61
    {0x0C, 0x0C, 0x0C, 0x0C, 0x0C}  // pipe 124
};

static fontized text_to_font(const char *text, int scale) {
  fontized result;

  // Check if there is no text or
  // no scaling and return
  if (strlen(text) == 0 || scale < SCALE_MIN) {
    strcpy(result.text, "");
    result.value = 1;
    return result;
  }

  // Go through font height
  for (int row = 0; row < FONT_HEIGHT; row++) {
    // Vertical Scaling
    for (int vs = 0; vs < scale; vs++) {
      // Check per Character in char *text
      for (size_t i = 0; i < strlen(text); i++) {
        const unsigned char *glyph = NULL;
        // Check if character is a number
        // as they are on top of the font
        if (text[i] >= '0' && text[i] <= '9') {
          glyph = font[text[i] - '0'];
        } else {
          // Check other charactes based on ascii
          switch ((int)text[i]) {
          case 32:
            glyph = font[10];
            break;
          case 65:
            glyph = font[11];
            break;
          case 66:
            glyph = font[12];
            break;
          case 67:
            glyph = font[13];
            break;
          case 68:
            glyph = font[14];
            break;
          case 69:
            glyph = font[15];
            break;
          case 70:
            glyph = font[16];
            break;
          case 71:
            glyph = font[17];
            break;
          case 72:
            glyph = font[18];
            break;
          case 73:
            glyph = font[19];
            break;
          case 74:
            glyph = font[20];
            break;
          case 75:
            glyph = font[21];
            break;
          case 76:
            glyph = font[22];
            break;
          case 77:
            glyph = font[23];
            break;
          case 78:
            glyph = font[24];
            break;
          case 79:
            glyph = font[25];
            break;
          case 80:
            glyph = font[26];
            break;
          case 81:
            glyph = font[27];
            break;
          case 82:
            glyph = font[28];
            break;
          case 83:
            glyph = font[29];
            break;
          case 84:
            glyph = font[30];
            break;
          case 85:
            glyph = font[31];
            break;
          case 86:
            glyph = font[32];
            break;
          case 87:
            glyph = font[33];
            break;
          case 88:
            glyph = font[34];
            break;
          case 89:
            glyph = font[35];
            break;
          case 90:
            glyph = font[36];
            break;
          case 97:
            glyph = font[37];
            break;
          case 98:
            glyph = font[38];
            break;
          case 99:
            glyph = font[39];
            break;
          case 100:
            glyph = font[40];
            break;
          case 101:
            glyph = font[41];
            break;
          case 102:
            glyph = font[42];
            break;
          case 103:
            glyph = font[43];
            break;
          case 104:
            glyph = font[44];
            break;
          case 105:
            glyph = font[45];
            break;
          case 106:
            glyph = font[46];
            break;
          case 107:
            glyph = font[47];
            break;
          case 108:
            glyph = font[48];
            break;
          case 109:
            glyph = font[49];
            break;
          case 110:
            glyph = font[50];
            break;
          case 111:
            glyph = font[51];
            break;
          case 112:
            glyph = font[52];
            break;
          case 113:
            glyph = font[53];
            break;
          case 114:
            glyph = font[54];
            break;
          case 115:
            glyph = font[55];
            break;
          case 116:
            glyph = font[56];
            break;
          case 117:
            glyph = font[57];
            break;
          case 118:
            glyph = font[58];
            break;
          case 119:
            glyph = font[59];
            break;
          case 120:
            glyph = font[60];
            break;
          case 121:
            glyph = font[61];
            break;
          case 122:
            glyph = font[62];
            break;
          case 46:
            glyph = font[64];
            break;
          case 44:
            glyph = font[65];
            break;
          case 58:
            glyph = font[66];
            break;
          case 47:
            glyph = font[67];
            break;
          case 92:
            glyph = font[68];
            break;
          case 40:
            glyph = font[69];
            break;
          case 41:
            glyph = font[70];
            break;
          case 91:
            glyph = font[71];
            break;
          case 93:
            glyph = font[72];
            break;
          case 123:
            glyph = font[73];
            break;
          case 125:
            glyph = font[74];
            break;
          case 39:
            glyph = font[75];
            break;
          case 34:
            glyph = font[76];
            break;
          case 59:
            glyph = font[77];
            break;
          case 96:
            glyph = font[78];
            break;
          case 126:
            glyph = font[79];
            break;
          case 63:
            glyph = font[80];
            break;
          case 33:
            glyph = font[81];
            break;
          case 64:
            glyph = font[82];
            break;
          case 35:
            glyph = font[83];
            break;
          case 36:
            glyph = font[84];
            break;
          case 37:
            glyph = font[85];
            break;
          case 94:
            glyph = font[86];
            break;
          case 60:
            glyph = font[87];
            break;
          case 62:
            glyph = font[88];
            break;
          case 38:
            glyph = font[89];
            break;
          case 42:
            glyph = font[90];
            break;
          case 45:
            glyph = font[91];
            break;
          case 95:
            glyph = font[92];
            break;
          case 43:
            glyph = font[93];
            break;
          case 61:
            glyph = font[94];
            break;
          case 124:
            glyph = font[95];
            break;
          default:
            glyph = font[63];
            break;
          }
        }
        if (glyph) {
          for (int col = 0; col < FONT_WIDTH; col++) {
            int bit = glyph[row] & (1 << (FONT_WIDTH - 1 - col));
            for (int hs = 0; hs < scale; hs++) {
              strcat(result.text, bit ? "█" : " ");
            }
          }
        }
        for (int i = 0; i < scale; i++) {
          strcat(result.text, " ");
        }
      }
      strcat(result.text, "\n");
    }
  }
  result.value = 0;
  return result;
}

#endif // !BLOCKFONT_H
