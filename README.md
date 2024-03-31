# Lexical Analyzer

This C++ program analyzes the number of identifiers, reserved words, operators, and separators in a given C++ source file. The program prompts the user for the directory and name of the source file, then reads the source file and counts different types of lexical elements.

## Usage

Using the program is straightforward. Firstly, the program will ask for the directory and filename of the C++ source file. After obtaining this information from the user, it reads the source file and counts the lexical elements.
```bash
./LexicalAnalyzer
Enter the source file directory + file name (e.g., C:\CSE0405\main.cpp): C:\path\to\your\file.cpp
Entered file directory + file name: C:\path\to\your\file.cpp
```

## Results

Example:
```bash
int main() {
    cout << "Hello, world!";
    return 0;
}
```

Example output:
```bash
------------------------------

********* Identifiers *********

main : 1

Subtotal: 1

------------------------------

********* Reserved Words *********

return : 1
int : 1
cout: 1

Subtotal: 3

------------------------------

********* Operators *********

<< : 1

Subtotal: 1

------------------------------

********* Separators *********

{ : 1
} : 1
( : 1
) : 1
; : 2

Subtotal: 6

------------------------------

Total Number of Lines: 4
Lexemes Grand Total: 11

------------------------------

Runtime: 23 ms

