#include "algorithmics.h"
class VijinerEncoder
{
public:
    static void set_key( std::wstring&& );
    static std::wstring encode( const std::wstring& );
private:
    static std::wstring key;
};

std::wstring VijinerEncoder::key = L"";

void
VijinerEncoder::set_key( std::wstring&& key_in )
{
    key = key_in;
}


std::wstring
VijinerEncoder::encode( const std::wstring& original_text )
{
    std::wstring encoded_text;
    std::wstring clear_original_text = lower_case( original_text );

    encoded_text.reserve( clear_original_text.size() );

    const static auto alphabet_size = alphabet.size( );

    for (size_t i = 0; i < clear_original_text.size(); i++)
    {
        if ( clear_original_text[i] == L' ' )
        {
            //encoded_text.push_back( L' ' );
            continue;
        }
        
        auto letter_numeric = numeric_value_of_letter( clear_original_text[i] );
        auto key_letter_numeric = numeric_value_of_letter(key[i % key.size()] );
        auto numeric_new_letter = ( letter_numeric + key_letter_numeric ) % alphabet_size;
        wchar_t new_letter = alphabet[ numeric_new_letter ];
        encoded_text.push_back( new_letter );
    }

    return encoded_text;
    
}