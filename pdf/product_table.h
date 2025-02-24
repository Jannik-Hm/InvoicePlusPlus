//
// Created by Jannik Heym on 20.02.25.
//

#ifndef PRODUCT_TABLE_H
#define PRODUCT_TABLE_H

#include <hpdf.h>
#include <list>
#include <memory>

#include "../data_objects/product_data.h"

struct product_table_return {
    std::list<std::shared_ptr<ProductData>> rest;
    HPDF_REAL height;
};

class product_table {
public:
    /// Function to automatically draw the Product table on to a given invoice page
    /// @returns Products unable to fit onto page without exceeding dimensions
    static product_table_return createProductTable(HPDF_Page page, HPDF_REAL padding_left, HPDF_REAL padding_right, HPDF_REAL y, HPDF_REAL bottom_padding, std::list<std::shared_ptr<ProductData>> products, HPDF_Font font, HPDF_Font font_bold);

    static HPDF_REAL createTotalRow(HPDF_Page page, HPDF_REAL padding_left, HPDF_REAL padding_right, HPDF_REAL y, HPDF_REAL bottom_padding, const std::list<std::shared_ptr<ProductData>> &products, HPDF_Font font_bold);
};



#endif //PRODUCT_TABLE_H
