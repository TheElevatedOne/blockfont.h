#include "../blockfont.h"
#include <stdio.h>

int main() {
  fontized font;
  font = blockfont(" Á0123456789", 1);
  printf("\n");
  print_blockfont(font);
  font = blockfont("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1);
  printf("\n");
  print_blockfont(font);
  font = blockfont("abcdefghijklmnopqrstuvwxyz", 1);
  printf("\n");
  print_blockfont(font);
  font = blockfont(".,:;'\"/|\\()[]{}<>=+-_!?`~@", 1);
  printf("\n");
  print_blockfont(font);
  font = blockfont("#$%^&*", 1);
  printf("\n");
  print_blockfont(font);
  printf("\n");

  return 0;
}
