#ifndef STRING_H
#define STRING_H
#include <iostream>
using std::ostream;
using std::istream;

class String {
    friend ostream &operator<<(ostream &, const String &);
    friend istream &operator>>(istream &, String &);

    public:
        // construtor de conversão de string para
        // array de char
        String (const char * = "");
        String (const String &);
        ~String();

        const String &operator=(const String &);
        const String &operator+=(const String &);

        bool operator!() const;
        bool operator==(const String &) const;
        bool operator<(const String &) const;

        bool operator!=(const String &right) const {
            return !(*this == right);
        }

};

#endif