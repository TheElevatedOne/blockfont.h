# blockfont.h

blockfont.h is a C header-only library that renders text using a 6x5 grid of ASCII blocks (█). Supports numbers, letters, symbols, scaling, and ANSI colors.

![repo_title](https://raw.githubusercontent.com/TheElevatedOne/blockfont.h/refs/heads/main/example/repo_name.png)

## List of Contents

1. [**Features**](#features)
2. [**Installation**](#installation)
3. [**Usage**](#usage)
4. [**Documentation**](#documentation)
5. [**Issues**](#issues)
6. [**Disclaimer**](#disclaimer)

## Features

- **96 characters**: space, unknown, numbers, lowercase & uppercase letters, symbols.
- Scalable text with `scale` parameter.
- ANSI 256-color support.

## Installation

Either
```shell
git clone https://github.com/TheElevatedOne/blockfont.h.git
```

Or
```shell
git submodule add https://github.com/TheElevatedOne/blockfont.h.git blockfont
```

and then
```c
#include "blockfont.h/blockfont.h"
```

## Usage

### Basic Usage

```c
#include "blockfont.h/blockfont.h"
#include <stdio.h>

int main() {
  fontized text;
  text = blockfont("Hello", 1);
  for (int row = 0; row < 5; row++) {
    printf("%s\n", text.text[row]);
  }
  return 0;
}
```

### Color Usage
```c
int main() {
  fontized text;
  text = blockfont_color("Hello", 1, 9);
  for (int row = 0; row < 5; row++) {
    printf("%s\n", text.text[row]);
  }
  return 0;
}
```

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

## Issues

Some characters are not as easy to recognise and some are unrecognisable.<br>
This is a limitation of the Font Grid.

This is where other people can take the wheel.<br>
If you have a symbol you want to be added, have another way to render the character, etc., either **Open an Issue** or with many changes **Fork the Repository And Open a Pull Request**.

![font-preview](https://raw.githubusercontent.com/TheElevatedOne/blockfont.h/refs/heads/main/example/font.png)

## Disclaimer 

I, as many other programmers, use AI as a tool when working on projects. <br>
Some parts of this project have been firstly designed by AI, later modified or found by AI instead of looking through documentation.

I do not plan to stop this practice, but I also check every piece of code that comes out of AI so that it is not malicious nor code breaking. <br>
And for the better or the worse, AI prompting is much, much faster than searching up documentation.
