#ifndef PDF_EXCEPTION_H
#define PDF_EXCEPTION_H
#include <string>

/// @brief Libharu Exception
/// @details This exception will be thrown when Libharu encounters an error
class PDFException : public std::exception {
    HPDF_STATUS error_code;
    HPDF_STATUS detail_code;

public:
    explicit PDFException(const HPDF_STATUS error_code, const HPDF_STATUS detail_code)
        : error_code(error_code), detail_code(detail_code) {
    }

    std::string message() const {
        return std::format("Libharu Error Code: {:04X}\nDetail Code: {:d}", static_cast<unsigned int>(error_code),
                           static_cast<int>(detail_code));
    }
};

#endif //PDF_EXCEPTION_H
