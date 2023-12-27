#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <chrono>


using namespace std;

vector<string> reservedWords = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
        "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
        "class", "compl", "concept", "const", "consteval", "constexpr", "const_cast",
        "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
        "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
        "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
        "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
        "requires", "return", "short", "signed", "sizeof", "static", "static_assert",
        "static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
        "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
};

vector<string> operators = {
        "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "++", "--", "+=", "-=",
        "*=", "/=", "%=", "<<", ">>", "&=", "|=", "^=", "~", "!", "&&", "&", "|", "||", "?", ":", "::",
        "->", "[", "]","(", ")", "{", "}", "&", "*"
};

vector<string> separators = { ";", ",", "." };

bool isReservedWords(const string& token) {
    auto is = find(reservedWords.begin(), reservedWords.end(), token);
    return is != reservedWords.end();
}

bool isOperator(const string& token) {
    auto is = find(operators.begin(), operators.end(), token);
    return is != operators.end();
}

bool isSeparator(const string& token) {
    auto is = find(separators.begin(), separators.end(), token);
    return is != separators.end();
}


int main() {
    unordered_map<string, int> identifiersCount, operatorsCount, reservedWordsCount, separatorsCount;
    string currentToken = "";
    cout << "Enter the source file directory + file name (e.g., C:\\CSE0405\\main.cpp): ";
    string filename;
    getline(cin, filename);
    cout << "Entered file directory + file name: " << filename << endl;
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return 1;
    }
    string line;
    int lineCount = 0;
    auto start_time = chrono::high_resolution_clock::now();

    while (getline(inputFile, line)) {
        lineCount++;

        for (size_t i = 0; i < line.length(); ++i) {
            char ch = line[i];
            //Comment handling '//'
            if (ch == '/' && line[i + 1] == '/') {
                break;
            }
            // Multi-line comment handling /* */
            if (ch == '/' && line[i + 1] == '*') {
                i += 2;  // Skip the '/*'

                while (true) {
                    size_t found = line.find("*/", i);
                    if (found != string::npos) {
                        i = found + 2;  // Skip the '*/'
                        break;  // Exit the loop once the end of the multiline comment is found
                    }
                    if (!getline(inputFile, line)) {
                        cerr << "Error" << endl;
                        return 1;
                    }
                    lineCount++;
                    i = 0;
                }
                continue;
            }
            //String Handling
            if (ch == '"') {
                i += 1;
                while (line[i] != '"') {
                    if (line[i] == '\'') {
                        i++;
                        break;
                    }
                    i++;
                }
                ch = line[i];
            }

            //Single comma handling
            if (ch == '\'') {
                i += 1;
                if (line[i + 1] == '\'' && line[i + 2] == '\'') {
                    i += 3;
                }
                else if (line[i + 1] == '\'') {
                    i += 2;
                }
                ch = line[i];
            }
            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
                continue;
            }
            else if (isOperator(string(1, ch)) || isSeparator(string(1, ch))) {
                if (isSeparator(string(1, ch))) {
                    separatorsCount[string(1, ch)]++;
                }
                /*else if (isReservedWords(string(1, ch))) {
                    reservedWordsCount[string(1, ch)]++;
                }*/
                else if (isOperator(string(1, ch))) {
                    string chNext = "";
                    chNext += line[i + 1];
                    currentToken += string(1, ch) + chNext;
                    if (isOperator(currentToken)) {
                        operatorsCount[currentToken]++;
                        i++;
                        currentToken = "";
                        continue;
                    }
                    currentToken = "";
                    operatorsCount[string(1, ch)]++;
                }
            }
            else {
                currentToken += ch;
                if (currentToken == "#include") continue;
                if (i + 1 < line.length() && (isalnum(line[i + 1]) || line[i + 1] == '_')) {
                    continue;
                }
                if (isReservedWords(currentToken)) {
                    reservedWordsCount[currentToken]++;
                }
                else if (isalpha(currentToken[0])) {
                    identifiersCount[currentToken]++;
                }
                currentToken = "";
            }
        }
    }

    int subTotal = 0, grandTotal = 0;
    cout << "\n------------------------------\n" << endl;
    cout << "********* Identifiers *********\n" << endl;
    for (const auto& pair : identifiersCount) {
        cout << pair.first << " : " << pair.second << endl;
        subTotal += pair.second;
    }
    cout << "\nSubtotal: " << subTotal << endl;
    grandTotal += subTotal;
    subTotal = 0;
    cout << "\n------------------------------\n" << endl;
    cout << "********* Reserved Words *********\n" << endl;
    for (const auto& pair : reservedWordsCount) {
        cout << pair.first << " : " << pair.second << endl;
        subTotal += pair.second;
    }
    cout << "\nSubtotal: " << subTotal << endl;
    grandTotal += subTotal;
    subTotal = 0;
    cout << "\n------------------------------\n" << endl;
    cout << "********* Operators *********\n" << endl;
    for (const auto& pair : operatorsCount) {
        cout << pair.first << " : " << pair.second << endl;
        subTotal += pair.second;
    }
    cout << "\nSubtotal: " << subTotal << endl;
    grandTotal += subTotal;
    subTotal = 0;
    cout << "\n------------------------------\n" << endl;
    cout << "********* Seperators *********\n" << endl;
    for (const auto& pair : separatorsCount) {
        cout << pair.first << " : " << pair.second << endl;
        subTotal += pair.second;
    }
    cout << "\nSubtotal: " << subTotal << endl;
    cout << "\n------------------------------\n" << endl;
    grandTotal += subTotal;
    cout << "Total Number of Lines: " << lineCount << endl;
    cout << "Lexemes Grand Total: " << grandTotal << endl;
    cout << "\n------------------------------\n" << endl;
    subTotal = 0;
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Runtime: " << duration.count() << " ms\n";

    return 0;
}