#ifndef INVOICE_H
#define INVOICE_H
#include <hpdf.h>

#include "pdf_utils.h"
#include "../data_objects/invoice_data.h"


class Invoice {
public:
    explicit Invoice(const std::shared_ptr<InvoiceData> &invoice_data) {
        this->invoice_data = invoice_data;
        this->pdf = HPDF_New(error_handler, nullptr);
        if (!pdf) {
            throw std::runtime_error("Error: cannot create PdfDoc object");
        }
        this->font_normal = HPDF_GetFont(pdf, "Helvetica", "WinAnsiEncoding");
        this->font_bold = HPDF_GetFont(pdf, "Helvetica-Bold", "WinAnsiEncoding");
        this->current_height = padding_top;
    }
    HPDF_Doc pdf;

    /// @brief generate a PDF invoice and save it to the users downloads folder as the invoice_number.pdf
    /// @return the location of the saved pdf
    /// @exception PDFException
    std::string generate();
private:

    /// @brief create a new page and add to pages list
    /// @return the created page
    HPDF_Page _generateNewPage();

    /// @brief prints the footer on the current pdf page, excluding the page number
    void _generateFooter(HPDF_Page page) const;

    /// @brief print page numbering on all pages
    void _generatePageNumbers() const;

    std::shared_ptr<InvoiceData> invoice_data{};
    std::list<HPDF_Page> pages{};
    float line_height_factor = 1.2;
    HPDF_PageSizes page_size = HPDF_PAGE_SIZE_A4;
    HPDF_PageDirection page_direction = HPDF_PAGE_PORTRAIT;
    float padding_left = 55;
    float padding_right = 55;
    float padding_top = 55;
    float padding_bottom = 65;
    HPDF_REAL current_height;
    HPDF_Font font_normal;
    HPDF_Font font_bold;
};



#endif //INVOICE_H
