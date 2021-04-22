# Concept of One Language

_One Programming Language_

**Stage:** lexer and parser

**Remaining work:** Operator analysis / data-type support / intermediate code generation

## Story

![](figure1.jpg)

(Thanks to https://app.diagrams.net/)

primitive but reflects the essence of what is needed. a universal structural unit for storing parsing elements. with all connections and the rules for their formation.
For example how and what to disassemble:
```
int32 a
itn32 a = 0
int32 a = previously defined_constant
```


I tired. for today it is enough to work with the TCC code. in short: this is a hard parsing machine - it is quite difficult to add a token that is not provided in advance. the rest of the principles of parsing the code are quite standard: the tree is built as the code is disassembled, the decision on a new branch is made by numerous ifs or branches (which greatly complicates the possibility of adding new types of tokens). some implementations seemed strange, for example skip ("(") instead of just next () or two skip ("("); skip ("("); which strictly requires the presence of double brackets in the parsed code (to which it does not apply).

Only an idea can be applied to it, the rest will have to be rewritten. this code is not adaptable.
development will have to start with structures like TCCState.

This is the fourth start from scratch.

© Copyright 2020 Max Base, Val K
