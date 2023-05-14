#include "subject.h"

void Subject::attach(Observer *o) {
    // put the pointer of the observer into the vector
    observers.emplace_back(o);
}
