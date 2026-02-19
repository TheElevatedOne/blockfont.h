#include "../blockfont.h"
#include <stdio.h>

int main() {
  fontized font;
  font = text_to_font(" Á0123456789", 1);
  printf("\n%s\n", font.text);
  font = text_to_font("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1);
  printf("%s\n", font.text);
  font = text_to_font("abcdefghijklmnopqrstuvwxyz", 1);
  printf("%s\n", font.text);
  font = text_to_font(".,:;'\"/|\\()[]{}<>=+-_!?`~@", 1);
  printf("%s\n", font.text);
  font = text_to_font("#$%^&*", 1);
  printf("%s\n", font.text);

  return 0;
}
