#include "jeux.h"
#include "jouer.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <cstdlib>
using namespace std;

class Jeux{

    private:

    vector<Jouer*> players;
    int points_to_win;
    int t1points;
    int t2points;
    int front;
    int back;
    int winner;
    vector<int> numleft;
    vector<Rock> rocks;
    

    public:

    Jeux(): players(vector<Jouer*>()), rocks(vector<Rock>()) {
        players = {nullptr, nullptr, nullptr, nullptr};
        cout << "Welcome, you are about to begin a new Domino game\n";
        string m;
        string name;
        int k = 0;
        for(int i = 1; i <= 2; ++i){
            for(int j = 1; j <= 2; ++j){
                cout << "For player " << j << " of team " << i << ", enter c if CPU or h if human:\n";
                cin >> m;
                while(!(m == "c" || m == "h")){
                    cout << "Error, unrecognized player type, please try again:\n";
                    cin >> m;
                }
                cout << "For player " << j << " of team " << i << ", enter the name:\n";
                cin >> name;
                if(m == "c"){
                    if(i == 1 && j == 2){
                        players[2] = Jouer_constructor(name, false);
                        players[2]->name = name;
                        players[2]->is_human = false;
                    }
                    else if(i == 2 && j == 1){
                        players[1] = Jouer_constructor(name, false);
                        players[1]->name = name;
                        players[1]->is_human = false;
                    }
                    else{
                        players[k] = Jouer_constructor(name, false);
                        players[k]->name = name;
                        players[k]->is_human = false;
                    }
                    ++k;
                }
                else{
                    if(i == 1 && j == 2){
                        players[2] = Jouer_constructor(name, true);
                        players[2]->name = name;
                        players[2]->is_human = true;
                    }
                    else if(i == 2 && j == 1){
                        players[1] = Jouer_constructor(name, true);
                        players[1]->name = name;
                        players[1]->is_human = true;
                    }
                    else{
                        players[k] = Jouer_constructor(name, true);
                        players[k]->name = name;
                        players[k]->is_human = true;
                    }
                    ++k;
                }
            }
        }
        t1points = 0;
        t2points = 0;
        winner = 3;
        numleft = vector<int>(7, 8);
        cout << "Please enter the number of points required to win:\n";
        cin >> points_to_win;
        while(points_to_win < 1 || points_to_win > 5000){
            cout << "Error: the points to win must be between 1 and 5000, please try again:\n";
            cin >> points_to_win;
        }
        rocks.reserve(28);
        for(int i = 0; i < 7; ++i){
            for(int j = i; j < 7; ++j){
                rocks.push_back({i,j});
            }
        }
    }// constructor

    void print_team(int team){
        if(team == 1){
            cout << "Team 1, " << players[0]->name << " and " << players[2]->name;
        }
        else{
            cout << "Team 2, " << players[1]->name << " and " << players[3]->name;
        }
    }

    void shuffle(){
        cout << "Shuffling cards...\n";
        numleft = vector<int>(7, 8);
        
        random_shuffle(rocks.begin(), rocks.end());
        int k = 0;
        for(size_t i = 0; i < 4; ++i){
            if(players[i]->is_human){
                cout << players[i]->name << ", here is your hand:\n";
                for(size_t j = 0; j < 7; ++j){
                    cout << j << ":  [" << rocks[k].top << "|" << rocks[k].bottom <<"]\n";
                    players[i]->hand.push_back(rocks[k++]);
                }
            }
            else{
                for(size_t j = 0; j < 7; ++j){
                    players[i]->hand.push_back(rocks[k++]);
                }
            } 
            if(players[i]->fivedoubles()){
                cout << players[i]->name << " has at least 5 doubles, so we will reshuffle\n";
                for(auto it:players){
                    it->hand.clear();
                }
                return shuffle();
            }
        }
    }// shuffle

    bool no_hands_empty(){
        for(auto it:players){
            if(it->hand.empty()){
                return false;
            }
        }
        return true;
    }

    int play6_6(){
        int ind = 0;
        for(auto it:players){
            for(size_t i = 0; i < 7; ++i){
                if(it->hand[i].is6_6()){
                    cout << it->name << " plays [6|6]\n";
                    front = 6;
                    back = 6;
                    numleft[6] -= 2;
                    it->hand.erase(it->hand.begin() + i);
                    return (ind + 1)%4;
                }
            }
            ++ind;
        }
        return -1;
    }

    int start_cpu(int x, int y){
        sort(players[x]->hand.begin(), players[x]->hand.end());
        sort(players[y]->hand.begin(), players[y]->hand.end());   
        if(players[y]->hand.back() < players[x]->hand.back()){
            cout << "CPU " << players[x]->name << " plays [" << players[x]->hand.back().top << "|";
            cout << players[x]->hand.back().bottom << "]\n";
            front = players[x]->hand.back().top;
            back = players[x]->hand.back().bottom;
            --numleft[front];
            --numleft[back];
            players[x]->hand.pop_back();
            return (x+1)%4;
        }       
        else{
            cout << "CPU " << players[y]->name << " plays [" << players[y]->hand.back().top << "|";
            cout << players[y]->hand.back().bottom << "]\n";
            front = players[y]->hand.back().top;
            back = players[y]->hand.back().bottom;
            --numleft[front];
            --numleft[back];
            players[y]->hand.pop_back();
            return (y+1)%4;
        }
    }//start cpu

    int start_human(int x, int y){
        cout << "Which player would like to start?\n";
        cout << "Enter 0 for " << players[x]->name << " and 1 for " << players[y]->name << ":\n";
        int c;
        cin >> c;
        while(!(c == 0 || c == 1)){
            cout << "Error: you have entered an invalid number. Please try again.\n";
            cout << "Enter 0 for " << players[x]->name << " and 1 for " << players[y]->name << ":\n";
            cin >> c;
        }
        int i = (c == 0) ? x : y;
        size_t index = 0;
        cout << players[i]->name << ", Here is your hand\n";
        for(auto it:players[i]->hand){
            cout << index++ << " [" << it.top << "|" << it.bottom << "] \n"; 
        }
        cout << "Enter which number you would like to play:\n";
        cin >> index;
        while(index > 6){
            cout << "Error, that number does not exist, please try again:\n";
            cin >> index;
        }
        cout << players[i]->name << " plays [" << players[i]->hand[index].top << "|" << players[i]->hand[index].bottom << "]\n";
        front = players[i]->hand[index].top;
        back = players[i]->hand[index].bottom;
        --numleft[front];
        --numleft[back];
        players[i]->hand.erase(players[i]->hand.begin() + index);
        return (i + 1)%4;
    }//start human

    int start_cphum(int h, int c){
        auto rh = min_element(players[h]->hand.begin(), players[h]->hand.end());
        auto rc = min_element(players[c]->hand.begin(), players[c]->hand.end());
        if(*rh < *rc){
            cout << "CPU " << players[c]->name << " plays [" << (*rc).top << "|" << (*rc).bottom << "]\n";     
            front = (*rc).top;
            back = (*rc).top;      
            --numleft[(*rc).top];
            --numleft[(*rc).bottom];
            players[c]->hand.erase(rc);
            return (c+1)%4;
        }
        cout << players[h]->name << ", please select a card to start with\n";
        size_t index = 0;
        cout << "Here is your hand\n";
        for(auto it:players[h]->hand){
            cout << index++ << " [" << it.top << "|" << it.bottom << "] \n"; 
        }
        cout << "Enter which number you would like to play:\n";
        cin >> index;
        while(index > 6){
            cout << "Error, that number does not exist, please try again:\n";
            cin >> index;
        }
        cout << players[h]->name << " plays [" << players[h]->hand[index].top << "|" << players[h]->hand[index].bottom << "]\n";
        front = players[h]->hand[index].top;
        back = players[h]->hand[index].bottom;
        --numleft[front];
        --numleft[back];
        players[h]->hand.erase(players[h]->hand.begin() + index);
        return (h+1)%4;
    }//cphum


    int start_round(){
        shuffle();
        if(winner > 2){
            return play6_6();
        }
        else if(winner == 2){
            print_team(2);
            cout << " will start\n";
            if(!players[1]->is_human && !players[3]->is_human){
                return start_cpu(1, 3);
            }
            if(players[1]->is_human && players[3]->is_human){
                return start_human(1, 3);
            }
            if(players[1]->is_human && !players[3]->is_human){
                return start_cphum(1, 3);
            }
            else{
                return start_cphum(3, 1);
            }
        }
        else{
            print_team(1);
            cout << " will start\n";
            if(!players[0]->is_human && !players[2]->is_human){
                return start_cpu(0,2);
            }
            if(players[0]->is_human && players[2]->is_human){
                return start_human(0,2);
            }
            if(players[0]->is_human && !players[2]->is_human){
                return start_cphum(0, 2);
            }
            else{
                return start_cphum(2, 0);
            }
        }
    }//start round

    void empty_hand(int x){
        if(x == 1){
            if(players[0]->hand.empty()){
                cout << players[0]->name << " has no rocks left\n";
            }
            else{
                cout << players[2]->name << " has no rocks left\n";
            }
            round_victory(1);
        }
        else{
            if(players[1]->hand.empty()){
                cout << players[1]->name << " has no rocks left\n";
            }
            else{
                cout << players[3]->name << " has no rocks left\n";
            }
            round_victory(2);
        }
    }

    void tebla3_la3b(){
        cout << "Tebla3 la3b, ";
        cout << "No " << front << "'s or " << back << "'s remaining\n";
        int min1 = players[0]->sum_hand();
        int i1 = 0;
        int min2 = players[1]->sum_hand();
        int i2 = 1;
        int m1 = players[2]->sum_hand();
        int m2 = players[3]->sum_hand();
        for(size_t i = 0; i < 4; ++i){
            cout << players[i]->name << " has " << players[i]->sum_hand() << " remaining\n";
        }
        if(m1 < min1){
            min1 = m1;
            i1 = 2;
        }
        if(m2 < min2){
            min2 = m1;
            i2 = 3;
        }
        if(min1 < min2){
            cout << players[i1]->name << " of team 1 has the least remaining\n";
            winner = 1;
            round_victory(1);
        }
        else if(min1 > min2){
            cout << players[i2]->name << " of team 2 has the least remaining\n";
            winner = 2;
            round_victory(2);
        }
        else{
            cout << "Ma7roga, Team 1 has " << min1 << " and Team 2 has " << min2 << "\n";
            cout << "No points gained by either team\n";
            print_team(1);
            cout << " currently have " << t1points << " points and ";
            print_team(2);
            cout << " currently have " << t2points << " points\n";
            cout << "The goal is " << points_to_win;
            if(points_to_win > 1){
                cout << " points\n";
            }
            else{
                cout << " point\n";
            }
            winner = 3;
        }
        for(auto it:players){
            it->hand.clear();
        }
    }

    void round_victory(int x){
        if(x == 1){
            print_team(1);
            int pts = players[1]->sum_hand() + players[3]->sum_hand();
            cout << " win this round and gain " << pts << " points!\n";
            t1points += pts;
            print_team(1);
            cout << " currently have " << t1points << " points and ";
            print_team(2);
            cout << " currently have " << t2points << " points\n";
            cout << "The goal is " << points_to_win;
            if(points_to_win > 1){
                cout << " points\n";
            }
            else{
                cout << " point\n";
            }
        }
        else{
            print_team(2);
            int pts = players[0]->sum_hand() + players[2]->sum_hand();
            cout << " win this round and gain " << pts << " points!\n";
            t2points += pts;
            print_team(1);
            cout << " currently have " << t1points << " points and ";
            print_team(2);
            cout << " currently have " << t2points << " points\n";
            cout << "The goal is " << points_to_win;
            if(points_to_win > 1){
                cout << " points\n";
            }
            else{
                cout << " point\n";
            }
        }
    }

    void play_round(){
        cout << "New round beginning\n";
        int s = start_round();
        while(no_hands_empty()){
            if((numleft[front] < 1) && (numleft[back] < 1)){
                return tebla3_la3b();
            }
            else{
                tuple<int, int, Rock> tup = players[s]->play_rock(front, back);
                front = get<0>(tup);
                back = get<1>(tup);
                --numleft[get<2>(tup).top];
                --numleft[get<2>(tup).bottom];
            }
            s = (s+1)%4;
        }
        if(players[0]->hand.empty() || players[2]->hand.empty()){
            empty_hand(1);
            winner = 1;
        }
        else{
            empty_hand(2);
            winner = 2;
        }
        for(auto it:players){
            it->hand.clear();
        }
    }// play_round;

    void jeux(){
        while((t1points < points_to_win) && (t2points < points_to_win)){
            play_round();
        }//sequence of a full game
        if(t1points > points_to_win){
            print_team(1);
            cout << ", win the game with " << t1points << " points!\n";
            print_team(2);
            cout  << " had " << t2points << " points\n";
            cout << "Congratulations " << players[0]->name << " and " << players[2]->name << "\n";
        }
        else{
            print_team(2);
            cout << ", wins the game with " << t2points << " points!\n";
            print_team(1);
            cout  << " had " << t1points << " points\n";
            cout << "Congratulations " << players[1]->name << " and " << players[3]->name << "\n";
        }
        cout << "Thanks for playing Domino, by Youcef Ab\n";
        for(size_t u = 0; u < 4; ++u){
            delete players[u];
        }
    }// jeux function, main one

}; //jeux class

int main(){
    srand(static_cast<unsigned int>(time(0)));
    Jeux j;
    j.jeux();
    return 0;
}