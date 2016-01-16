## colort[int]

A small program for 'tinting' colors by values.

``` sh
$ colort -t 2 -c "#000000"
#222222
$ colort -l upper -t 2 -c "#ffffff"
#ffffff
```


### TODO ###

- [x] add --upper and --lower flags to set boundries (eg `colort --upper 3 "ffffff" --> ffffff`)
	- [  ] should this be automatic depending on tint direction?
- [ ] make values be toggled on their own (eg `colort 1 000000 --> 010101`)
- [x] proper args and usage
- [ ] --invert option.
