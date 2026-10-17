#include "blockfont.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FONT_CHARS 128

// Longest color escape sequence "\033[38;5;255m"
#define COLOR_SEQ_MAX 11
// Reset escape sequence "\033[0m"
#define RESET_SEQ "\033[0m"
#define BLOCK "█"

// 6x5 font stored as bitmasks (each row is 6 bits)
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
    {0x06, 0x18, 0x1E, 0x18, 0x18}, // f 102
    {0x0C, 0x33, 0x0F, 0x23, 0x1C}, // g 103
    {0x30, 0x30, 0x3F, 0x33, 0x33}, // h 104
    {0x00, 0x0C, 0x00, 0x0C, 0x0C}, // i 105
    {0x03, 0x00, 0x03, 0x33, 0x3F}, // j 106
    {0x30, 0x30, 0x33, 0x3C, 0x33}, // k 107
    {0x3C, 0x0C, 0x0C, 0x0C, 0x3F}, // l 108
    {0x00, 0x00, 0x34, 0x2A, 0x2A}, // m 109
    {0x00, 0x00, 0x3C, 0x33, 0x33}, // n 110
    {0x00, 0x00, 0x3F, 0x33, 0x3F}, // o 111
    {0x00, 0x3C, 0x33, 0x3C, 0x30}, // p 112
    {0x00, 0x0F, 0x33, 0x0F, 0x03}, // q 113
    {0x00, 0x33, 0x3C, 0x30, 0x30}, // r 114
    {0x00, 0x0F, 0x38, 0x07, 0x3C}, // s 115
    {0x00, 0x0C, 0x3F, 0x0C, 0x0C}, // t 116
    {0x00, 0x00, 0x33, 0x33, 0x3F}, // u 117
    {0x00, 0x00, 0x33, 0x33, 0x0C}, // v 118
    {0x00, 0x00, 0x22, 0x2A, 0x14}, // w 119
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
    {0x00, 0x10, 0x2A, 0x04, 0x00}, // tilde 126
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

// Returns the glyph for a character
static const unsigned char *glyph_for(char c) {
  // Numbers are on top of the font
  if (c >= '0' && c <= '9') {
    return font[c - '0'];
  }
  // Check other charactes based on ascii
  switch ((int)c) {
  case 32:
    return font[10];
  case 65:
    return font[11];
  case 66:
    return font[12];
  case 67:
    return font[13];
  case 68:
    return font[14];
  case 69:
    return font[15];
  case 70:
    return font[16];
  case 71:
    return font[17];
  case 72:
    return font[18];
  case 73:
    return font[19];
  case 74:
    return font[20];
  case 75:
    return font[21];
  case 76:
    return font[22];
  case 77:
    return font[23];
  case 78:
    return font[24];
  case 79:
    return font[25];
  case 80:
    return font[26];
  case 81:
    return font[27];
  case 82:
    return font[28];
  case 83:
    return font[29];
  case 84:
    return font[30];
  case 85:
    return font[31];
  case 86:
    return font[32];
  case 87:
    return font[33];
  case 88:
    return font[34];
  case 89:
    return font[35];
  case 90:
    return font[36];
  case 97:
    return font[37];
  case 98:
    return font[38];
  case 99:
    return font[39];
  case 100:
    return font[40];
  case 101:
    return font[41];
  case 102:
    return font[42];
  case 103:
    return font[43];
  case 104:
    return font[44];
  case 105:
    return font[45];
  case 106:
    return font[46];
  case 107:
    return font[47];
  case 108:
    return font[48];
  case 109:
    return font[49];
  case 110:
    return font[50];
  case 111:
    return font[51];
  case 112:
    return font[52];
  case 113:
    return font[53];
  case 114:
    return font[54];
  case 115:
    return font[55];
  case 116:
    return font[56];
  case 117:
    return font[57];
  case 118:
    return font[58];
  case 119:
    return font[59];
  case 120:
    return font[60];
  case 121:
    return font[61];
  case 122:
    return font[62];
  case 46:
    return font[64];
  case 44:
    return font[65];
  case 58:
    return font[66];
  case 47:
    return font[67];
  case 92:
    return font[68];
  case 40:
    return font[69];
  case 41:
    return font[70];
  case 91:
    return font[71];
  case 93:
    return font[72];
  case 123:
    return font[73];
  case 125:
    return font[74];
  case 39:
    return font[75];
  case 34:
    return font[76];
  case 59:
    return font[77];
  case 96:
    return font[78];
  case 126:
    return font[79];
  case 63:
    return font[80];
  case 33:
    return font[81];
  case 64:
    return font[82];
  case 35:
    return font[83];
  case 36:
    return font[84];
  case 37:
    return font[85];
  case 94:
    return font[86];
  case 60:
    return font[87];
  case 62:
    return font[88];
  case 38:
    return font[89];
  case 42:
    return font[90];
  case 45:
    return font[91];
  case 95:
    return font[92];
  case 43:
    return font[93];
  case 61:
    return font[94];
  case 124:
    return font[95];
  default:
    return font[63];
  }
}

fontized blockfont_color(const char *text, int scale, int color) {
  fontized result = {0};
  result.value = 1;

  // Check if there is no text or
  // no scaling and return
  if (text == NULL || text[0] == '\0' || scale < SCALE_MIN) {
    return result;
  }

  // Check if color values are
  // out of range for ANSI colors
  if (color < 0 || color > 255) {
    return result;
  }

  if (scale > INT_MAX / FONT_HEIGHT) {
    return result;
  }

  size_t len = strlen(text);
  size_t rows = (size_t)scale * FONT_HEIGHT;

  // Worst case bytes per character on a row:
  // every column is a block, plus the spacing after it
  size_t per_char = (size_t)scale * (FONT_WIDTH * (sizeof(BLOCK) - 1) + 1);
  size_t overhead = COLOR_SEQ_MAX + (sizeof(RESET_SEQ) - 1) + 1;
  if (len > (SIZE_MAX - overhead) / per_char) {
    return result;
  }
  size_t row_size = len * per_char + overhead;
  if (rows > SIZE_MAX / row_size) {
    return result;
  }

  // One block for row pointers, one block for all row data
  char **lines = malloc(rows * sizeof(char *));
  if (lines == NULL) {
    return result;
  }
  char *data = malloc(rows * row_size);
  if (data == NULL) {
    free(lines);
    return result;
  }

  size_t line = 0;
  // Go through font height
  for (int row = 0; row < FONT_HEIGHT; row++) {
    // Vertical Scaling
    for (int vs = 0; vs < scale; vs++, line++) {
      char *out = data + line * row_size;
      lines[line] = out;
      out += sprintf(out, "\033[38;5;%dm", color);
      // Check per Character in char *text
      for (size_t i = 0; i < len; i++) {
        const unsigned char *glyph = glyph_for(text[i]);
        for (int col = 0; col < FONT_WIDTH; col++) {
          int bit = glyph[row] & (1 << (FONT_WIDTH - 1 - col));
          for (int hs = 0; hs < scale; hs++) {
            if (bit) {
              memcpy(out, BLOCK, sizeof(BLOCK) - 1);
              out += sizeof(BLOCK) - 1;
            } else {
              *out++ = ' ';
            }
          }
        }
        memset(out, ' ', (size_t)scale);
        out += scale;
      }
      memcpy(out, RESET_SEQ, sizeof(RESET_SEQ));
    }
  }

  result.value = 0;
  result.scale = scale;
  result.rows = (int)rows;
  result.text = lines;
  return result;
}

fontized blockfont(const char *text, int scale) {
  return blockfont_color(text, scale, 15);
}

void print_blockfont(fontized result) {
  for (int row = 0; row < result.rows; row++) {
    printf("%s\n", result.text[row]);
  }
}

void free_blockfont(fontized *result) {
  if (result == NULL) {
    return;
  }
  if (result->text != NULL) {
    free(result->text[0]);
    free(result->text);
  }
  result->text = NULL;
  result->rows = 0;
  result->scale = 0;
  result->value = 1;
}
