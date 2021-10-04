// Author   : Wie Lie Sie.
// Class    : CSC 402 - Advanced Programming Languages.
// Project  : Hospital Application.
// Date     : 4/25/2021.

#ifndef HW4_COMPAREBYPRIORITY
#define HW4_COMPAREBYPRIORITY

#include "Patient.h"

template<typename T>
struct CompareByPriority
{
    //overload bool operator() that compare patient left hand side with patient right hand side based on priorities
    bool operator()(const Patient &LHS, const Patient &RHS) const
    {
        return LHS < RHS;
    }
};

#endif //HW4_COMPAREBYPRIORITY