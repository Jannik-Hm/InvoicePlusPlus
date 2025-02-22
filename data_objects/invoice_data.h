#ifndef INVOICE_DATA_H
#define INVOICE_DATA_H
#include <list>
#include <qdatetimeedit.h>
#include <string>
#include "product_data.h"
#include "representative_data.h"

class InvoiceData {
    public:
    RepresentativeData *sender;
    RepresentativeData *recipient;
    std::string invoice_number;
    QDate invoice_service_date;
    std::string invoice_title;
    std::string iban;
    std::string bic;
    std::string tax_number;
    std::list<ProductData*> products;
};

#endif //INVOICE_DATA_H
