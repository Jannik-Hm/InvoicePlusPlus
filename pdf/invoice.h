#ifndef INVOICE_H
#define INVOICE_H
#include <hpdf.h>

#include "pdf_utils.h"
#include "../data_objects/invoice_data.h"


class Invoice {
public:
    explicit Invoice(InvoiceData* invoice_data) {
        this->invoice_data = invoice_data;
        this->pdf = HPDF_New(error_handler, nullptr);
        if (!pdf) {
            throw std::runtime_error("Error: cannot create PdfDoc object");
        }
        this->font_normal = HPDF_GetFont(pdf, "Helvetica", "WinAnsiEncoding");
        this->font_bold = HPDF_GetFont(pdf, "Helvetica-Bold", "WinAnsiEncoding");
    }
    int generate();
private:
    InvoiceData *invoice_data{};
    float line_height_factor = 1.2;
    HPDF_PageSizes page_size = HPDF_PAGE_SIZE_A4;
    HPDF_PageDirection page_direction = HPDF_PAGE_PORTRAIT;
    float padding_left = 0;
    float padding_right = 0;
    float padding_top = 0;
    float padding_bottom = 0;
    HPDF_Doc pdf;
    HPDF_Font font_normal;
    HPDF_Font font_bold;
    HPDF_REAL createProductRow(const HPDF_Page page, HPDF_Font font, Product* product, HPDF_REAL y, HPDF_REAL left, HPDF_REAL right);
};



#endif //INVOICE_H
