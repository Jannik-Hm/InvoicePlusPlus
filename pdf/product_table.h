//
// Created by Jannik Heym on 20.02.25.
//

#ifndef PRODUCT_TABLE_H
#define PRODUCT_TABLE_H

#include <hpdf.h>
#include <list>
#include "../data_objects/product.h"

struct product_table_return {
    std::list<Product*> rest;
    HPDF_REAL height;
};

class product_table {
public:
    /// Function to automatically draw the Product table on to a given invoice page
    /// @returns Products unable to fit onto page without exceeding dimensions
    static product_table_return createProductTable(HPDF_Page page, HPDF_REAL padding_left, HPDF_REAL padding_right, HPDF_REAL y, HPDF_REAL bottom_padding, std::list<Product*> products, HPDF_Font font, HPDF_Font font_bold);

    static HPDF_REAL createTotalRow(HPDF_Page page, HPDF_REAL padding_left, HPDF_REAL padding_right, HPDF_REAL y, HPDF_REAL bottom_padding, std::list<Product*> products, HPDF_Font font_bold);
};



#endif //PRODUCT_TABLE_H
