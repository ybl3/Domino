struct Rock{
    int top;
    int bottom;

    bool is_double() const;

    bool is6_6() const;

};

bool operator<(const Rock &lhs, const Rock &rhs);