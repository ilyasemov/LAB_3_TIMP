#include "modAlphaCipher.h"

modAlphaCipher::modAlphaCipher(const std::string& skey)
{
    if (skey.empty())
        throw cipher_error("Empty key");
    for (int i=0; i<skey.length(); i++) {
        if (!isdigit(skey[i]))
            throw cipher_error(std::string("Invalid key ")+skey);
    }
    if (stoi(skey) == 1)
        throw cipher_error("WeakKey");
    if (stoi(skey)>0)
        key = stoi(skey);
    else
        throw cipher_error(std::string("Invalid key ")+skey);
}

std::string modAlphaCipher::encrypt(const std::string& open_text)
{
    string s = getValidOpenText(open_text);
    string n_s = s;
    int dl, nstrok, index, k;
    dl = s.length();
    nstrok = (dl - 1) / key + 1;
    k = 0;
    for (int i = key; i > 0; i--) {
        for (int j = 0; j < nstrok; j++) {
            index = i+key*j;
            if (index-1 < dl) {
                n_s[k] = s[index-1];
                k++;
            }
        }
    }
    return n_s;
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
    string s = getValidCipherText(cipher_text);
    string n_s = s;
    int dl, nstrok, index, k;
    dl = s.length();
    nstrok = (dl - 1) / key + 1;
    k = 0;
    for (int i = key; i > 0; i--) {
        for (int j = 0; j < nstrok; j++) {
            index = i+key*j;
            if (index-1 < dl) {
                n_s[index-1] = s[k];
                k++;
            }
        }
    }
    return n_s;
}

inline std::string modAlphaCipher::getValidOpenText(const std::string & s)
{
    std::string tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c))
                tmp.push_back(toupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

inline std::string modAlphaCipher::getValidCipherText(const std::string & s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (auto c:s) {
        if (!isupper(c))
            throw cipher_error(std::string("Invalid cipher text ")+s);
    }
    return s;
}
