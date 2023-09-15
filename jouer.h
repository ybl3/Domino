#include <vector>
#include <tuple>
#include "rock.h"

void display_hand();

class Jouer{
    private:

    public:

    std::vector<Rock> hand;

    std::string name;

    bool is_human;

    virtual std::tuple<int, int, Rock> play_rock(int front, int back) = 0;

    virtual Rock play_first() = 0;

    virtual int sum_hand() = 0;

    virtual bool fivedoubles() = 0;

    virtual ~Jouer() {};
};

Jouer* Jouer_constructor(std::string name_in, bool human);