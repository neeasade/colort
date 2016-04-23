## colort[int]

A small program for 'tinting' colors by values. Also supports inverting colors.

command                             | output
------------------------------------|-------
`colort 1 "#000000"`                | `#010101`
`colort -l 1 "#FFFFFF"`             | `#FFFFFF`
`colort -i "#000000"`               | `#FFFFFF`
`colort 60 "#000000"`               | `#3C3C3C`
`colort -60 "#000000"`              | `#C4C4C4`
`colort -s 4 1 "spam000000spam"`    | `spam010101spam`
`colort -t -s 4 1 "spam000000spam"` | `010101`
`colort -r 1 "#000000"`             | `#010000`


### Notes:

- The color is assumed to be the last 6 chars of the input string (can be changed with `-s`)
- The `-l` flag limits color tinting by not letting values roll around.
- The `-i` flag inverts colors.
- The `-s` flag selects the index in the input string to start getting color from.
- The `-t` flag makes the output only the color string
- The `-c` flag calculates the contrast of the color. If this evaluates to black, exit status 0. If white, exit status 1.
- If the -r, -g, or -b flags are used, red, green, or blue are affected by the operation respectively.
- The tint value can be within the set of values supported by a `long` datatype.


### Example use cases:

Invert a background color to have readable text on any background:

![1](https://u.teknik.io/nS1O3.png) | ![2](https://u.teknik.io/jHTr9.png) | ![3](https://u.teknik.io/JLLZ2.png)
------------------------------------|-------------------------------------|------------------------------------

Auto-determine select and icon colors for GTK themes based on the background (using oomox and acyl in these examples)
- `Select_color="$(colort -c "$BG" && colort 25 "$BG" || colort -25 "$BG")"`
	- If the background contrast is 'dark', tint up, else tint down.
- `Icon_color="$(colort -c "$BG" && colort -l 80 "$BG" || colort -l -80 "$BG")"`
	- the same logic, but tinted further to make icons more bold, and a flag to top out at white or black.

![1](https://u.teknik.io/d90oe.png) | ![2](https://u.teknik.io/TQjth.png) | ![3](https://u.teknik.io/5rUdv.png)
------------------------------------|-------------------------------------|------------------------------------

If for some reason we wanted everything to have a blue tint, we can wrap both the above calls with a `colort -b 40`:

![1](https://u.teknik.io/TcvZm.png) | ![2](https://u.teknik.io/EVX9y.png) | ![3](https://u.teknik.io/swKON.png)
------------------------------------|-------------------------------------|------------------------------------

Input background colors used for the examples: `282828`, `AB4642`, `D8D8D8` from base16 colorsets.


### TODO

- consider accepting input from STDIN
- update the man page
