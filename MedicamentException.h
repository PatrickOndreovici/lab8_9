//
// Created by Patrick Ondreovici on 18.04.2024.
//

#ifndef LAB6_MEDICAMENTEXCEPTION_H
#define LAB6_MEDICAMENTEXCEPTION_H
#include <string>
#include <utility>
using std::string;
class MedicamentException : public std::exception{
private:
    string msg;
public:
    explicit MedicamentException(string m) : msg{std::move(m)}{
    }

    string getMessage(){
        return msg;
    }

};


#endif //LAB6_MEDICAMENTEXCEPTION_H
