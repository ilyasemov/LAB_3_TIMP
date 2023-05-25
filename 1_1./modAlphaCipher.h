#pragma once
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
    std::string numAlpha = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
    std::string numalpha = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec; //кодек UTF-8
    wstring ws = codec.from_bytes(numAlpha);
    std::wstring wa = codec.from_bytes(numalpha);
    std::map <char,int> alphaNum; //ассоциативный массив "номер по символу"
    std::vector <int> key; //ключ
    std::vector<int> convert(const std::string& s); //преобразование строка-вектор
    std::string convert(const std::vector<int>& v); //преобразование вектор-строка
    std::string getValidOpenText(const std::string & s);
    std::string getValidCipherText(const std::string & s);
    std::string getValidKey(const std::string & s);
public:
    modAlphaCipher(const std::string& skey); //конструктор для установки ключа
    std::string encrypt(const std::string& open_text); //зашифрование
    std::string decrypt(const std::string& cipher_text);//расшифрование
};

class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
