#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
#include <iostream>
#include <cctype>
using namespace std;
class modAlphaCipher
{
private:
    int key;
    std::string getValidOpenText(const std::string & s);
    std::string getValidCipherText(const std::string & s);
public:
    modAlphaCipher()=delete;
    modAlphaCipher(const string& key1);
    std::string encrypt(const std::string& open_text);
    std::string decrypt(const std::string& cipher_text);
};

class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
