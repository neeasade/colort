## colort[int]

A small program for 'tinting' colors by values.

``` sh
$ colort 2 "#000000"
#222222
$ colort -l 2 "#ffffff"
#ffffff
```

The `-l` option 'limits' color tinting by not letting it cycle.


### TODO ###

- [x] add --upper and --lower flags to set boundries (eg `colort --upper 3 "ffffff" --> ffffff`)
	- [x] should this be automatic depending on tint direction? it should be.
- [ ] make values be toggled on their own (eg `colort 1 000000 --> 010101`)
	- This would mean color/pattern validation, as currently we just iterate on characters that /could/ be in a color.
- [ ] proper args and usage
- [ ] --invert option.
