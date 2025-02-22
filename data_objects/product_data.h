#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class ProductData {
public:
    ProductData(const std::string &name, const int count, const double price_per_unit) {
        this->name = name;
        this->count = count;
        this->price_per_unit = price_per_unit;
    };
    std::string name;
    int count;
    double price_per_unit;
};

#endif //PRODUCT_H
