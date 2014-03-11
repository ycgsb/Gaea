#ifndef CHARACTER_HPP
#define CHARACTER_HPP


namespace ycg {

class Character {
public:
    static bool isDigit(char ch);
    static bool isLetter(char ch);
    static bool isLowerCase(char ch);
    static bool isUpperCase(char ch);
    static bool isWhitespace(char ch);
    static char toLower(char ch);
    static char toUpper(char ch);
};

inline bool Character::isDigit(char ch) {
    return (ch >= '0') && (ch <= '9');
}

inline bool Character::isLetter(char ch) {
    return  (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

inline bool Character::isLowerCase(char ch) {
    return (ch >= 'a' && ch <= 'z');
}

inline bool Character::isUpperCase(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}

inline bool Character::isWhitespace(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}

inline char Character::toLower(char ch) {
    if (isUpperCase(ch)) {
        char lower = ch - 'A' + 'a';
        return lower;
    } else {
        return ch;
    }
}

inline char Character::toUpper(char ch) {
    if (isUpperCase(ch)) {
        char lower = ch - 'A' + 'a';
        return lower;
    } else {
        return ch;
    }
}

}  // namespace ycg

#endif // CHARACTER_HPP
