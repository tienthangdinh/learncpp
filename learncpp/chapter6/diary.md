# operator precedence & associativity
- precedence: priority level
- of all have same precedence level: associativity tell if that operator L->R or R->L

- precedence levels: 1-17
- associativity L->R, R->L

e.g R->L rule:
- address of: &
- dereference: *

# 6.2 arithmetic operator
- binary operator: +-*/ , take both left and right operands
- if u want to divide two integer, static_cast them into float first

## arithmetic assignment:
`x*=y; x+=y; x-=y; x/=y;`

# 6.4 increment/decrement operator
- `++x` return  new x
- `x++`return old x

# 6.6 conditional operator
`result = (a > b) ? result + 1 : result - 1;`