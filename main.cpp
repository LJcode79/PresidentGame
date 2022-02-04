#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "Player.h"
using namespace std;

bool checkWinner(Player list[],int candidates);
string getWinner(Player list[],int candidates);
void displayMenu();
void randomEvent(Player player, Player list[],int currentPos);

int main() {
  srand(time(NULL));
  int candidates;
  int round = 1;
  int reset = 0;
  int choice;
  string myName;
  string myParty;
  while (reset == 0){
  cout << "Welcome to the election game!" << endl;

  //Add option to show rules
  char seeRule = 'n';
  cout << "Would you like to see the list of rules?(y/n)" << endl;
  cin >> seeRule;
  if (seeRule == 'y'){
    cout << "---------------------" << endl << "RULES" << endl << "---------------------" << endl << "-The Election Game is a game which simulates a presidential election. " << endl << endl << "-Each candidate is given a turn each round. "<< endl << endl << "-One of the candidates is selected at random to become incumbent president at the beginning of each game. The incumbent recieves 10 points for free due to the incumbency advantage" << endl << endl << "-The goal of the game is to reach 270 points, representing 270 electors in a real election" << endl << endl << "-During each turn, the candidate is given 6 actions to choose from" << endl << endl << "-Every 10 points between 0 and 270 triggers an \"EVENT\" which may prompt you to take action" << endl << endl << "-Rolling the dice: add 1-12 to your score depending on the roll." << endl << endl << "-Run ads against an opponent: use your turn, but take 3 points away from a candidate of your choice. " << endl << endl << "-Host a fundraising event: there is a 10% chance your fundraiser may go bad, in that case, 5 points will be deducted from your score. Otherwise 7 points will be added." << endl << endl << "-Debate a candidate: Debate a candidate of your choice, the challenger of the debate has a 60% chance of winning. " << endl << endl << "End of rules" << endl << endl << "---------------------" << endl << endl;
  }

  cout << "Enter the number of candidates that would like to participate in the election: ";
  while (candidates <= 1){
  cin >> candidates;
    if (candidates <= 1) {
      cout << "Error: Need at least 2 candidates. Try again" << endl;
    }
  }
  cout << endl;
  Player playerList[100];
    for (int i = 1; i <= candidates; i++){
      cout << "Enter the name of candidate number " << i << ": ";
      cin >> myName;

      cout << "Enter the political party of " << myName << " (R for Republican, D for Democrat, T for Third) " << ": ";
      myParty = "y";
      while ((myParty != "R") && (myParty!="D") && (myParty != "T")){
      cin >> myParty;
        if ((myParty != "R") && (myParty!="D") && (myParty != "T")){
          cout << "Error, not a valid political party. Try again" << endl;
        }
      }

      Player player(myName,myParty);
      playerList[i] = player;
    }
      int static incumbent = rand() % candidates + 1;
      cout << endl << "The current president, " << playerList[incumbent].getName() << ", starts with \n10 points because they are the incumbent. " << endl;
      playerList[incumbent].raiseScore(10);
    while(checkWinner(playerList,candidates)!=true){
      cout << endl;
      for (int i = 1; i <= candidates; i++){
      cout << endl << "------------------------" << endl;
      cout << "Round " << round << ", " << playerList[i].getName() << "'s turn:  " << endl;
      
      cout << endl << "Current candidate leaderboard: " << endl;
      cout << "num" << setw(15) << "name"  << setw(15) << "score" << endl;
      for (int i = 1; i <= candidates; i++){
        cout << left << i <<setw(13) << ". " << setw(14) << playerList[i].getName() << playerList[i].getScore() << endl; 
      }
      cout << right;
      cout << endl;

      displayMenu();
      cin >> choice;
      cout << endl;

        if (choice == 1){
          playerList[i].roll();
        }
        else if (choice == 2){
          int temp;
          temp = i;
          while (temp == i){
          cout << "Enter the number of the candidate you want to run ads  against: " << endl;
            for (int n = 1; n <= candidates; n++){
              if (n != i){
              cout << n << ". " << playerList[n].getName() << endl;
              }
            }
            cin >> temp;
            if (temp == i){
              cout << "Error, you can't run ads against yourself, choose another candidate!" << endl;
            }
          }
          cout << "Bad ad went well! Lowering " << playerList[temp].getName() << "'s score by 3." << endl;
          playerList[temp].lowerScore(3);
        }
        else if (choice == 3){
          int fundraise = rand() % 10;//rolls in the range of 0-9
          if (fundraise == 9){
            cout << "Fundraising went bad! -5 points to score." << endl;
            playerList[i].lowerScore(5);
          }
          else{
            cout << "Fundraising went well! +7 points to score." << endl;
            playerList[i].raiseScore(7);
          }
        }
        else if (choice == 4){
          int temp;
          int winChance;
          cout << "Enter the number of the candidate you want to debate: " << endl;
          temp = i;
          while (temp == i){
            for (int n = 1; n <= candidates; n++){
              if (n!= i){
              cout << n << ". " << playerList[n].getName() << endl;
              }
            }
            cin >> temp;
            if (temp == i){
              cout << "Error, you cannot debate yourself, enter another candidate!" << endl;
            }
          }
          winChance = rand() % 10; //rolls in the range of 0-9
          if (winChance <= 5){
            cout << playerList[i].getName() << " has won the debate! Raising " << playerList[i].getName() << "'s score by 10 and lowering " << playerList[temp].getName() << "'s score by 10" << endl;
            playerList[temp].lowerScore(10);
            playerList[i].raiseScore(10);
          }
          else{
            cout << playerList[temp].getName() << " has won the debate! Raising " << playerList[temp].getName() << "'s score by 10 and lowering " << playerList[i].getName() << "'s score by 10" << endl;
            playerList[i].lowerScore(10);
            playerList[temp].raiseScore(10);
          }
        }
        else if (choice == 5){ //Display player with most points
           cout << endl << "Game ended early. Congratulations " << getWinner(playerList,candidates) << ", you are the next President! " << endl;
           exit(0);
        }
        else {
          playerList[i].roll();
        }

        if ((playerList[i].getScore()%15 == 0) && (playerList[i].getScore() > 0)){
          cout << endl << "**Landed on an event tile! Drawing an event.**" << endl;
          randomEvent(playerList[i], playerList, i);
        }
      }

      round++;
    }
    cout << "Congratulations " << getWinner(playerList,candidates) << ", you are the next President! " << endl;
    char resQ;
    cout << "Play again? (y/n)" << endl;
    cin >> resQ;
    if (resQ == 'y') {
      reset = 0;
      incumbent = 0;
    }
    else {
      reset = 1;
    }
  }
} 

void displayMenu(){
  cout << "1. Roll dice" << endl << "2. Run ads against a candidate" << endl <<  "3. Host a fundraising event" << endl << "4. Debate a candidate " << endl << "5. End Game" << endl  << "Enter a number to use your turn: ";
}

void randomEvent(Player player, Player list[], int currentPos){
 int qNum = rand() % 10;
 
  if (qNum == 0){//news media, liberal news +5 pts D -5 pts R
    int rNum = rand() % 1;
    if (rNum == 0){//CNN
      cout << "EVENT: You were just on CNN! Your approval ratings have changed by ";
      if(player.getParty() == "R"){
        cout << "-5" << endl;
        player.lowerScore(5);
      }
      else if(player.getParty() == "D"){
        cout << "+5" << endl;
        player.lowerScore(5);
      }
      else {
        cout << "0" << endl;
      }
    }
    else{//fox
      cout << "EVENT: You were just on Fox News! Your approval ratings have changed by ";
      if(player.getParty() == "R"){
          cout << "+5" << endl;
          player.lowerScore(5);
        }
        else if(player.getParty() == "D"){
          cout << "-5" << endl;
          player.lowerScore(5);
        }
        else {
          cout << "0" << endl;
        }
    }
  }
  if (qNum == 1){//Political protests, support police or protestors? changes depend on party
    int protestChoice;
    cout << "EVENT: A protest just happened in one of your State's inner cities. Do you:\n1) Address the concern of the protestors \n2) Support the police breaking up the protest? \npick a number: ";
    cin >> protestChoice;
    cout << endl;
    if (protestChoice == 1) {
      if (player.getParty() == "R"){
        cout << "Your party didn't like that very much. -2 points" << endl;
        player.lowerScore(2);
      }
      else if (player.getParty() == "D"){
        cout << "Your party liked that! +2 points" << endl;
        player.raiseScore(2);
      }
      else{
        cout << "Your party liked that! +1 point" << endl;
        player.raiseScore(1);
      }
    }
    else{
      if (player.getParty() == "D"){
        cout << "Your party didn't like that very much. -2 points" << endl;
        player.lowerScore(2);
      }
      else if (player.getParty() == "R"){
        cout << "Your party liked that! +2 points" << endl;
        player.raiseScore(2);
      }
      else{
        cout << "Your party liked that! +1 point" << endl;
        player.raiseScore(1);
      }
    }
  }
  if (qNum == 2){//PAC decided to support you +10 points
    cout << "EVENT: A super PAC endorsed you! +10 points!" << endl;
    player.raiseScore(10);
  }
  if (qNum == 3){//Endorsed by random party colleague colleague is of same party +10
    cout << "EVENT: A famous party member just endorsed you!" << endl;
    int colleagueNum = rand() % 2;
    if (player.getParty() == "R"){
      if (colleagueNum == 0){
        cout << "Donald Trump just endorsed you! +15 points!" << endl;
        player.raiseScore(15);
      }
      else if(colleagueNum == 1){
        cout << "George W. Bush just endorsed you! +10 points!" << endl;
        player.raiseScore(10);
      }
      else{
        cout << "Mitch McConnell just endorsed you! +5 points!" << endl;
        player.raiseScore(5);
      }
    }
    else if(player.getParty() == "D"){
      if (colleagueNum == 0){
        cout << "Barack Obama just endorsed you! +15 points!" << endl;
        player.raiseScore(15);
      }
      else if(colleagueNum == 1){
        cout << "Joe Biden just endorsed you! +10 points!" << endl;
        player.raiseScore(10);
      }
      else{
        cout << "Nancy Pelosi just endorsed you! +5 points!" << endl;
        player.raiseScore(5);
      }
    }
    else{
      if (colleagueNum == 0){
        cout << "Bernie Sanders just endorsed you! +15 points!" << endl;
        player.raiseScore(15);
      }
      else if(colleagueNum == 1){
        cout << "Angus King just endorsed you! +10 points!" << endl;
        player.raiseScore(10);
      }
      else{
        cout << "Vermin Supreme just endorsed you! +5 points!" << endl;
        player.raiseScore(5);
      }
    }
  }
  if (qNum == 4){//Tragedy occurs, visit place?
    int tragedyNum = rand() % 2;
    if (tragedyNum == 0){
      cout << "EVENT: The west coast of the USA has been hit by a Tsunami and a lot of people died. ";
    }
    else if (tragedyNum == 1){
      cout << "EVENT: An earthquake destroyed a hospital in the midwest. ";
    }
    else if (tragedyNum == 2){
      cout << "EVENT: The east coast has become a popsicle, many freeze to death.";
    }
    cout << "Do you go and visit? (y/n)" << endl;
    char tragChoice;
    cin >> tragChoice;
    if (tragChoice == 'y'){
      cout << "The public liked that! +7 points" << endl;
      player.raiseScore(7);
    }
    else{
      cout << "The public was wondering why you haven't addressed the tragedy! -2 points";
      player.lowerScore(2);
    }
  }
  if (qNum == 5){//Marijuanna legislation change score depends on party
    int mjNum;
    cout << "EVENT: Laws have been proposed which favor the legalization of Marijuanna. Do you \n1) Support it \n2) Oppose it \nEnter a number: ";
    cin >> mjNum;
    if (mjNum == 1){
      cout << "The majority of America agrees with you. +5 points " << endl;
      player.raiseScore(5);
    }
    else{
      cout << "Unfortunately the majority of America does not agree with you. -5 points " << endl;
    }
    player.lowerScore(5);
  }
  if (qNum == 6){//a PAC decided to run a shadow campaign against you -10 points
    cout << "EVENT: A super PAC decided to run negative advertisements against you as part of a shadow campaign! -10 points" << endl;
    player.lowerScore(10);
  }
  if (qNum == 7){//Gun restriction laws proposed, support or oppose? change depends on party
    int gunNum;
    cout << "EVENT: New laws which make it harder to own guns are being proposed in your area. Do you: \n1)Support them \n2)Oppose them \nEnter a number: ";
    cin >> gunNum;
    if (gunNum == 1){
      if (player.getParty() == "D"){
        cout << "Your party didn't like that very much. -2 points" << endl;
        player.lowerScore(2);
      }
      else if (player.getParty() == "R"){
        cout << "Your party liked that! +2 points" << endl;
        player.raiseScore(2);
      }
      else{
        cout << "Your party liked that! +1 point" << endl;
        player.raiseScore(1);
      }
    }
    else{
       if (player.getParty() == "R"){
        cout << "Your party didn't like that very much. -2 points" << endl;
        player.lowerScore(2);
      }
      else if (player.getParty() == "D"){
        cout << "Your party liked that! +2 points" << endl;
        player.raiseScore(2);
      }
      else{
        cout << "Your party did not like that! -1 point" << endl;
        player.lowerScore(1);
      }
    }
  }
  if (qNum == 8){//You are trending on social media +20
    cout << "EVENT: You have become the face of a meme on the internet! Your name recognition skyrockets and everyone is talking about you. +20 points!" << endl;
    player.raiseScore(20);
  }
  if (qNum == 9){//Volunteers canvass for you +15
    cout << "EVENT: Volunteers are inspired by your message go out and preach your campaign calls. +15 points" << endl;
    player.raiseScore(15);
  }
  if (qNum == 10){//Scandal! -15
    cout << "EVENT: Scandal! You did something you didn't want any one to see! You also spent a lot of money trying to cover it up to stay in the race. -15 points." << endl;
    player.lowerScore(15);
  }
  if (qNum == 11){//Appearance in public, decide where to go
    int publicNum;
    cout << "EVENT: You decide to walk around your community to build PR. Where do you go? \n1)The beach \n2)Local donut shop \n3)A Public School \n4)A food shelter \n\nPick a number: ";
    cin >>  publicNum;
    cout << endl;
    if (publicNum == 1){
      cout << "You go to the beach. Theres nothing to do but sit around and gaze in the sunset. +1 point" << endl;
      player.raiseScore(1);
    }
    else if (publicNum == 2){
      cout << "You go to the local donut shop and befriend the owner! +5 points" << endl;
      player.raiseScore(5);
    }
    else if (publicNum == 3){
      cout << "You go to the public school and build relations with the faculty and students. +5 points" << endl;
      player.raiseScore(5);
    }
    else if (publicNum == 4){
      cout << "You go to the food shelter and help distribute food. You are thanked for being a good person. +5 points" << endl;
      player.raiseScore(5);
    }
  }
  if (qNum == 12){//got sick
    cout << "EVENT: You contracted a variant of COVID! take some time off. -7 points" << endl;
    player.lowerScore(7);
  }
  if (qNum == 13){//Fracking laws proposed
    int frackNum;
    cout << "EVENT: laws are being proposed to allow oil companies to drill land in your area. Do you \n1)Support it \n2)Oppose it \nPick a number: ";
    cin >> frackNum;
    cout << endl;
    if (frackNum == 1){
      if (player.getParty() == "D"){
        cout << "Your party didn't like that very much. -5 points" << endl;
        player.lowerScore(5);
      }
      else if (player.getParty() == "R"){
        cout << "Your party liked that! +5 points" << endl;
        player.raiseScore(5);
      }
      else{
        cout << "Your party didn't like that very much. -2 points" << endl;
        player.lowerScore(2);
      }
    }
    else{
       if (player.getParty() == "R"){
        cout << "Your party didn't like that very much. -2 points" << endl;
        player.lowerScore(2);
      }
      else if (player.getParty() == "D"){
        cout << "Your party liked that! +6 points" << endl;
        player.raiseScore(6);
      }
      else{
        cout << "Your party did not like that! -3 point" << endl;
        player.lowerScore(3);
      }
    }
  }
  if (qNum == 14){//Abortion laws proposed
  int abortNum;
    cout << "EVENT: laws are being proposed to ban abortion in your area. Do you \n1)Support the ban \n2)Oppose the ban \nPick a number: ";
    cin >> abortNum;
    cout << endl;
    if (abortNum == 1){
      if (player.getParty() == "D"){
        cout << "Your party didn't like that very much. -4 points" << endl;
        player.lowerScore(4);
      }
      else if (player.getParty() == "R"){
        cout << "Your party liked that! +6 points" << endl;
        player.raiseScore(6);
      }
      else{
        cout << "Your party liked that! +2 points" << endl;
        player.raiseScore(2);
      }
    }
    else{
       if (player.getParty() == "R"){
        cout << "Your party didn't like that very much. -4 points" << endl;
        player.lowerScore(4);
      }
      else if (player.getParty() == "D"){
        cout << "Your party liked that! +6 points" << endl;
        player.raiseScore(6);
      }
      else{
        cout << "Your party did not like that! -3 points" << endl;
        player.lowerScore(3);
      }
    }
  }
}

string getWinner(Player list[],int candidates){
  Player winner = list[1];
  for (int i = 1; i <= candidates; i++){
    if (list[i].getScore() > winner.getScore()){
    winner = list[i];
    }
  }
  return winner.getName();
}

bool checkWinner(Player list[],int candidates){
  for (int i = 1; i <= candidates; i++){
    if (list[i].getScore() >= 270){
    return true;
    }
  }
  return false;
}