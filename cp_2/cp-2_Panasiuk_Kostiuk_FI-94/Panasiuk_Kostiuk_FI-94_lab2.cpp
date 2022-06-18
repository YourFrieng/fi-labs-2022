#include <iostream>
#include "VijinerEncoder.h"
#include "VijinerDecoder.h"



int main()
{
    setlocale(LC_ALL, "");
    #ifdef _WIN32
    system("chcp 1251"); // настраиваем кодировку консоли
    #endif

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring input;
    std::string line;
    std::ifstream fin;
    fin.open( "small copy.txt", std::ifstream::in );
    while (std::getline(fin, line, '\n') && !line.empty())
    {
        input += converter.from_bytes(line);
    }
    fin.close( );
    
    input = lower_case( input );

    std::wcout << input << std::endl;

    std::wcout << L"I" << 0 << " = " << VijinerDecoder::compliance_index( input ) << std::endl;

    for (size_t r = 2; r < 6; r++)
    {
        std::wcout << L"I" << r << " = " << VijinerDecoder::compliance_index( input, r ) << std::endl;
    }

    std::vector<size_t> r = VijinerDecoder::get_period_v( input );

    std::wcout << L"Method 1" << std::endl;
    for ( const auto& el : r)
    {
        std::wcout << el << std::endl;
        auto maybe_key = VijinerDecoder::get_key_variant1( input, L'о', el );
        std::wcout << maybe_key << std::endl;
    }

    std::wcout << L"Method 2" << std::endl;
    for ( const auto& el : r)
    {
        std::wcout << el << std::endl;
        auto maybe_key = VijinerDecoder::get_key_variant2( input, el );
        std::wcout << maybe_key << std::endl;
        std::wcout << VijinerDecoder::decode( input, maybe_key ) << std::endl;
    }
    

    return 0;
}
