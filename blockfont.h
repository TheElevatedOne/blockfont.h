#ifndef BLOCKFONT_H
#define BLOCKFONT_H

#ifdef __cplusplus
extern "C" {
#endif

#define FONT_WIDTH 6
#define FONT_HEIGHT 5
#define SCALE_MIN 1

/**
 * Is the return-type for both functions.
 * Must be released with free_blockfont().
 *
 * @param int value Returns a 0 if all good, otherwise 1
 * @param int scale Scale the text was rendered with
 * @param int rows Number of rows in text (FONT_HEIGHT * scale)
 * @param char **text Heap allocated array of rows of blocks
 */
typedef struct {
  int value;
  int scale;
  int rows;
  char **text;
} fontized;

/**
 * Returns a blockfont with specified color
 *
 * @param char *text Input Text
 * @param int scale Font Scale
 * @param int color ANSI Color 0-255
 *
 * Colors are ANSI Escape Sequences:
 * so 0 for Black
 * and 8 for Gray
 */
fontized blockfont_color(const char *text, int scale, int color);

/**
 * Returns a blockfont
 * with default color15 white
 *
 * @param char *text Input Text
 * @param int scale Font Scale
 */
fontized blockfont(const char *text, int scale);

/**
 * Prints the blockfont into the console
 * without any changes to it.
 * For testing/example purposes
 *
 * @param fontized result Return from blockfont functions
 */
void print_blockfont(fontized result);

/**
 * Frees memory allocated by blockfont functions
 * and resets the struct. Safe to call on failed
 * results and multiple times.
 *
 * @param fontized *result Return from blockfont functions
 */
void free_blockfont(fontized *result);

#ifdef __cplusplus
}
#endif

#endif // !BLOCKFONT_H
