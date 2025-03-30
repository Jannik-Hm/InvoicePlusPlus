//
// Created by Jannik Heym on 20.02.25.
//

#ifndef PRODUCT_TABLE_H
#define PRODUCT_TABLE_H

#include <hpdf.h>
#include <list>
#include <memory>

#include "../data_objects/product_data.h"

/// @brief return struct for "createProductTable()"
struct product_table_return {
    std::list<std::shared_ptr<ProductData>> rest;
    HPDF_REAL height;
};

class product_table {
public:
    /// @brief Function to automatically draw the Product table on to a given invoice page
    /// @returns list of Products unable to fit onto page without exceeding dimensions and height of this element
    static product_table_return createProductTable(HPDF_Page page, HPDF_REAL padding_left, HPDF_REAL padding_right, HPDF_REAL y, HPDF_REAL bottom_padding, std::list<std::shared_ptr<ProductData>> products, HPDF_Font font, HPDF_Font font_bold);

    /// @brief Draws the Product Tables Total Row on to a given pdf page
    /// @return the height of the element on the page
    static HPDF_REAL createTotalRow(HPDF_Page page, HPDF_REAL padding_left, HPDF_REAL padding_right, HPDF_REAL y, HPDF_REAL bottom_padding, const std::list<std::shared_ptr<ProductData>> &products, HPDF_Font font_bold);
};



#endif //PRODUCT_TABLE_H
