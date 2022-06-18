#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cwctype>
#include <map>
#include <cmath>
#include <sstream>
#include <locale>
#include <codecvt>

using namespace std;
const map<wchar_t, wchar_t> lowercase =
{
    {L'А',L'а'},
    {L'Б',L'б'},
    {L'В',L'в'},
    {L'Г',L'г'},
    {L'Д',L'д'},
    {L'Е',L'е'},
    {L'Ё',L'е'},
    {L'Ж',L'ж'},
    {L'З',L'з'},
    {L'И',L'и'},
    {L'Й',L'й'},
    {L'К',L'к'},
    {L'Л',L'л'},
    {L'М',L'м'},
    {L'Н',L'н'},
    {L'О',L'о'},
    {L'П',L'п'},
    {L'Р',L'р'},
    {L'С',L'с'},
    {L'Т',L'т'},
    {L'У',L'у'},
    {L'Ф',L'ф'},
    {L'Х',L'х'},
    {L'Ц',L'ц'},
    {L'Ч',L'ч'},
    {L'Ш',L'ш'},
    {L'Щ',L'щ'},
    {L'Ъ',L'ь'},
    {L'Ы',L'ы'},
    {L'Ь',L'ь'},
    {L'Э',L'э'},
    {L'Ю',L'ю'},
    {L'Я',L'я'},
    {L'а',L'а'},
    {L'б',L'б'},
    {L'в',L'в'},
    {L'г',L'г'},
    {L'д',L'д'},
    {L'е',L'е'},
    {L'ё',L'е'},
    {L'ж',L'ж'},
    {L'з',L'з'},
    {L'и',L'и'},
    {L'й',L'й'},
    {L'к',L'к'},
    {L'л',L'л'},
    {L'м',L'м'},
    {L'н',L'н'},
    {L'о',L'о'},
    {L'п',L'п'},
    {L'р',L'р'},
    {L'с',L'с'},
    {L'т',L'т'},
    {L'у',L'у'},
    {L'ф',L'ф'},
    {L'х',L'х'},
    {L'ц',L'ц'},
    {L'ч',L'ч'},
    {L'ш',L'ш'},
    {L'щ',L'щ'},
    {L'ъ',L'ь'},
    {L'ы',L'ы'},
    {L'ь',L'ь'},
    {L'э',L'э'},
    {L'ю',L'ю'},
    {L'я',L'я'},
    {L' ',L' '}
};


wstring delete_rubish(const wstring& input) {
    wstring result;
    for (const auto& c : input) {
        if (lowercase.find(c) != lowercase.end()) {
            result.push_back(c);
        }
    }
    return result;
}

wstring lower_case(wstring input) {
    input = delete_rubish(input);
    for_each(input.begin(), input.end(), [&](wchar_t& c) {c = lowercase.at(c); });
    return input;
}
wstring parse(const wstring& input) {

    wstring low_input = lower_case(input);
    wstringstream ss;
    ss << low_input;
    wstring buf, result;
    while (!ss.eof())
    {
        ss >> buf;
        auto c = ss.peek();
        do {
            ss.ignore(1);
            c = ss.peek();
        } while (c == L' ');
        result += buf + L' ';
    }
    result.erase(result.end() - 1);
    return result;
}
void output_frequency(const map<wchar_t, size_t>& letter_counter) {
    for (const auto& p : letter_counter) {
        wcout << L"letter: " << p.first << L" consized: " << p.second << endl;
    }
}

//Количесвто каждой буквы, сначала беру первую букву слова и сравниваю с остальными, считая, 
//потом во 2 цикле удаляю эти буквы, взял два цикла чтоб не потеряться, если оптимизируешь то будет классно
auto letter_frequency(wstring input) {
    map <wchar_t, size_t> let_counter;
    for (const auto& c : input) {
        ++let_counter[c];
    }
    
    output_frequency(let_counter);
    return let_counter;
}

void output_bigram(const map<wstring, size_t>& bidram_counter) {
    for (const auto& p : bidram_counter) {
        wcout << L"Bigram: " << p.first << L" consized " << p.second << endl;
    }
}
auto bigram_count(wstring input) {
    map <wstring, size_t> bigram_counter;
    for (int i = 0; i < input.length() - 1; i++) {

        ++bigram_counter[input.substr(i, 2)];
    }
    output_bigram(bigram_counter);
    return bigram_counter;
}

double letter_probability( double text_size, double letter_count )
{
    return letter_count / text_size;
}

double entropy_term( double probability )
{
    return probability * log2( probability );
}

double letter_entrop( const wstring& input )
{
    auto parsed_input = parse( input );
    auto text_size = parsed_input.size();
    auto letters_count = letter_frequency( parsed_input );
    double result = 0;
    
    for ( const auto& pair_let_count : letters_count )
    {
        auto probability = letter_probability( text_size , pair_let_count.second );
        result += entropy_term( probability );
    }

    result *= -1;
    std::wcout << "H1 = ";
    return result;
}

double bigram_sum( const map<wstring, size_t>& bigrams )
{
    size_t dick = 0;
    for ( const auto& bigram : bigrams )
    {
        dick += bigram.second;
    }
    
    return dick;
}

double bigram_entrop( const wstring& input )
{
    auto parsed_input = parse( input );
    auto bigrams_count = bigram_count( parsed_input );
    auto all_bigrams = bigram_sum( bigrams_count );
    double result = 0;
    
    for ( const auto& pair_bigram_count : bigrams_count )
    {
        auto probability = letter_probability( all_bigrams, pair_bigram_count.second );
        result += entropy_term( probability );
    }

    result *= -1;
    
    return result;
}


int main()
{
    setlocale(LC_ALL, "");
    #ifdef _WIN32
    system("chcp 1251"); // настраиваем кодировку консоли
    #endif

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    wstring input;
    string line;
    //wcout << L"Введите текст на русском языке: ";
    std::ifstream fin( "./dead_souls.txt" );
    while (getline(fin, line, '\n') && !line.empty())
    {
        input += converter.from_bytes(line);
    }
    fin.close( );
    
    input = parse(input);
    wcout << input << endl;
    //letter_frequency(input);
    //bigram_count(input);

    wcout << letter_entrop( input ) << std::endl;
    auto entropia_bigrams = bigram_entrop( input );
    wcout << entropia_bigrams << std::endl;
    wcout << L"Result: H2 = " << entropia_bigrams / 2 << std::endl;
}

