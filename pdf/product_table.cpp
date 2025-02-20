#include "product_table.h"
#include "pdf_utils.h"

HPDF_REAL product_count_width = 40;
HPDF_REAL product_price_per_width = 70;
HPDF_REAL product_total_width = 70;

HPDF_REAL _createProductRow(const HPDF_Page page, HPDF_Font font, Product *product, HPDF_REAL y, HPDF_REAL left,
                            HPDF_REAL right, HPDF_REAL max_y) {
    int font_size = 10;
    HPDF_REAL line_height = changeFont(page, font_size, font);
    HPDF_REAL product_per_right = right - product_total_width;
    HPDF_REAL product_count_right = product_per_right - product_price_per_width;
    HPDF_REAL product_name_right = product_count_right - product_count_width;
    // center count, ppe and total to product name vertically when it is multi line
    HPDF_REAL product_name_height = writeTextIfNotHeightExceeded(page, product->name, left, y, line_height,
                                                                 product_name_right - left, HPDF_TALIGN_LEFT,
                                                                 y - max_y);
    if (product_name_height > 0) {
        HPDF_REAL centered_y = y - (product_name_height - line_height) / 2;
        writeText(page, to_str(product->count), product_name_right, centered_y, line_height, product_count_width,
                  HPDF_TALIGN_RIGHT, 1);
        // std::to_string(product_price_per) has rounding error
        writeText(page, to_str(product->price_per_unit), product_count_right, centered_y, line_height,
                  product_price_per_width, HPDF_TALIGN_RIGHT, 1);
        writeText(page, to_str(product->price_per_unit * product->count), product_per_right, centered_y, line_height,
                  product_total_width, HPDF_TALIGN_RIGHT, 1);
    }
    return product_name_height;
}

HPDF_REAL _createProductHeader(const HPDF_Page page, HPDF_Font font, HPDF_REAL y, HPDF_REAL left, HPDF_REAL right) {
    int font_size = 10;
    HPDF_REAL line_height = changeFont(page, font_size, font);
    HPDF_REAL product_per_right = right - product_total_width;
    HPDF_REAL product_count_right = product_per_right - product_price_per_width;
    HPDF_REAL product_name_right = product_count_right - product_count_width;
    HPDF_REAL product_name_height = writeText(page, "Produktname", left, y, line_height, product_name_right - left,
                                              HPDF_TALIGN_LEFT, 1);;
    HPDF_REAL product_count_height = writeText(page, "Anzahl", product_name_right, y, line_height, product_count_width,
                                               HPDF_TALIGN_RIGHT, 1);
    HPDF_REAL product_per_height = writeText(page, "Einzelpreis\nin EUR", product_count_right, y, line_height,
                                             product_price_per_width, HPDF_TALIGN_RIGHT, 2);
    HPDF_REAL product_total_height = writeText(page, "Gesamtpreis\nin EUR", product_per_right, y, line_height,
                                               product_total_width, HPDF_TALIGN_RIGHT, 2);
    return std::max(std::max(product_name_height, product_count_height),
                    std::max(product_per_height, product_total_height));
}

void _drawLine(HPDF_Page page, HPDF_REAL from_x, HPDF_REAL from_y, HPDF_REAL to_x, HPDF_REAL to_y) {
    HPDF_Page_MoveTo(page, from_x, from_y);
    HPDF_Page_LineTo(page, to_x, to_y);
    HPDF_Page_Stroke(page);
}

std::list<Product *> product_table::createProductTable(HPDF_Page page, HPDF_REAL padding_left, HPDF_REAL padding_right,
                                                       HPDF_REAL y, HPDF_REAL bottom_padding,
                                                       std::list<Product *> products, HPDF_Font font_normal,
                                                       HPDF_Font font_bold) {
    HPDF_REAL currentHeight = y;
    HPDF_Page_SetLineWidth(page, 2.0);
    currentHeight -= _createProductHeader(page, font_bold, currentHeight, padding_left, padding_right);
    //TODO: figure out how to center this
    _drawLine(page, padding_left, currentHeight - 5, padding_right, currentHeight - 5);
    currentHeight -= 10;
    HPDF_Page_SetLineWidth(page, 1.0);
    std::list<Product*> remainingElements;
    for (std::list<Product*>::iterator i=products.begin(); i!=products.end();++i) {
        HPDF_REAL row_height = _createProductRow(page, font_normal, *i, currentHeight, padding_left, padding_right, bottom_padding);
        if (&*i != &products.front() and row_height > 0) {

            _drawLine(page, padding_left, currentHeight + 5, padding_right, currentHeight + 5);
            std::cout << currentHeight + row_height - 5 << " " << currentHeight << " " << row_height << std::endl;
        }
        currentHeight -= row_height;
        currentHeight -= 10;
        if (row_height == 0) {
            std::list<Product *> temp(i, products.end());
            return temp;
        }
    }
    return {};
}
