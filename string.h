#include <iostream>
#include <cstring>

class String {

private:

    size_t sz = 0;
    size_t cap = 1;
    char *str = new char[1];

    size_t try_out(size_t x, size_t i, const String& substring) const {
        size_t sz_substring = substring.length();
        size_t count = 0;
        for (; ;i += x) {
            count++;
            bool flag = true;
            for (size_t j = 0; j < sz_substring; ++j) {
                if (str[i + j] != substring[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) return i;
            if (count == sz - sz_substring) break;
        }
        return sz;
    }

public:

    String() {}

    String(const char *c_style): sz(strlen(c_style)), cap(2 * sz + 1), str(new char[++cap]) {
        memcpy(str, c_style, sz);
    }

    String(char c): sz(1), cap(2), str(new char[1]){
        memset(str, c, 1);
    }

    String(size_t sz, char c = '\0'): sz(sz), cap(sz * 2 + 1), str(new char[++cap]) {
        memset(str, c, sz);
    }

    String(const String& s) : sz(s.sz), cap(s.cap), str(new char[s.sz]) {
        memcpy(str, s.str, sz);
    }

    String& operator=(const String& s) {
        if (*this == s){
            return *this;
        }
        else {
            delete[] str;
            str = new char[s.cap];
            sz = s.sz;
            cap = s.cap;
            memcpy(str, s.str, sz);
            return *this;
        }
    }

    ~String() {
        delete[]str;
    }

    size_t length() const {
        return sz;
    }

    void swap(String& s) {
        std::swap(sz, s.sz);
        std::swap(cap, s.cap);
        std::swap(str, s.str);
    }

    String& operator+=(char c) {
        push_back(c);
        return *this;
    }

    void push_back(char c) {
        if (sz + 1 >= cap) {
            cap *= 2;
            char *new_str = new char[cap];
            memcpy(new_str, str, sz);
            delete[] str;
            str = new_str;
        }
        str[sz] = c;
        sz++;
    }

    String& operator+=(const String& s) {
        if (sz + s.sz >= cap) {
            cap += s.cap;
            char *new_str = new char[cap];
            memcpy(new_str, str, sz);
            delete[] str;
            str = new_str;
        }
        for (size_t i = 0; i <= s.sz - 1; i++) {
            str[sz + i] = s[i];
        }
        sz += s.sz;
        return *this;
    }

    void pop_back() {
        if (sz == 0) return;
        sz--;
        if (sz * 2 <= cap) {
            cap /= 2;
            char *new_str = new char[cap];
            memcpy(new_str, str, sz);
            delete[] str;
            str = new_str;
        }
    }

    String substr(size_t start, size_t count) const {
        String s(count);
        std::copy(str + start, str + start + count, s.str);
        memcpy(s.str, str + start, count);
        return s;
    }

    size_t find(const String& substring) const{
        return try_out(1, 0, substring);
    }

    size_t rfind(const String& substring) const{
        return try_out(-1, sz - substring.length(), substring);
    }

    bool operator==(const String& s) {
        if (sz != s.sz) return 0;
        for (size_t i = 0; i < sz; i++) {
            if (str[i] != s[i])return 0;
        }
        return 1;
    }

    String operator+(const String& s) const {
        String new_str = *this;
        new_str += s;
        return new_str;
    }

    char& front() {
        return str[0];
    }

    const char& front() const {
        return str[0];
    }

    char& back() {
        return str[sz - 1];
    }

    const char& back() const {
        return str[sz - 1];
    }

    bool empty() const {
        return sz == 0;
    }

    void clear() {
        char *new_str = new char[1];
        delete[] str;
        str = new_str;
        sz = 0;
        cap = 1;
    }

    char& operator[](int index) {
        return str[index];

    }

    char operator[](int index) const{
        return str[index];
    }

};

String operator+(char c, String s){
    String new_str = c;
    new_str += s;
    return new_str;
}

std::istream& operator>>(std::istream& stream, String& str){
    str.clear();
    int c;
    while(((c = stream.get()) != '\n') && (!stream.eof()) && (!isspace(c))){
        str.push_back(char(c));
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const String& str){
    for (size_t i = 0; i < str.length(); i++)
        stream << str[i];
    return stream;
}
