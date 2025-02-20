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

    HPDF_Page page = HPDF_AddPage(this->pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    // Non UTF-8 -> Ansi only
    // HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", "WinAnsiEncoding");
    // HPDF_Font font_bold = HPDF_GetFont(pdf, "Helvetica-Bold", "WinAnsiEncoding");

    float padding_left = 55;
    float padding_right = HPDF_Page_GetWidth(page) - 55;
    float innerWidth = padding_right - padding_left;

    float x_contact = 55;
    float y_contact = HPDF_Page_GetHeight(page) - 120;

    HPDF_INT sender_font_size = 8;
    HPDF_INT invoiceMeta_font_size = 10;
    HPDF_INT recipient_font_size = 11;
    HPDF_INT title_font_size = 12;

    HPDF_REAL currentHeight = y_contact;

    HPDF_REAL line_height = changeFont(page, sender_font_size, this->font_normal);

    currentHeight -= writeText(page, "Name", padding_left, currentHeight, line_height, innerWidth/2 - padding_left, HPDF_TALIGN_LEFT, 2);
    currentHeight -= writeText(page, "Straße Hausnummer – PLZ Stadt", padding_left, currentHeight, line_height, innerWidth/2 - padding_left, HPDF_TALIGN_LEFT, 1);
    currentHeight -= 1;

    float invoiceMeta_data_y = currentHeight - 1; //correction as address font size is 11 and invoiceMeta 10

    HPDF_REAL invoiceMeta_data_x = innerWidth / 2 + 200 + 10;
    float font_size = invoiceMeta_font_size;
    line_height = changeFont(page, font_size, font_bold);
    writeText(page, "Rechnung Nr.:", innerWidth/2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT, 1);

    HPDF_Page_SetFontAndSize(page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(page, "2025-02-18-MM", invoiceMeta_data_x, invoiceMeta_data_y, line_height, padding_right - invoiceMeta_data_x, HPDF_TALIGN_LEFT, 1);
    invoiceMeta_data_y -= recipient_font_size - invoiceMeta_font_size;

    HPDF_Page_SetFontAndSize(page, this->font_bold, font_size);
    writeText(page, "Rechnungsdatum:", innerWidth/2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT, 1);

    HPDF_Page_SetFontAndSize(page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(page, "19.02.2025", invoiceMeta_data_x, invoiceMeta_data_y, line_height, padding_right - invoiceMeta_data_x, HPDF_TALIGN_LEFT, 1);
    invoiceMeta_data_y -= recipient_font_size - invoiceMeta_font_size;

    HPDF_Page_SetFontAndSize(page, this->font_bold, font_size);
    writeText(page, "Leistungsdatum:", innerWidth/2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT, 1);

    HPDF_Page_SetFontAndSize(page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(page, "18.02.2025", invoiceMeta_data_x, invoiceMeta_data_y, line_height, padding_right - invoiceMeta_data_x, HPDF_TALIGN_LEFT, 1);


    line_height = changeFont(page, recipient_font_size, this->font_normal);

    currentHeight -= writeText(page, "Max Mustermann", x_contact, currentHeight, line_height, innerWidth/2 - x_contact, HPDF_TALIGN_LEFT, 1);
    currentHeight -= writeText(page, "Potsdamer Platz 10", x_contact, currentHeight, line_height, innerWidth/2 - x_contact, HPDF_TALIGN_LEFT, 1);
    currentHeight -= writeText(page, "10785 Berlin", x_contact, currentHeight, line_height, innerWidth/2 - x_contact, HPDF_TALIGN_LEFT, 1);

    std::string invoice_date = "19.02.2025";
    HPDF_REAL text_width = HPDF_Page_TextWidth(page, invoice_date.c_str());
    // get lowest point of left and right text
    currentHeight = std::min(invoiceMeta_data_y, currentHeight) - 30;
    writeText(page, "19.02.2025", padding_right - text_width, currentHeight, line_height, text_width, HPDF_TALIGN_RIGHT, 1);

    line_height = changeFont(page, title_font_size, this->font_bold);
    std::string title = "Projekt XY";
    std::transform(title.begin(), title.end(), title.begin(), ::toupper);
    currentHeight -= writeText(page, title, x_contact, currentHeight, line_height, innerWidth/2 - x_contact, HPDF_TALIGN_LEFT, 1);

    currentHeight -= 20;

    //generates the first product table and returns the items that did not fit onto the page --> TODO: loop until no items are over with generating a new page with header and footer each loop
    std::list<Product *> temp = product_table::createProductTable(page, padding_left, padding_right, currentHeight, this->padding_bottom, this->invoice_data->products, this->font_normal, this->font_bold);
    std::cout << temp.size() << std::endl;

    // Sample data
    std::vector<std::vector<std::string> > data = {
        {"Header1", "Header2", "Header3"},
        {"Row1 Col1", "Row1 Col2", "Row1 Col3"},
        {"Row2 Col1", "Row2 Col2", "Row2 Col3"},
        {"Row3 Col1", "Row3 Col2", "Row3 Col3"}
    };

    // Table parameters
    float x = padding_left;
    float y = currentHeight - 20;
    float cell_width = innerWidth/3;
    float cell_height = 20;

    // create_table(pdf, page, data, x, y, cell_width, cell_height, font);

    // Save the document to a file
    HPDF_SaveToFile(pdf, "table_example.pdf");

    // Clean up
    HPDF_Free(pdf);

    return 0;
}
