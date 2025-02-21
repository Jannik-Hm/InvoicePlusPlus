//
// Created by Jannik Heym on 20.02.25.
//

#include "invoice.h"

#include <QtCore/qtextstream.h>

#include "product_table.h"

int Invoice::generate() {
    // HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
    // if (!pdf) {
    //     printf("Error: cannot create PdfDoc object\n");
    //     return 1;
    // }

    HPDF_Page first_page = HPDF_AddPage(this->pdf);
    std::list<HPDF_Page> pages = {first_page};
    HPDF_Page_SetSize(first_page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    // Non UTF-8 -> Ansi only
    // HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", "WinAnsiEncoding");
    // HPDF_Font font_bold = HPDF_GetFont(pdf, "Helvetica-Bold", "WinAnsiEncoding");

    this->padding_right = HPDF_Page_GetWidth(first_page) - this->padding_right;
    float innerWidth = this->padding_right - this->padding_left;
    this->padding_top = HPDF_Page_GetHeight(first_page) - this->padding_top;

    float y_contact = HPDF_Page_GetHeight(first_page) - 120;

    HPDF_INT sender_font_size = 8;
    HPDF_INT invoiceMeta_font_size = 10;
    HPDF_INT recipient_font_size = 11;
    HPDF_INT title_font_size = 12;

    HPDF_REAL currentHeight = y_contact;

    HPDF_REAL line_height = changeFont(first_page, sender_font_size, this->font_normal);

    currentHeight -= writeText(first_page, "Name", padding_left, currentHeight, line_height, innerWidth/2 - padding_left, HPDF_TALIGN_LEFT, 2);
    currentHeight -= writeText(first_page, "Straße Hausnummer – PLZ Stadt", padding_left, currentHeight, line_height, innerWidth/2 - padding_left, HPDF_TALIGN_LEFT, 1);
    currentHeight -= 1;

    float invoiceMeta_data_y = currentHeight - 1; //correction as address font size is 11 and invoiceMeta 10

    HPDF_REAL invoiceMeta_data_x = innerWidth / 2 + 200 + 10;
    float font_size = invoiceMeta_font_size;
    line_height = changeFont(first_page, font_size, font_bold);
    writeText(first_page, "Rechnung Nr.:", innerWidth/2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT, 1);

    HPDF_Page_SetFontAndSize(first_page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(first_page, "2025-02-18-MM", invoiceMeta_data_x, invoiceMeta_data_y, line_height, padding_right - invoiceMeta_data_x, HPDF_TALIGN_LEFT, 1);
    invoiceMeta_data_y -= recipient_font_size - invoiceMeta_font_size;

    HPDF_Page_SetFontAndSize(first_page, this->font_bold, font_size);
    writeText(first_page, "Rechnungsdatum:", innerWidth/2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT, 1);

    HPDF_Page_SetFontAndSize(first_page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(first_page, "19.02.2025", invoiceMeta_data_x, invoiceMeta_data_y, line_height, padding_right - invoiceMeta_data_x, HPDF_TALIGN_LEFT, 1);
    invoiceMeta_data_y -= recipient_font_size - invoiceMeta_font_size;

    HPDF_Page_SetFontAndSize(first_page, this->font_bold, font_size);
    writeText(first_page, "Leistungsdatum:", innerWidth/2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT, 1);

    HPDF_Page_SetFontAndSize(first_page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(first_page, "18.02.2025", invoiceMeta_data_x, invoiceMeta_data_y, line_height, padding_right - invoiceMeta_data_x, HPDF_TALIGN_LEFT, 1);


    line_height = changeFont(first_page, recipient_font_size, this->font_normal);

    currentHeight -= writeText(first_page, "Max Mustermann", this->padding_left, currentHeight, line_height, innerWidth/2 - this->padding_left, HPDF_TALIGN_LEFT, 1);
    currentHeight -= writeText(first_page, "Potsdamer Platz 10", this->padding_left, currentHeight, line_height, innerWidth/2 - this->padding_left, HPDF_TALIGN_LEFT, 1);
    currentHeight -= writeText(first_page, "10785 Berlin", this->padding_left, currentHeight, line_height, innerWidth/2 - this->padding_left, HPDF_TALIGN_LEFT, 1);

    std::string invoice_date = "19.02.2025";
    HPDF_REAL text_width = HPDF_Page_TextWidth(first_page, invoice_date.c_str());
    // get lowest point of left and right text
    currentHeight = std::min(invoiceMeta_data_y, currentHeight) - 30;
    writeText(first_page, "19.02.2025", padding_right - text_width, currentHeight, line_height, text_width, HPDF_TALIGN_RIGHT, 1);

    line_height = changeFont(first_page, title_font_size, this->font_bold);
    std::string title = "Projekt XY";
    std::transform(title.begin(), title.end(), title.begin(), ::toupper);
    currentHeight -= writeText(first_page, title, this->padding_left, currentHeight, line_height, innerWidth/2 - this->padding_left, HPDF_TALIGN_LEFT, 1);

    currentHeight -= 20;

    //generates the first product table and returns the items that did not fit onto the page --> TODO: loop until no items are over with generating a new page with header and footer each loop
    product_table_return table = product_table::createProductTable(first_page, padding_left, padding_right, currentHeight, this->padding_bottom, this->invoice_data->products, this->font_normal, this->font_bold);
    while (table.rest.size() > 0) {
        HPDF_Page new_page = HPDF_AddPage(this->pdf);
        pages.push_back(new_page);
        currentHeight = padding_top;
        table = product_table::createProductTable(new_page, padding_left, padding_right, currentHeight, this->padding_bottom, table.rest, this->font_normal, this->font_bold);
        std::cout << table.rest.size() << std::endl;
    }
    currentHeight -= table.height;
    if (product_table::createTotalRow(pages.back(), padding_left, padding_right, currentHeight, this->padding_bottom, this->invoice_data->products, this->font_bold) == 0) {
        HPDF_Page new_page = HPDF_AddPage(this->pdf);
        pages.push_back(new_page);
        currentHeight = padding_top;
        product_table::createTotalRow(pages.back(), padding_left, padding_right, currentHeight, this->padding_bottom, this->invoice_data->products, this->font_bold);
    }

    // Save the document to a file
    HPDF_SaveToFile(pdf, "table_example.pdf");

    // Clean up
    HPDF_Free(pdf);

    return 0;
}
