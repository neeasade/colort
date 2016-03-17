## colort[int]

A small program for 'tinting' colors by values. Also supports inverting colors.

command                          | output
---------------------------------|-------
`colort 1 "#000000"`             | `#010101`
`colort -l 1 "#FFFFFF"`          | `#FFFFFF`
`colort -i "#000000"`            | `#FFFFFF`
`colort 60 "#000000"`            | `#3C3C3C`
`colort -60 "#000000"`           | `#C4C4C4`
`colort -s 4 1 "spam000000spam"` | `spam010101spam`
`colort -r 1 "#000000"`          | `#010000`


### Notes:

- The color is assumed to be the last 6 chars of the input string (can be changed with `-s`)
- The `-l` flag limits color tinting by not letting values roll around.
- The `-i` flag inverts colors.
- The `-s` selects the index in the input string to start getting color from.
- The `-c` flag calculates the contrast of the color. If this evaluates to black, exit status 0. If white, exit status 1.
- If the -r, -g, or -b flags are used, red, green, or blue are affected by the operation respectively.
- The tint value can be within the set of values supported by a `long` datatype.


### TODO

- [x] add --upper and --lower flags to set boundries (eg `colort --upper 3 "ffffff" --> ffffff`)
	- [x] should this be automatic depending on tint direction? it should be.
- [x] make values be toggled on their own (eg `colort 1 000000 --> 010101`)
	- This would mean color/pattern validation, as currently we just iterate on characters that /could/ be in a color.
- [x] proper args and usage
- [x] --invert(-i) option.
