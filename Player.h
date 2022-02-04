#ifndef PLAYER_H
#define PLAYER_H
using namespace std;

class Player{
  private:
    //static int PLAYERNUM = 1;
    string name;
    string state;
    string culture;
    string party;
    int score;
  public:
    Player();
    Player(string name,string state);
    string getName();
    string getParty();
    int getScore();
    void lowerScore(int num);
    void raiseScore(int num);
    void roll();
};

#endif