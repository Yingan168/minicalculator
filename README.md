# mini calculator

This project is a simple calculator written in C that can evaluate math expressions typed by the user.  
It supports parentheses `()`, operator priority (`+`, `-`, `*`, `/`, `^`), negative numbers, and decimal numbers.

---

##  How It Works

### 1. Input Handling
- The user types in a normal math expression like:  
  `(3 + 5) * 2 - 4 / 2`
- The input is read as a **string**.

### 2. Infix to Postfix Conversion
- It work by convert the input from **infix** format (what we write normally) to **postfix** format.
- Example:  
  Infix: `(3 + 5) * 2`  
  Postfix: `3 5 + 2 *`

### 3. Postfix Evaluation
- We evaluate the postfix expression using a **stack**.
- Each number is pushed into the stack.
- When we see an operator, we pop two numbers, do the calculation, and push the result back.

---

## Stack Usage

We use **two stacks**:

1. **Operator Stack** (for +, -, *, /, ^)  
   - Helps with checking precedence and order when converting infix to postfix.

2. **Value Stack** (for numbers)  
   - Helps in evaluating the postfix expression.

---

## File Structure

| File            | Purpose |
|-----------------|---------|
| `main.c`        | This is the main program. It shows the user interface and handles input/output. |
| `calculator.c`  | This file contains all the logic: converting to postfix, calculating results, and stack operations. |
| `calculator.h`  | This is a header file. It tells the compiler what functions are available in `calculator.c`. It helps `main.c` to use them. |

---

## How to Run

```bash
gcc main.c calculator.c -o calculator -lm
```
3. Run the program:

```bash
./calculator
```

---

## Sample Test Cases

| Input                   | Output |
|------------------------|--------|
| `(3 + 5) * 2 - 4 / 2`   | `14`   |
| `3 + 5 * 2`             | `13`   |
| `2 ^ 3 + 4`             | `12`   |
| `-3 + 5`                | `2`    |
| `3.5 + 2.1 * 4`         | `11.9` |

---

## Error Handling

- Shows error if:
  - Parentheses don’t match
  - Invalid symbols are typed
  - Division by zero
  - Incorrect expression (like `5 + * 3`)

---

## Why Use 3 Files?

Using three files helps keep the project organized and clean:

- `main.c` → handles what the user sees and types
- `calculator.c` → does the hard work behind the scenes
- `calculator.h` → connects the two by declaring shared functions

This makes your code easier to read, debug, and reuse.

---
