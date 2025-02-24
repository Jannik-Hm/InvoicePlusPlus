#ifndef INVOICE_H
#define INVOICE_H
#include <hpdf.h>

#include "pdf_utils.h"
#include "../data_objects/invoice_data.h"


class Invoice {
public:
    explicit Invoice(std::shared_ptr<InvoiceData> invoice_data) {
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
    std::string generate();
private:
    HPDF_Page _generateNewPage();
    void _generateFooter(HPDF_Page page) const;
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
