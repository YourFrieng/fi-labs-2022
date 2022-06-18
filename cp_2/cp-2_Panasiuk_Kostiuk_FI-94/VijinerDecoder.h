#include "algorithmics.h"
#include <fstream>
class VijinerDecoder
{
public:
    static std::wstring get_key_variant2( const std::wstring& Y, size_t r );
    static std::wstring decode( const std::wstring& Y, const std::wstring& key );
    //I(Y)
    static double compliance_index( const std::wstring& );
    //I_r(Y_r)
    static double compliance_index( const std::wstring& Y, size_t r );
    //D_r
    static double same_pares_counter( const std::wstring& Y, size_t r );
    static size_t get_period( const std::wstring& );
    static std::vector<size_t> get_period_v( const std::wstring& );
    static std::wstring get_key_variant1( const std::wstring& Y, wchar_t x, size_t r );
    static std::vector<std::wstring> get_Y_blocks( const std::wstring& Y, size_t r );
};

std::vector<std::wstring>
VijinerDecoder::get_Y_blocks( const std::wstring& Y, size_t r )
{
    std::vector<std::wstring> blocks;
    blocks.reserve( r );
    std::wstring block_of_r;
    block_of_r.reserve( ( Y.size( ) / r )  + 1 );
    
    size_t letter_for_read_index = 0;
    for (size_t i = 0; i < r; i++)
    {
        letter_for_read_index = i;
        while ( letter_for_read_index <= Y.size() )
        {
            block_of_r.push_back( Y[letter_for_read_index] );
            letter_for_read_index += r;
        }
        blocks.push_back( block_of_r );
        block_of_r.clear();
    }
    return blocks;
}

std::wstring
VijinerDecoder::get_key_variant1( const std::wstring& Y, wchar_t x, size_t r )
{
    const auto blocks = get_Y_blocks( Y, r );
    std::wstring key;
    key.reserve( r );
    const auto numeric_x = numeric_value_of_letter( x );
    
    for ( const auto& Y_i : blocks )
    {
        size_t max_counted_letter = 0;
        wchar_t most_common_letter = ' ';

        for ( const auto& letter : alphabet )
        {
            size_t letter_count = std::count( std::begin( Y_i ), 
                                  std::end( Y_i ), letter );
            if ( letter_count > max_counted_letter )
            {
                max_counted_letter = letter_count;
                most_common_letter = letter;
            }
        }

        auto numeric_most_common_letter = numeric_value_of_letter( most_common_letter );
        auto numeric_key_letter = numeric_difference_between_letters( numeric_most_common_letter, numeric_x );
        wchar_t key_letter = alphabet[ numeric_key_letter ];
        key.push_back( key_letter );
    }
    
    return key;
}

double
M_i( const std::wstring& Y_i, const std::map<wchar_t, size_t>& letters_freqs, 
     wchar_t maybe_key_letter, size_t text_size )
{
    auto numeric_maybe_key_letter = numeric_value_of_letter( maybe_key_letter );
    double m_i = 0;
    for ( const auto& l : alphabet )
    {
        auto letter_prob = letter_probability( text_size, letters_freqs.at( l ) );
        auto numeric_l = numeric_value_of_letter( l );
        auto x = alphabet[ ( numeric_maybe_key_letter + numeric_l ) % alphabet.size() ];
        m_i += letter_prob * std::count( std::begin( Y_i ), std::end( Y_i ), x );
    }
    
    
    return m_i;
}

std::wstring
VijinerDecoder::get_key_variant2( const std::wstring& Y, size_t r )
{
    const auto blocks = get_Y_blocks( Y, r );
    std::wstring key;
    key.reserve( r );

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring input;
    std::string line;
    std::ifstream fin;
    fin.open( "dead_souls.txt", std::ifstream::in );
    while (std::getline(fin, line, '\n') && !line.empty())
    {
        input += converter.from_bytes(line);
    }
    fin.close( );
    
    input = lower_case( input );

    auto letters_freq = letter_frequency( input );

    for ( const auto& block : blocks )
    {
        std::vector<double> m_i;
        m_i.reserve( alphabet.size( ) );
        for ( const auto& g : alphabet )
        {
            auto m_i_for_g = M_i( block, letters_freq, g, input.size( ) );
            m_i.push_back( m_i_for_g );
        }
        auto max_m_i_g = std::max_element( std::begin( m_i ), std::end( m_i ) );
        auto numeric_g_value = std::distance( std::begin( m_i ), max_m_i_g );
        auto g_letter = alphabet[ numeric_g_value ];
        key.push_back( g_letter );
    }
    
    return key;
}

std::vector<size_t>
VijinerDecoder::get_period_v( const std::wstring&  Y )
{
    size_t r = 2;
    std::vector<double> D_r;
    D_r.reserve( 28 );
    for (; r <= 30; r++)
    {
        D_r.push_back( VijinerDecoder::same_pares_counter( Y, r ) );
    }

    auto max_el = std::max_element( std::begin( D_r ), std::end( D_r ) );
    double max = *max_el;
    
    r = std::distance( std::begin( D_r ), max_el ) + 2;

    return dividers( r );
}

size_t
VijinerDecoder::get_period( const std::wstring&  Y )
{
    size_t r = 2;
    std::vector<double> D_r;
    D_r.reserve( 28 );
    for (; r < 30; r++)
    {
        D_r.push_back( VijinerDecoder::same_pares_counter( Y, r ) );
    }

    auto max_el = std::max_element( std::begin( D_r ), std::end( D_r ) );
    double max = *max_el;
    
    r = std::distance( std::begin( D_r ), max_el ) + 2;
    
    return r;
}

double
VijinerDecoder::compliance_index( const std::wstring& Y )
{
    double comp_index = 0;
    for ( const auto& c : alphabet )
    {
        auto letter_count_in_text = std::count( std::begin( Y ), std::end( Y ), c );
        comp_index += letter_count_in_text * ( letter_count_in_text - 1 );
    }
    double n = Y.size( );
    n -= std::count( std::begin( Y ), std::end( Y ), L' ' );
    comp_index /= n * ( n - 1 );

    return comp_index;
}

double
VijinerDecoder::compliance_index( const std::wstring& Y, size_t r )
{
    double comp_index = 0;

    const auto blocks = VijinerDecoder::get_Y_blocks( Y, r );
    for ( const auto& Y_i : blocks )
    {
        comp_index += VijinerDecoder::compliance_index( Y_i );
    }
    

    return comp_index;
}

double
VijinerDecoder::same_pares_counter( const std::wstring& Y, size_t r )
{
    double d = 0;
    for (size_t i = 0; i < Y.size( ) - r; i++)
    {
        if ( Y[i] == Y[i + r] )
        {
            ++d;
        }
        
    }
    return d;
}

std::wstring
VijinerDecoder::decode( const std::wstring& Y, const std::wstring& key )
{
    std::wstring decoded_text;
    decoded_text.reserve( Y.size() );

    for (size_t i = 0; i < Y.size(); i++)
    {
        auto numeric_decoded_letter = numeric_difference_between_letters( 
                                                    numeric_value_of_letter( Y[i] ), 
                                                    numeric_value_of_letter( key[ i % key.size() ] ) 
                                      );
        decoded_text.push_back( alphabet[ numeric_decoded_letter ] );
    }

    return decoded_text;
}
