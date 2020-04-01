#include "token.h"

#include <stdexcept>

using namespace std;

vector<Token> Tokenize(istream &cl) {
    vector<Token> tokens;

    char c;
    while (cl >> c) {
        if (isdigit(c)) {
            string date(1, c);
            for (int i = 0; i < 3; ++i) {
                while (isdigit(cl.peek())) {
                    date += cl.get();
                }
                if (i < 2) {
                    date += cl.get(); // Consume '-'
                }
            }
            tokens.push_back({date, TokenType::DATE});
            continue;
        }

        string event;
        switch (c) {
            case '"':
                getline(cl, event, '"');
                tokens.push_back({event, TokenType::EVENT});
                break;
            case 'd':
                if (cl.get() == 'a' && cl.get() == 't' && cl.get() == 'e') {
                    tokens.push_back({"date", TokenType::COLUMN});
                } else {
                    throw logic_error("Unknown token");
                }
                break;
            case 'e':
                if (cl.get() == 'v' && cl.get() == 'e' && cl.get() == 'n' &&
                    cl.get() == 't') {
                    tokens.push_back({"event", TokenType::COLUMN});
                } else {
                    throw logic_error("Unknown token");
                }
                break;
            case 'A':
                if (cl.get() == 'N' && cl.get() == 'D') {
                    tokens.push_back({"AND", TokenType::LOGICAL_OP});
                } else {
                    throw logic_error("Unknown token");
                }
                break;
            case 'O':
                if (cl.get() == 'R') {
                    tokens.push_back({"OR", TokenType::LOGICAL_OP});
                } else {
                    throw logic_error("Unknown token");
                }
                break;
            case '(':
                tokens.push_back({"(", TokenType::PAREN_LEFT});
                break;
            case ')':
                tokens.push_back({")", TokenType::PAREN_RIGHT});
                break;
            case '<':
                if (cl.peek() == '=') {
                    cl.get();
                    tokens.push_back({"<=", TokenType::COMPARE_OP});
                } else {
                    tokens.push_back({"<", TokenType::COMPARE_OP});
                }
                break;
            case '>':
                if (cl.peek() == '=') {
                    cl.get();
                    tokens.push_back({">=", TokenType::COMPARE_OP});
                } else {
                    tokens.push_back({">", TokenType::COMPARE_OP});
                }
                break;
            case '=':
                if (cl.get() == '=') {
                    tokens.push_back({"==", TokenType::COMPARE_OP});
                } else {
                    throw logic_error("Unknown token");
                }
                break;
            case '!':
                if (cl.get() == '=') {
                    tokens.push_back({"!=", TokenType::COMPARE_OP});
                } else {
                    throw logic_error("Unknown token");
                }
                break;
            default:
                continue;
        }
    }

    return tokens;
}