#include "../blockfont.h"
#include <stdio.h>

int main() {
  fontized font;
  font = text_to_block("blockfont.h", 1);
  printf("%s\n", font.text);

  return 0;
}
