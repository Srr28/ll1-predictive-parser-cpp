# LL(1) Predictive Parser in C++

A general-purpose **LL(1) Predictive Parser** implemented in C++. The parser accepts a context-free grammar through terminal input, computes FIRST and FOLLOW sets, constructs an LL(1) parsing table, and validates input strings using stack-based predictive parsing.

## Features

- **Grammar Input:** Accepts context-free grammar productions interactively through the terminal.
- **FIRST Set Calculation:** Computes FIRST sets using an iterative algorithm.
- **FOLLOW Set Calculation:** Computes FOLLOW sets using an iterative algorithm.
- **Parsing Table Construction:** Automatically generates the LL(1) predictive parsing table.
- **Stack-Based Parsing:** Simulates predictive parsing using a stack.
- **Input Validation:** Determines whether an input string belongs to the given grammar.
- **Parsing Trace:** Displays stack contents, remaining input, and parsing actions at every step.

## Algorithm Overview

The parser consists of four major stages:

1. **Grammar Processing**
   - Reads productions from standard input.
   - Identifies terminals and non-terminals.
   - Uses the first production's LHS as the start symbol.

2. **FIRST and FOLLOW Computation**
   - Computes FIRST sets for all non-terminals.
   - Computes FOLLOW sets using FIRST of subsequent symbols and FOLLOW propagation.
   - Handles epsilon productions.

3. **Predictive Parsing Table**
   - Constructs the parsing table using FIRST and FOLLOW.
   - Uses FIRST of a production's RHS to determine table entries.
   - Uses FOLLOW when a production can derive epsilon.

4. **String Parsing**
   - Initializes a stack with the start symbol and end marker.
   - Matches terminals against the input.
   - Expands non-terminals using the parsing table.
   - Accepts or rejects the input string.

## Grammar Notation

| Symbol | Meaning |
|---|---|
| `A`, `B`, `S` | Non-terminals (uppercase letters) |
| `a`, `b`, `c` | Terminals |
| `#` | Epsilon (ε) |
| `$` | End-of-input marker |
 
**Input format:** Each non-terminal is followed by its number of productions and the corresponding RHS strings.

## Example

Consider the grammar:

```text
S -> aAB
A -> bA | ε
B -> c
```

### Input

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

### Test String

```text
abbc
```

The parser calculates the FIRST and FOLLOW sets, generates the predictive parsing table, and simulates the parsing process.

Expected result:

```text
String ACCEPTED
```

## Compilation and Execution

### Prerequisites

- C++ compiler supporting C++17 or later.
- GCC or Clang.

### Compile

```bash
g++ -std=c++17 -O2 main.cpp -o parser
```

### Run

```bash
./parser
```

On Windows:

```powershell
g++ -std=c++17 -O2 main.cpp -o parser.exe
.\parser.exe
```

## Project Structure

```text
LL1-Predictive-Parser/
│
├── main.cpp
├── README.md
└── .gitignore
```

## Limitations

- Supports single-character terminals and non-terminals.
- Non-terminals must be uppercase letters.
- Does not automatically eliminate left recursion.
- Does not automatically perform left factoring.
- Assumes the grammar is suitable for LL(1) parsing.
- Does not currently provide explicit LL(1) conflict reporting.

## Concepts Demonstrated

- Context-Free Grammars (CFG)
- FIRST and FOLLOW sets
- LL(1) Predictive Parsing
- Top-Down Parsing
- Stack-Based Parsing
- Parsing Table Construction
- C++ STL (`unordered_map`, `set`, `map`, `stack`)

## Future Improvements

- Support multi-character grammar symbols.
- Detect and report LL(1) parsing conflicts.
- Automatic left-recursion elimination.
- Automatic left factoring.
- Improved parsing table visualization.
- Support grammar input from external files.
- More detailed error reporting and recovery.

## License

This project is licensed under the MIT License.
