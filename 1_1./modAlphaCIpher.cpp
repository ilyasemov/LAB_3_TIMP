#include "modAlphaCipher.h"
modAlphaCipher::modAlphaCipher(const std::string& skey)
{
    for (unsigned i=0; i<ws.size(); i++) {
        alphaNum[ws[i]]=i;  //map
    }
    key = convert(getValidKey(skey)); 
    int n = 0; //заплатка их методички
    for (auto e:key) {
        if (e==0)
            n++;
    }
    if (2*n > key.size())
        throw cipher_error("WeakKey");

}

std::string modAlphaCipher::encrypt(const std::string& open_text) //зашифровка
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

inline std::vector<int> modAlphaCipher::convert(const std::string& s) 
{
    std::vector<int> result;
    wstring w_s = codec.from_bytes(s); // перекодируем
    for (unsigned i=0; i<w_s.size(); i++) {
        result.push_back(alphaNum[w_s[i]]); //мап в вектор
    }
    return result;
}

inline std::string modAlphaCipher::convert(const std::vector<int>& v)
{
    std::string result;
    wstring result_s = codec.from_bytes("");
    for (unsigned i=0; i<v.size(); i++) {
        result_s.push_back(ws[v[i]]);
    }
    result = codec.to_bytes(result_s);
    return result;
}

inline std::string modAlphaCipher::getValidKey(const std::string & s)
{
    if (s.empty())
        throw cipher_error("Empty key");
    std::locale loc("ru_RU.UTF-8");
    std::wstring tmp = codec.from_bytes(s);
    for(int i = 0; i < tmp.size(); i++) {
        if (wa.find(tmp[i]) != string::npos) {
            tmp[i] = toupper(tmp[i], loc);
        }
        if (ws.find(tmp[i]) == string::npos)
            throw cipher_error(std::string("Invalid key ")+s);
    }
    string tmp1 = codec.to_bytes(tmp);
    return tmp1;
}

inline std::string modAlphaCipher::getValidOpenText(const std::string & s)
{
    std::locale loc("ru_RU.UTF-8");
    std::wstring tmp = codec.from_bytes(s);
    std::wstring n_tmp;
    for(int i = 0; i < tmp.size(); i++) {
        if (wa.find(tmp[i]) != string::npos) {
            n_tmp.push_back(toupper(tmp[i], loc));
        }
        if (ws.find(tmp[i]) != string::npos)
            n_tmp.push_back(tmp[i]);
    }
    string tmp1 = codec.to_bytes(n_tmp);
    if (tmp1.empty())
        throw cipher_error("Empty text");
    return tmp1;
}

inline std::string modAlphaCipher::getValidCipherText(const std::string & s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    std::locale loc("ru_RU.UTF-8");
    std::wstring tmp = codec.from_bytes(s);
    for(int i = 0; i < tmp.size(); i++) {
        if (ws.find(tmp[i]) == string::npos)
            throw cipher_error(std::string("Invalid cipher text ")+s);
    };
    return s;
}
