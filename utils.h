#ifndef UTILS_H
#define UTILS_H

#include <iconv.h>
#include <stdexcept>
#include <vector>
#include <sstream>

/// @brief converts a UTF8 string to ISO8859-1 / ANSI using iconv
/// @return ANSI String
inline std::string UTF8toISO8859_1(const std::string& utf8_str) {
    iconv_t conv_desc = iconv_open("ISO-8859-1//TRANSLIT", "UTF-8");
    if (conv_desc == reinterpret_cast<iconv_t>(-1)) {
        throw std::runtime_error("iconv_open failed");
    }

    size_t in_bytes_left = utf8_str.size();
    size_t out_bytes_left = in_bytes_left; // ISO-8859-1 won't be larger than UTF-8
    std::vector<char> output_buffer(out_bytes_left);
    char* in_buf = const_cast<char*>(utf8_str.data());
    char* out_buf = output_buffer.data();

    if (iconv(conv_desc, &in_buf, &in_bytes_left, &out_buf, &out_bytes_left) == static_cast<size_t>(-1)) {
        iconv_close(conv_desc);
        throw std::runtime_error("iconv conversion failed");
    }

    std::string result(output_buffer.data(), output_buffer.size() - out_bytes_left);
    iconv_close(conv_desc);
    return result;
}

/// @brief converts various datatypes to string using ostringstream
/// @return data as string
template < typename Type > std::string to_str (const Type & t)
{
    std::ostringstream os;
    os << t;
    return os.str ();
}

#endif //UTILS_H
