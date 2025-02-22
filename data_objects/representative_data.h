#ifndef REPRESENTATIVE_DATA_H
#define REPRESENTATIVE_DATA_H
#include <string>

class RepresentativeData {
public:
    RepresentativeData(const std::string &name, const std::string &street, const std::string &housenumber, const std::string &zipcode, const std::string &city) {
        this->name = name;
        this->street = street;
        this->housenumber = housenumber;
        this->zipcode = zipcode;
        this->city = city;
    };
    std::string name;
    std::string street;
    std::string housenumber;
    std::string zipcode;
    std::string city;
};

#endif //REPRESENTATIVE_DATA_H
