#include "../blockfont.h"
#include <stdio.h>

int main() {
  fontized font;
  font = text_to_block(" Á0123456789", 1);
  printf("\n%s\n", font.text);
  font = text_to_block("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1);
  printf("%s\n", font.text);
  font = text_to_block("abcdefghijklmnopqrstuvwxyz", 1);
  printf("%s\n", font.text);
  font = text_to_block(".,:;'\"/|\\()[]{}<>=+-_!?`~@", 1);
  printf("%s\n", font.text);
  font = text_to_block("#$%^&*", 1);
  printf("%s\n", font.text);

  return 0;
}
