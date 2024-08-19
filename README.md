# LLDBF
A Brainf*ck inspired, interpreted language using signed 64bit cells (or whatever long long int will be on your machine) and a 2-element stack. Numbers can be entered as literals in the source code.

## Usage
LLDBF is inspired by BF and some of its dialects. In fact, any non-wrapping BF code should work as is, but no guarantee. The similarities, diffrences and extensions are as follows:

The usual BF commands work as expected:

`+` increase the current cells value by 1

`-` decrease the current cells value by 1

`>` go to next cell

`<` go to previous cell

`[` enter loop if current cells value is > 0, else skip it

`]` leave loop if current cells value is <= 0, else repeat it

`.` print current cells value as char

`,` get number as user input from stdin


&nbsp;


In addition there are the following commands:

`#` print current cells value as number

`^` push current cells value on the stack (leaves cell unchanged)

`v` pop top stack item in current cell

`a` add the numbers on the stack

`s` subtract top stack item from bottom one

`m` multiply the numbers on the stack

`d` divide bottom stack item by top one (integer division like / in C)

`r` modulus of bottom stack item and top one

## Integer literals
You can set the current cell to a certain value by just using the number in the source code. A trivial example would be the following "Hello, World!" implementation, which just uses the same cell over and over to print the characters one by one and a final new line:

`72.101.108..111.44.32.87.111.114.108.100.33.10.`
### Negative numbers
If you want to put a negative number in a cell (and because '-' is already used as a decrement operator), you need to use a little workaround for now. You can either multiply the number by -1 like so: `1234^0-^mv` or you can subtract it from 0 like so: `0^1234^sv`. When you can be sure that the stack is empty (i.e. it consists of 0s), you may also just do `1234^sv`.

## The stack
The stack can hold up to two numbers, which can be pushed to the stack using `^`. The top stack item can be popped with `v`, after which the bottom item becomes the new top item (last in, first out). For example, if the current tape has the values 2, 3 in the first two cells, the pointer is at the first cell and we execute the sequence `^>^>v>v`, the first four cells will now be 2, 3, 3, 2.

If more than two numbers are pushed to the stack, the bottom one will be discarded.

### Stack arithmetics:
You can use the stack to quickly get the sum, difference, product, quotient or modulus of two numbers. Both stack items will be consumed by the operation and the result will be the new top stack item:

| Stack before | Operation | Stack after |
| ------------ | --------- | ----------- |
| 14 3         | a         | 0 17        |
| 14 3         | s         | 0 11        |
| 14 3         | m         | 0 42        |
| 14 3         | d         | 0 4         |
| 14 3         | r         | 0 2         |

## Some practical examples
### Hello, World!
`72.101.108..111.44.32.87.111.114.108.100.33.10.` (Same as above)
### Factorial of n (taking n as user input)
`0>,[^>v-]1<[^<^mv]>#10.`
### Print the first n Fibonacci numbers (n as user input)
`,>0>1<<[>^^#32.v>^>v<^av>^<<v<-]10.`
### Solutions for the first three Project Euler problems:
`0>1000[>1[<-^>3^rv<^>>5^r<^mv]<^<^av>]<#10.`

`0>1>1>1[[<^^>v<<^>av>^^<<v>>2^rv]<<^<^av>>>4000000^<^>sv]<<<#10.`

`600851475143>3>1[<<^>^>rv[<++<^>^>rv]<<^>^<dv^>>1^sv]<#10.`
