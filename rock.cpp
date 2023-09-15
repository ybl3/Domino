// This file includes the implementation for the rock data type. A rock refers to one piece of the dominoes,
// similar to how a card refers to one card of a card stack
#include "rock.h"
using namespace std;

bool Rock::is_double() const{
    return (top == bottom);
}

bool Rock::is6_6() const{
    return (top == 6 && bottom == 6);
}

// less than operator to compare value of rocks (which is subjective, this is just what I chose)
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