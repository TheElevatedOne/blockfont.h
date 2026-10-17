#include "../blockfont.h"
#include <stdio.h>

int main() {
  const char *lines[] = {
      " Á0123456789",
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "abcdefghijklmnopqrstuvwxyz",
      ".,:;'\"/|\\()[]{}<>=+-_!?`~@",
      "#$%^&*",
  };
  for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
    fontized font = blockfont(lines[i], 1);
    printf("\n");
    print_blockfont(font);
    free_blockfont(&font);
  }
  printf("\n");

  return 0;
}
