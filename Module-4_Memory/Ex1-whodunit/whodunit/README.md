# Questions

## What's `stdint.h`?

`stdint.h` is a header which specifies integers to have set widths.
Where the width of an integer is the number of bit used in a pure binary system to store the integer.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

You can use these to define integers with a width of at exact;y 8, 16 or 32 bits.
If you use `uin8_t`, `uint16_t` or `uint32_t` you're able to use positive numbers with a width of exactly 8, 16 or 32 bits.
If you use `int32_t` you're able to use both positive and negative numbers but the number can only have a width of 31 bits,
        the leftmost bit is used for positive or negative.
This can be pretty handy if you're making a program which hadles a lot of integer numbers of size 8, 16, 32 or positive/negative 31 bits.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

A `BYTE` is 1 byte, a `DWORD` is 4 bytes, a `LONG` is 4 bytes and a `WORD` is 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes of a BMP-file must be `0x4d42`

## What's the difference between `bfSize` and `biSize`?

`bfSize` refers to the size of the Bitmap file, `biSize` is the size of the Bitmap info header. Both are in bytes.

## What does it mean if `biHeight` is negative?

A negative `biHeight` means that the bitmap begins at the left upper most pixel and then goes left to right and top to bottom.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The color depth is specified at adress `0x1C` which is field called `biBitCount`

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

`fopen` will return `NULL` when it is not able to open the file or create a file to write in.

## Why is the third argument to `fread` always `1` in our code?

`fread` has `1` because only one element of size `sizeof()` is needed to be read.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

`sizeof(RGBTRIPLE)` = 3 bytes ->
    (4 - (3 * 3) % 4) % 4 ->
        (4 - (9) % 4) % 4 ->
            (4 - 1) % 4 -> 3 % 4 -> `padding` = 3

## What does `fseek` do?

`fseek` changes cursor position in stream (file) from `whence` to `whence` + `offset`.

## What is `SEEK_CUR`?

`SEEK_CUR` is the current position in the stream (file).
