// This file contains the player class implementations. 
// There are two derived classes, CPU and Human which from the base player(joueur) class
#include "jouer.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// CPU class
class Cpu : public Jouer{

    private:

    public:
    vector<Rock> hand;
    string name;
    bool is_human;

    Cpu(string name_in, bool h_in): name(name_in), is_human(h_in){}

    // play_rock chooses which rock to play for the CPU
    virtual tuple<int, int, Rock> play_rock(int front, int back){
        cout << "It is CPU " << name << "'s turn\n";
        Rock r = {7,7};
        sort(Jouer::hand.begin(), Jouer::hand.end());
        reverse(Jouer::hand.begin(), Jouer::hand.end());
        size_t prevsize = Jouer::hand.size();
        auto it1 = Jouer::hand.begin();
        cout << "Current rocks in play:\n";
        cout << "[" << front << "\n";
        cout << back << "]\n";
        for(auto it:Jouer::hand){
            if(it.top == front){
                cout << "CPU " << name << " plays [" << it.bottom << "|" << it.top << "] on [" << front << "\n";
                front = it.bottom;
                r = it;
                Jouer::hand.erase(it1);
                break;
            }
            else if(it.bottom == front){
                cout << "CPU " << name << " plays [" << it.top << "|" << it.bottom << "] on [" << front << "\n";
                front = it.top;
                r = it;
                Jouer::hand.erase(it1);
                break;
            }
            else if(it.top == back){
                cout << "CPU " << name << " plays [" << it.bottom << "|" << it.top << "] on [" << back << "\n";
                back = it.bottom;
                r = it;
                Jouer::hand.erase(it1);
                break;
            }
            else if(it.bottom == back){
                cout << "CPU " << name << " plays [" << it.top << "|" << it.bottom << "] on [" << back << "\n";
                back = it.top;
                r = it;
                Jouer::hand.erase(it1);
                break;
            }
            ++it1;
        }
        if(Jouer::hand.size() == prevsize){
            cout << "CPU " << name << " tiaret \n";
        }
        return {front, back, r};
    }// play_rock

    // play_first chooses which rock for the cpu to play if they are the first to play in the round
    virtual Rock play_first(){
        sort(hand.begin(), hand.end());
        Rock r = hand.back();
        hand.pop_back();
        cout << "CPU " << name << " plays [" << r.top << "|" << r.bottom << "]";
        return r;
    }// play_first

    // sums the total number of each rock in the hand
    virtual int sum_hand(){
        int sum = 0;
        for(auto it:Jouer::hand){
            sum += it.top;
            sum += it.bottom;
        }
        return sum;
    }//sum hand

    // checks to see if there are 5 doubles in the hand
    virtual bool fivedoubles(){
        int doubles = 0;
        for(auto it:Jouer::hand){
            if(it.top == it.bottom){
                ++doubles;
            }
        }
        if(doubles > 4){
            return true;
        }
        return false;
    }//5 doubles
    
};// CPU class

// the human class (for human players)
class Human : public Jouer{

    private:
    public:

    vector<Rock> hand;
    string name;
    bool is_human;

    Human(string name_in, bool h_in): name(name_in), is_human(h_in){}

    // play_rock allows the human to choose what rock to play, but makes sure they play a valid rock
    virtual tuple<int, int, Rock> play_rock(int front, int back){
        cout << name << ", it is your turn\n";
        Rock r = {7,7};
        size_t index = 0;
        cout << name << ", Here is your hand\n";
        
        for(auto it:Jouer::hand){
            cout << index++ << " [" << it.top << "|" << it.bottom << "] \n"; 
        }
        cout << index << " Pass\n";
        cout << "Current rocks in play:\n";
        cout << "f: [" << front << "\n";
        cout << "b: " << back << "]\n";
        cout << "p: Pass\n";
        cout << "Enter which number you would like to play:\n";
        cin >> index;
        while(index > Jouer::hand.size()){
            cout << "Error, that number does not exist, please try again:\n";
            cin >> index;
        }
        cout << "Enter which location to place your chosen rock (f/b/p)\n";
        char loc;
        cin >> loc;
        while(!((loc == 'f') || (loc == 'b') || (loc == 'p'))){
            cout << "Error, unrecognized location. Please only enter either f, b, or p (pass):\n";
            cin >> loc;
        }
        if(index == Jouer::hand.size()){
            if(loc != 'p'){
                cout << "Error: You have selected to pass and not pass, please try again\n";
                cout << "\n";
                return play_rock(front, back);
            }
            for(auto it1:Jouer::hand){
                if((it1.top == front) || (it1.top == back) || (it1.bottom == front) || (it1.bottom == back)){
                    cout << "Error: You cannot pass, please try again\n";
                    cout << "\n";
                    return play_rock(front, back);
                }
            }
            cout << name << " tiaret\n";
            return {front, back, r};
        }
        if(loc == 'p'){
            cout << "Error: You have selected to not pass and pass, please try again\n";
            cout << "\n";
            return play_rock(front, back);
        }
        int comp = (loc == 'f') ? front : back;
        if(!((Jouer::hand[index].top == comp) || Jouer::hand[index].bottom == comp)){
            cout << "Error: You have made an invalid selection, please try again\n";
            cout << "\n";
            return play_rock(front, back);
        }
        bool played = false;
        if(loc == 'f'){
            if(Jouer::hand[index].top == front){
                cout << name << " plays [" << Jouer::hand[index].bottom << "|" << Jouer::hand[index].top << "] on [" << front << "\n";
                front = Jouer::hand[index].bottom;
                r = Jouer::hand[index];
                Jouer::hand.erase(Jouer::hand.begin() + index);
                played = true;
            }
            else if(Jouer::hand[index].bottom == front){
                cout << name << " plays [" << Jouer::hand[index].top << "|" << Jouer::hand[index].bottom << "] on [" << front << "\n";
                front = Jouer::hand[index].top;
                r = Jouer::hand[index];
                Jouer::hand.erase(Jouer::hand.begin() + index);
                played = true;
            }
        }
        else{
            if(Jouer::hand[index].top == back){
                cout << name << " plays [" << Jouer::hand[index].bottom << "|" << Jouer::hand[index].top << "] on [" << back << "\n";
                back = Jouer::hand[index].bottom;
                r = Jouer::hand[index];
                Jouer::hand.erase(Jouer::hand.begin() + index);
                played = true;
            }
            else if(Jouer::hand[index].bottom == back){
                cout << name << " plays [" << Jouer::hand[index].top << "|" << Jouer::hand[index].bottom << "] on [" << back << "\n";
                back = Jouer::hand[index].top;
                r = Jouer::hand[index];
                Jouer::hand.erase(Jouer::hand.begin() + index);
                played = true;
            }
        }
        if(!played){
            cout << "Error: You have made an invalid selection, please try again\n";
            cout << "\n";
            return play_rock(front, back);
        }
        return {front, back, r};
    }// play_rock

    // play_first allows the human to choose what cared to play if they are going first in the round
    virtual Rock play_first(){
        size_t index = 0;
        cout << name << ", Here is your hand\n";
        for(auto it:hand){
            cout << index++ << " [" << it.top << "|" << it.bottom << "] \n"; 
        }
        cout << "Select a rock to play:\n";
        size_t i;
        cin >> i;
        while(i >= hand.size()){
            cout << "Error: You have made an invalid selection, please try again\n";
            cin >> i;
        }
        Rock r = hand[i];
        cout << name << " plays [" << hand[i].top << "|" << hand[i].bottom << "]";
        hand.erase(hand.begin() + i);
        return r;
    }//play_first

    // sums the total number of each rock in the hand
    virtual int sum_hand(){
        int sum = 0;
        for(auto it:Jouer::hand){
            sum += it.top;
            sum += it.bottom;
        }
        return sum;
    }// sum hand

    // returns true if there are 5 doubles in the hand
    virtual bool fivedoubles(){
        int doubles = 0;
        for(auto it:Jouer::hand){
            if(it.is_double()){
                ++doubles;
            }
        }
        if(doubles > 4){
            return true;
        }
        return false;
    }//5 doubles


};// human class

// constructs a new player
Jouer* Jouer_constructor(string name_in, bool human){
    if(human){
        return new Human(name_in, true);
    }
    else{
        return new Cpu(name_in, false);
    }
}