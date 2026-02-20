#include "../blockfont.h"
#include <stdio.h>

int main() {
  fontized font;
  font = blockfont_color("blockfont.h", 1, 10);
  printf("\n");
  for (int row = 0; row < 5; row++) {
    printf("%s", font.text[row]);
    printf("\n");
  }
  printf("\n");

  return 0;
}
