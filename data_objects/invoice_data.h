#ifndef INVOICE_DATA_H
#define INVOICE_DATA_H
#include <list>
#include <string>
#include "product.h"

class InvoiceData {
    public:
    std::string sender_name;
    std::list<Product*> products;
};

#endif //INVOICE_DATA_H
