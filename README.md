# blockfont.h

![repo_title](https://raw.githubusercontent.com/TheElevatedOne/blockfont.h/refs/heads/main/example/repo_name.png)

A Font Import for C using 6x5 Grid of Ascii Blocks

## List of Contents

1. [**Font**](#font)
2. [**Documentation**](#documentation)
    - [Struct](#struct)
    - [Functions](#functions)
    - [Character Map](#character-map)

## Font

![font-preview](https://raw.githubusercontent.com/TheElevatedOne/blockfont.h/refs/heads/main/example/font.png)

Font currently has 96 characters, uses a 6 Wide and 5 Tall Grid of Spaces and ASCII Blocks (█).

It includes a space, unknown (shown as the first two in the preview),
Numbers, Small Latin Alphabet, Large Latin Alphabet and Symbols found on ANSI Keyboards.

Some characters are less recognisable than others, as it is a limitation of the grid size.
If you have some variation for a character that can be easier to recognise, create an Issue.

## Documentation

The code consists of a Struct, a Function and the Character Map.

### Struct

```c
typedef struct {
    int value;
    char text[5][8192];
} fontized;
```

The Struct is the return value of the function.
It consists of:
- `int value` - return code
- `char text[5][8192]` - return array of blocks and spaces per row of the result text without newlines

### Functions

```c
static fontized blockfont(const char *text, int scale);
```

The Function expects a Text and a Scale value.<br>
Text must be at least 1 character long and scale must be at least 1.<br>
Otherwise it returns a Struct with `int value = 1` and `char text = ""`.<br>
Return `int value = 0` is normal.<br>
Uses the default white coloring (ANSI color15, `\033[38;5;15m`)

```c
static fontized blockfont_color(const char *text, int scale, int color);
```

Expects the same as previous function, plus a Color.<br>
The color is an integer from 0 to 255 of an ANSI color.<br>

**Color Table:** (16 Colors)<br>
<img src="https://raw.githubusercontent.com/TheElevatedOne/blockfont.h/refs/heads/main/example/color_table.png" width="25%">

For Color Code Reference above 16 colors, look up [ANSI 256 Color Sheet](https://www.ditig.com/256-colors-cheat-sheet).

### Character Map

```c
#define FONT_HEIGHT 5
#define FONT_CHARS 128

static const unsigned char font[FONT_CHARS][FONT_HEIGHT] = {
    // CATEGORY | {6-bit binary per line} | character | ascii
    //
    // NUMBERS
    {0x3F, 0x33, 0x33, 0x33, 0x3F}, // zero 48
    {0x0C, 0x3C, 0x0C, 0x0C, 0x3F}, // one 49
    {0x3F, 0x03, 0x3F, 0x30, 0x3F}, // two 50
    ...
}
```

It maps the font per line in 6-bit Binary in Hexadecimal Format,
where `1` is a block and `0` is a space.

It has comments per Categories and per Character, with its Name and ASCII value.

## Disclaimer 

I, as many other programmers, use AI as a tool when working on projects.

Some parts of this project have been firstly designed by AI, later modified or found by AI instead of looking through documentation.

I do not plan to stop this practice, but I also check every piece of code that comes out of AI so that it is not malicious nor code breaking.

And for the better or the worse, AI prompting is much, much faster than searching up documentation.
