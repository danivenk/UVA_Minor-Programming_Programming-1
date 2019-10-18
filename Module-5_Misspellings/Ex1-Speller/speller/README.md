# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

pneumonoultramicroscopicsilicovolcanoconiosis is a lung desease caused by inhaling fine ash or sand.

## According to its man page, what does `getrusage` do?

`getrusage` returns resource usage measures for `who`.

## Per that same man page, how many members are in a variable of type `struct rusage`?

14 variables and 2 structures.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

because the `calculate` function expects a pointer.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

First it opens the specified file, then it reads it character for character. For each first character of a
    word it checks if it is alpha or apostrophe, when this is true it adds the character to the word and
    reads the rest. If it is a number it ignores it. When the end of a word has been found it terminates the
    word array and checks if the word is included in the dictionary and checks for misspellings.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

when using `fgetc` to read each character punctuation and unwanted character can get easily be discarded.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

to avoid it being changed by the function, `const` means the parameter won't be changed
