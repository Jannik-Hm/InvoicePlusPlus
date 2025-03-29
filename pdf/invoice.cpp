#include "invoice.h"
#include <QtCore/qcoreapplication.h>

#include "product_table.h"
#include "../ui/customWidgets/inputWidget/dateInputWidget.h"
#include <QStandardPaths>
#include <QMessageBox>

HPDF_Page Invoice::_generateNewPage() {
    const HPDF_Page new_page = HPDF_AddPage(this->pdf);
    HPDF_Page_SetSize(new_page, this->page_size, this->page_direction);
    pages.push_back(new_page);
    current_height = padding_top;
    this->_generateFooter(new_page);
    return new_page;
}

void Invoice::_generateFooter(const HPDF_Page page) const {
    const HPDF_REAL line_height = changeFont(page, 8.0, font_normal);
    const HPDF_REAL column_width = (padding_right - padding_left) / 3.0;
    HPDF_Page_SetLineWidth(page, 2.0);
    drawLine(page, padding_left, padding_bottom - 15, padding_right, padding_bottom - 15);
    const HPDF_REAL line_1_y = padding_bottom - 20;
    const HPDF_REAL line2_y = line_1_y - (1 + writeText(page, this->invoice_data->sender->name, padding_left, line_1_y,
                                                        line_height, column_width, HPDF_TALIGN_LEFT));
    const HPDF_REAL line3_y = line2_y - (1 + writeText(
                                             page,
                                             this->invoice_data->sender->street + " " + this->invoice_data->sender->
                                             housenumber, padding_left, line2_y, line_height, column_width,
                                             HPDF_TALIGN_LEFT));
    writeText(page, this->invoice_data->sender->zipcode + " " + this->invoice_data->sender->city, padding_left, line3_y,
              line_height, column_width, HPDF_TALIGN_LEFT);

    // center middle column
    std::string iban = "IBAN: " + this->invoice_data->iban;
    std::string bic = "BIC: " + this->invoice_data->bic;
    // calculate maximum width of iban and bic + safe space when calculation returns a bit less than actually required
    HPDF_REAL banking_width = std::max(HPDF_Page_TextWidth(page, iban.c_str()), HPDF_Page_TextWidth(page, bic.c_str())) + 10.0;
    HPDF_REAL banking_x = padding_left + column_width + (column_width - banking_width) / 2.0;
    writeText(page, iban, banking_x, line_1_y, line_height, banking_width, HPDF_TALIGN_LEFT);
    writeText(page, bic, banking_x, line2_y, line_height, banking_width, HPDF_TALIGN_LEFT);

    writeText(page, "Steuernummer: " + this->invoice_data->tax_number, padding_left + 2 * column_width, line_1_y,
              line_height, column_width, HPDF_TALIGN_RIGHT);
}

void Invoice::_generatePageNumbers() const {
    int page_index = 1;
    for (const auto page : pages) {
        const HPDF_REAL line_height = changeFont(page, 8.0, font_normal);
        writeText(page, "Seite " + to_str(page_index++) + " von " + to_str(pages.size()), padding_left, padding_bottom - 3, line_height, padding_right-padding_left, HPDF_TALIGN_CENTER);
    }
}

std::string Invoice::generate() {

    // Special Handling for first page to rewrite paddings to correct values + possible special design
    const HPDF_Page first_page = HPDF_AddPage(this->pdf);
    pages.push_back(first_page);
    HPDF_Page_SetSize(first_page, this->page_size, this->page_direction);

    this->padding_top = HPDF_Page_GetHeight(first_page) - this->padding_top;
    this->padding_right = HPDF_Page_GetWidth(first_page) - this->padding_right;
    const float innerWidth = this->padding_right - this->padding_left;

    this->_generateFooter(first_page);

    const float y_contact = HPDF_Page_GetHeight(first_page) - 120;

    const HPDF_INT sender_font_size = 8;
    const HPDF_INT invoiceMeta_font_size = 10;
    const HPDF_INT recipient_font_size = 11;
    const HPDF_INT title_font_size = 12;

    const std::string invoice_date = QDate::currentDate().toString("dd.MM.yyyy").toStdString();

    current_height = y_contact;

    HPDF_REAL line_height = changeFont(first_page, sender_font_size, this->font_normal);

    current_height -= writeText(first_page, this->invoice_data->sender->name, padding_left, current_height, line_height,
                                innerWidth / 2 - padding_left, HPDF_TALIGN_LEFT, 2);
    current_height -= writeText(
        first_page,
        this->invoice_data->sender->street + " " + this->invoice_data->sender->housenumber + " - " + this->invoice_data
        ->sender->zipcode + " " + this->invoice_data->sender->city, padding_left, current_height, line_height,
        innerWidth / 2 - padding_left, HPDF_TALIGN_LEFT, 1);
    current_height -= 1;

    float invoiceMeta_data_y = current_height - 1; //correction as address font size is 11 and invoiceMeta 10

    HPDF_REAL invoiceMeta_data_x = innerWidth / 2 + 200 + 10;
    float font_size = invoiceMeta_font_size;
    line_height = changeFont(first_page, font_size, font_bold);
    writeText(first_page, "Rechnung Nr.:", innerWidth / 2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT, 1);

    HPDF_Page_SetFontAndSize(first_page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(first_page, this->invoice_data->invoice_number, invoiceMeta_data_x,
                                    invoiceMeta_data_y, line_height, padding_right - invoiceMeta_data_x,
                                    HPDF_TALIGN_LEFT, 1);
    invoiceMeta_data_y -= recipient_font_size - invoiceMeta_font_size;

    HPDF_Page_SetFontAndSize(first_page, this->font_bold, font_size);
    writeText(first_page, "Rechnungsdatum:", innerWidth / 2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT,
              1);

    HPDF_Page_SetFontAndSize(first_page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(first_page, invoice_date, invoiceMeta_data_x, invoiceMeta_data_y, line_height,
                                    padding_right - invoiceMeta_data_x, HPDF_TALIGN_LEFT, 1);
    invoiceMeta_data_y -= recipient_font_size - invoiceMeta_font_size;

    HPDF_Page_SetFontAndSize(first_page, this->font_bold, font_size);
    writeText(first_page, "Leistungsdatum:", innerWidth / 2, invoiceMeta_data_y, line_height, 200, HPDF_TALIGN_RIGHT,
              1);

    HPDF_Page_SetFontAndSize(first_page, this->font_normal, font_size);
    invoiceMeta_data_y -= writeText(
        first_page, this->invoice_data->invoice_service_date.toString("dd.MM.yyyy").toStdString(), invoiceMeta_data_x,
        invoiceMeta_data_y, line_height, padding_right - invoiceMeta_data_x, HPDF_TALIGN_LEFT, 1);


    line_height = changeFont(first_page, recipient_font_size, this->font_normal);

    current_height -= writeText(first_page, this->invoice_data->recipient->name, this->padding_left, current_height,
                                line_height, innerWidth / 2 - this->padding_left, HPDF_TALIGN_LEFT, 1);
    current_height -= writeText(
        first_page, this->invoice_data->recipient->street + " " + this->invoice_data->recipient->housenumber,
        this->padding_left, current_height, line_height, innerWidth / 2 - this->padding_left, HPDF_TALIGN_LEFT, 1);
    current_height -= writeText(
        first_page, this->invoice_data->recipient->zipcode + " " + this->invoice_data->recipient->city,
        this->padding_left, current_height, line_height, innerWidth / 2 - this->padding_left, HPDF_TALIGN_LEFT, 1);

    HPDF_REAL text_width = HPDF_Page_TextWidth(first_page, invoice_date.c_str());
    // get lowest point of left and right text
    current_height = std::min(invoiceMeta_data_y, current_height) - 30;
    writeText(first_page, invoice_date, padding_right - text_width, current_height, line_height, text_width,
              HPDF_TALIGN_RIGHT, 1);

    line_height = changeFont(first_page, title_font_size, this->font_bold);
    std::string title = this->invoice_data->invoice_title;
    std::transform(title.begin(), title.end(), title.begin(), ::toupper);
    current_height -= writeText(first_page, title, this->padding_left, current_height, line_height,
                                innerWidth / 2 - this->padding_left, HPDF_TALIGN_LEFT, 1);

    current_height -= 20;

    product_table_return table = product_table::createProductTable(first_page, padding_left, padding_right,
                                                                   current_height, this->padding_bottom,
                                                                   this->invoice_data->products, this->font_normal,
                                                                   this->font_bold);
    while (table.rest.size() > 0) {
        table = product_table::createProductTable(this->_generateNewPage(), padding_left, padding_right, current_height,
                                                  this->padding_bottom, table.rest, this->font_normal, this->font_bold);
    }
    current_height -= table.height;

    // create Total Row -> if not enough space left, generate on a new page
    if (product_table::createTotalRow(pages.back(), padding_left, padding_right, current_height, this->padding_bottom,
                                      this->invoice_data->products, this->font_bold) == 0) {
        product_table::createTotalRow(this->_generateNewPage(), padding_left, padding_right, current_height,
                                      this->padding_bottom, this->invoice_data->products, this->font_bold);
    }

    this->_generatePageNumbers();

    // Save the document to users downloads folder as invoice_number.pdf
    std::string filepath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation).toStdString() + "/"+ this->invoice_data->invoice_title +".pdf";
    if (HPDF_OK == HPDF_SaveToFile(pdf, filepath.c_str())) {
        HPDF_Free(pdf);
        return filepath;
    }
    HPDF_Free(pdf);
    return "";
}
