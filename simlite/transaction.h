/**
 *  SIMLite - simple discrete simulation core
 *  Authors:
 *     Adam Lucansky <xlucan01@stud.fit.vutbr.cz>
 *     Tomas Kello <xkello00@stud.fit.vutbr.cz>
 */

#include "shared.h"

#ifndef SIMLITE_TRANSACTION_H
#define SIMLITE_TRANSACTION_H

class Facility;

class Transaction {
public:
    PtrMethod ptrMethod;
    string name;
public:
    Transaction(string name = "No name");

    void Seize(Facility &f, PtrMethod nextMethod, unsigned int itemSize = 1, unsigned int priority = 1);

    void ActivateAfter(double interval, PtrMethod nextMethod);

    void ActivateNext();

    void Release(Facility &f, PtrMethod nextMethod, unsigned int itemSize = 1, unsigned int priority = 1);
};

#include "facility.h"

#endif //SIMLITE_TRANSACTION_H
