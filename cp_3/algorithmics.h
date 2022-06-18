#pragma once
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

const std::vector<wchar_t> alphabet =
{
    L'а',L'б',L'в',L'г',L'д',L'е',L'ж',L'з',L'и',L'й',L'к',L'л',L'м',L'н',L'о',L'п',L'р',L'с',L'т',L'у',L'ф',L'х',L'ц',L'ч',L'ш',L'щ',L'ъ',L'ы',L'ь',L'э',L'ю',L'я'
};



const std::map<wchar_t, wchar_t> lowercase =
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
    {L'ы',L'ы'},
    {L'ь',L'ь'},
    {L'э',L'э'},
    {L'ю',L'ю'},
    {L'я',L'я'},
};


std::wstring
delete_rubish(const std::wstring& input) {
    std::wstring result;
    for (const auto& c : input) {
        if (lowercase.find(c) != lowercase.end()) {
            result.push_back(c);
        }
    }
    return result;
}

std::wstring
lower_case(std::wstring input) {
    input = delete_rubish(input);
    for_each(input.begin(), input.end(), [&](wchar_t& c) {c = lowercase.at(c); });
    return input;
}


size_t
numeric_difference_between_letters( size_t y, size_t x )
{
    if ( y >= x )
    {
        return y - x;
    }
    else
    {
        auto buf = x - y;
        return alphabet.size( ) - buf;
    }
}

size_t
modulo_substitute( size_t y, size_t x, size_t mod )
{
    if ( y >= x )
    {
        return ( y - x ) % mod;
    }
    else
    {
        auto buf = ( x - y ) % mod;
        return mod - buf;
    }
}


auto
bigram_count(const std::wstring& input) {
    std::map <std::wstring, size_t> bigram_counter;

    for (int i = 0; i < input.length() - 1; i += 2) {

        ++bigram_counter[input.substr(i, 2)];
    }

    return bigram_counter;
}

auto
top_bigrams( const std::wstring& input )
{
    const auto bigram_counter = bigram_count( input );
    std::multimap< size_t, std::wstring > top_of_bigrams;
    for ( const auto& p : bigram_counter )
    {
        top_of_bigrams.insert( { p.second, p.first } );
    }
    
    return top_of_bigrams;
}

std::vector<size_t>
dividers( size_t r )
{
    std::vector<size_t> divs;
    divs.reserve( std::sqrt( r ) );
    for (size_t i = 2; i <= r; i++)
    {
        if ( r % i == 0 )
        {
            divs.push_back( i );
        }
        
    }

    return divs; 
}

size_t
numeric_value_of_letter( wchar_t l )
{
    auto alphabet_position =  std::find( std::begin( alphabet ), std::end( alphabet ), l );
    auto val = std::distance(  std::begin( alphabet ), alphabet_position );
    return val;
}

size_t
numeric_value_of_letter( wchar_t l, const std::vector<wchar_t>& custom_alphabet )
{
    auto alphabet_position =  std::find( std::begin( custom_alphabet ), std::end( custom_alphabet ), l );
    auto val = std::distance(  std::begin( custom_alphabet ), alphabet_position );
    return val;
}

auto letter_frequency(std::wstring input) {
    std::map <wchar_t, size_t> let_counter;
    for (const auto& c : input) {
        ++let_counter[c];
    }
    
    return let_counter;
}

double letter_probability( double text_size, double letter_count )
{
    return letter_count / text_size;
}

int gcd(long long a, long long b) {//Алгоритм Стейна
    int d = 1;
    while ((a % 2 == 0) && (b % 2 == 0)) {
        b /= 2;
        a /= 2;
        d *= 2;
    }
    while (a % 2 == 0) {
        a /= 2;
    }
    while (b != 0) {
        while (b % 2 == 0) {
            b /= 2;
        }
        if (a <= b) {
            a = a;
            b = b - a;
        }
        else {
            int b1 = b;
            b = a - b;
            a = b1;
        }
    }
    d *= a;
    return d;
}

//Написанно по псевдокоду из Википедии
long long reverse(long long a, long long n) {
    if (a >= n)a %= n;
    long long t = 0, r = n, newt = 1, newr = a;
    while (newr != 0) {
        long long quotient = r / newr;
        long long newt1 = t;
        t = newt;
        newt = newt1 - quotient * newt;
        long long newr1 = r;
        r = newr;
        newr = newr1 - quotient * newr;
    }
    
    if( t < 0 )
    {
        t += n;
    }

    return t;
}

size_t
get_bigram_number( const std::wstring& bigram, std::vector<wchar_t> custom_alphabet )
{
    if ( bigram.size( ) != 2)
    {
        throw( "error value" );
    }
    
    auto x_i = numeric_value_of_letter( bigram[0], custom_alphabet );
         x_i *= custom_alphabet.size( );
         x_i += numeric_value_of_letter( bigram[1], custom_alphabet );

    return x_i;
}
