#include "rock.h"
using namespace std;

bool Rock::is_double() const{
    return (top == bottom);
}

bool Rock::is6_6() const{
    return (top == 6 && bottom == 6);
}

bool operator<(const Rock &lhs, const Rock &rhs){
    if(rhs.is_double() && !lhs.is_double()){
        return true;
    }
    if(lhs.is_double() && !rhs.is_double()){
        return false;
    }
    if(lhs.is_double() && rhs.is_double()){
        if(rhs.top > lhs.top){
            return true;
        }
        return false;
    }
    if((rhs.top + rhs.bottom) > (lhs.top + lhs.bottom)){
        return true;
    }
    return false;
}