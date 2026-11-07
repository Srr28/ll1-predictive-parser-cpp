# LL(1) Predictive Parser in C++

A general-purpose LL(1) predictive parser implemented in C++. It computes FIRST and FOLLOW sets, constructs a predictive parsing table, and validates input strings using stack-based parsing.

## Features

- Interactive grammar input
- FIRST set computation
- FOLLOW set computation
- LL(1) predictive parsing table construction
- Stack-based parsing with a step-by-step trace
- Detection of parsing-table conflicts

## Grammar notation and constraints

- Non-terminals: single uppercase characters (`S`, `A`, `B`)
- Terminals: single characters (`a`, `b`, `+`, `*`)
- Epsilon: `#`
- End-of-input marker: `$` (added automatically)
- The first non-terminal entered is the start symbol.
- The grammar must not require automatic left-recursion elimination or left factoring.

## Input format

Enter the number of non-terminals. For each non-terminal, enter its name, number of productions, and then each RHS production as a string.

Example grammar:

```text
S -> aAB
A -> bA | #
B -> c
```

Terminal input:

```text
3
S 1
aAB
A 2
bA
#
B 1
c
```

Example test string:

```text
abbc
```

Expected result:

```text
String ACCEPTED
```

## Build and run

Requires a C++17-compatible compiler (GCC or Clang).

### Linux

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o parser
./parser
```

### Windows (MinGW)

```powershell
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o parser.exe
.\parser.exe
```

## Project structure

```text
ll1-predictive-parser-cpp/
├── main.cpp
├── README.md
└── .gitignore
```

## Limitations

- Supports single-character grammar symbols.
- Non-terminals must be uppercase characters.
- Does not automatically eliminate left recursion.
- Does not automatically perform left factoring.
- Reports a conflict if multiple productions occupy the same parsing-table cell.

## Concepts

Context-Free Grammars, FIRST and FOLLOW sets, LL(1) parsing, top-down parsing, predictive parsing tables, and stack-based parsing.

## License

MIT
