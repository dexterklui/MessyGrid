# Programming style

Follow mostly the requirement for assignments. For others which are unspecified
follow Google C++ styling (as recommended by the course, I guess...)

## Naming Style

### Files

All letters in lower case with underscore, e.g. `my_code.cpp`.


### Variables

All letters in lower case with underscore, e.g. `my_var`.

### Constants

Either all letters in uppercase, e.g. `PI`; or  
Starts with "k" followed by mixed case, e.g. `kMyConstant`.

### Functions

In mixed case, e.g. `MyFunction()`.

---

## Comment Styles

### comment Format

Use `//` rather than `/* */`.

For in-line comment `//` should be separated from the code by two spaces.

### Function Comments

**Function declarations** are in header files. Before each declaration there is a
comment specifying:

* What the function does (without describing how the function does it)
* What are the inputs (if any)
* What is the output (if any)

We adopt the commenting styles of the assignments' templates:  

```C++
// Function: [Description of the function]
// Input: int a: [description]
//        int b: [description]
// Output: int: [description]
```

Before **function definition** we may add a comment if it is required to explain
some nuanced details or tricks in the function implementation.

---

## Formatting Style

### Indentation and spacing

* Use **space** rather than tab for indentation and horizontal spacing.
* Use two spaces for each indentation level.
* Leave no trailing spaces.

### Function Definitions

Unlike other compound statements, in function definition open brace starts at
the next line.

```C++
int IsEven(int i)
{
  // function body
}
```

### Conditionals

If there is only one branch (no else) AND if the body has only one statement:

```C++
if (x > 2)
  cout << "x is bigger than 2." << endl;
```

However, if there are multiple branches, or if the body has more than one
statement, use braces to enclose the body.

```C++
if (x > 0) {
  cout << "x is positive." << endl;
}
else if (x < 0) {
  cout << "x is negative." << endl;
}
else {
  cout << "x is zero." << endl;
}
```

### Loops

```C++
for (int i = 0; i < 10; ++i) {
  // loop body
}
```

```C++
do {
  cout << x << ' ';
  ++x;
} while (x < 10);
```

### Switch

```C++
switch (grade) {
  case 'A':
    cout << "Excellent!" << endl;
    break;
  case 'B':
    cout << "Great!" << endl;
    break;
  case 'C':
    cout << "Not bad." << endl;
    break;
  case 'D':  // empty body: no need to comment that this case falls through
  case 'E':
    cout << "You can do better." << endl;
    break;
  case 'F':
    cout << "Failed." << endl;
    // fall through intended (comment explicitly that this case falls through)
  default:
    cout << "Try again." << endl;
}
```
