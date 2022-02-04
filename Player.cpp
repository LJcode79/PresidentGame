#include <string>
#include <iostream>
#include "Player.h" 
using namespace std;

Player::Player(){
  this->name = "Player 0";

  srand(time(NULL));
  int partyNum = rand() % 2;
  if (partyNum == 0){
  this->party = "R";
  }
  else if(partyNum == 1){
  this->party = "D";
  }
  else{
    this->party = "T";
  }

  this->score = 0;
}

Player::Player(string name,string party){
  this->name = name;
  this->party = party;
  this->score = 0;
}

string Player::getName(){
  return this->name;
}

string Player::getParty(){
  return this->party;
}

int Player::getScore(){
  return this->score;
}

void Player::lowerScore(int num){
  this->score -= num;
  if (this->score < 0){
    this->score = 0;
  }
}

void Player::raiseScore(int num){
  this->score += num;
}

void Player::roll(){
  int result;
  srand(time(NULL));
  result = rand() % 12 + 1;//rolls in the range of 1-12
  cout << "The dice read: " << result << endl << endl;
  cout << "Adding " << result << " to " << this->name << "'s score"<<endl;
  this->score+=result; 
}
