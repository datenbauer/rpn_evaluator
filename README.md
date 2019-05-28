# rpn_evaluate

## Evaluate arithmetic expressions in Reverse Polish Notation (RPN) from the command line

[Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) is a way to express arithmetic expressions using postfix operators.<br> Expamples:
```
1 + 1 ==> 1 1 +
a/2 + (10^3) ==> a 2 / 10 3 ^ +
((12.5 * 3) - 5)^2 ==> 12.5 3 * 5 - 2 ^
```

This program evaluates RPN expressions and prints the result to the command line.

How to compile:
```C
gcc -o rpn_evaluate rpn_evaluate.c -lm
```

Usage:
```sh
$ ./rpn_evaluate 1 1 +
$ 2
```

Available operators:

* addition `+`
* subtraction `-`
* multiplication `*`
* division `/`
* power `^` (attention: exponent must be whole number!)

Operands may be whole numbers or rational numbers (with decimal dot).