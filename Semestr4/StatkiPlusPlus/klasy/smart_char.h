#ifndef SMART_CHAR_H
#define SMART_CHAR_H

struct smart_char
{
private:
    char znak {'a'};

public:
    smart_char(){ znak = 'a';};

    smart_char& operator++()
    {
        switch (znak)
        {
        case 'a': znak = 'b'; break;
        case 'b': znak = 'c'; break;
        case 'c': znak = 'd'; break;
        case 'd': znak = 'e'; break;
        case 'e': znak = 'f'; break;
        case 'f': znak = 'g'; break;
        case 'g': znak = 'h'; break;
        case 'h': znak = 'i'; break;
        case 'i': znak = 'j'; break;
        case 'j': znak = 'k'; break;
        case 'k': znak = 'l'; break;
        case 'l': znak = 'm'; break;
        case 'm': znak = 'n'; break;
        case 'n': znak = 'o'; break;
        case 'o': znak = 'p'; break;
        case 'p': znak = 'q'; break;
        case 'q': znak = 'r'; break;
        case 'r': znak = 's'; break;
        case 's': znak = 't'; break;
        case 't': znak = 'u'; break;
        case 'u': znak = 'v'; break;
        case 'v': znak = 'w'; break;
        case 'w': znak = 'x'; break;
        case 'x': znak = 'y'; break;
        case 'y': znak = 'z'; break;
        case 'z': znak = 'A'; break;
        case 'A': znak = 'B'; break;
        case 'B': znak = 'C'; break;
        case 'C': znak = 'D'; break;
        case 'D': znak = 'E'; break;
        case 'E': znak = 'F'; break;
        case 'F': znak = 'G'; break;
        case 'G': znak = 'H'; break;
        case 'H': znak = 'I'; break;
        case 'I': znak = 'J'; break;
        case 'J': znak = 'K'; break;
        case 'K': znak = 'L'; break;
        case 'L': znak = 'M'; break;
        case 'M': znak = 'N'; break;
        case 'N': znak = 'O'; break;
        case 'O': znak = 'P'; break;
        case 'P': znak = 'Q'; break;
        case 'Q': znak = 'R'; break;
        case 'R': znak = 'S'; break;
        case 'S': znak = 'T'; break;
        case 'T': znak = 'U'; break;
        case 'U': znak = 'V'; break;
        case 'V': znak = 'W'; break;
        case 'W': znak = 'X'; break;
        case 'X': znak = 'Y'; break;
        case 'Y': znak = 'Z'; break;
        case 'Z': znak = 'a'; break;
        default: znak = 'a'; break;
        }
        return *this;
    };
    smart_char operator++(int)
    {
        smart_char temp = *this;
        ++*this;
        return temp;
    };
    friend std::ostream& operator<< (std::ostream& os, const smart_char& obj)
    {
        os << obj.znak;
        return os;
    };
};

#endif // SMART_CHAR_H
