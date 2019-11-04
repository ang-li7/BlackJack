#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;


struct Card {
    int value;
    string suit;
    string name;
};

void printCard(Card x){
    cout << x.name << " of " << x.suit << " ";
}

vector <Card> createDeck(){
    vector <Card> d;
    for(int i = 0; i<4; i++){
        string s;
        switch(i){
            case 0:
                s = "hearts";
                break;
            case 1:
                s = "spades";
                break;
            case 2:
                s = "diamonds";
                break;
            case 3:
                s = "clubs";
                break;
        }
        for(int j = 1; j<=13; j++){
            Card x;
            if (j == 1){
                x.value = 11;
                x.suit = s;
                x.name = "Ace";
            }
            else if(j ==11){
                x.value = 10;
                x.suit = s;
                x.name = "Jack";
            }
            else if(j ==12){
                x.value = 10;
                x.suit = s;
                x.name = "Queen";
            }
            else if(j ==13){
                x.value = 10;
                x.suit = s;
                x.name = "King";
            }
            else{
                x.value = j;
                x.suit = s;
                x.name = to_string(j);
            }
            d.push_back(x);
        }
    }
    return d;
}

void printDeck(vector <Card> d){
    for(int i = 0; i < d.size(); i++){
        printCard(d[i]);
    }
}

void shuffleDeck(vector <Card> *d){
    for (int i=0; i<52; i++){
        int r = rand()%52;
        Card x = (*d)[i];
        (*d)[i] = (*d)[r];
        (*d)[r] = x;
    }
}
int calculate(vector <Card> d){
    int tot = 0;
    int numOfAces = 0;
    for(int i = 0; i <d.size(); i++){
        tot = tot + d[i].value;
        if(d[i].value == 11){
            numOfAces = numOfAces + 1;
        }
    }
    if (tot > 21){
        tot = tot - numOfAces*10;
    }
    return tot;
}

struct Player {
    int playerNum;
    vector <Card> hand;
    bool cont;
};

void printPlayer(Player x){
    cout << x.playerNum << ": "<< calculate(x.hand) << "- ";
    printDeck(x.hand);
    cout << "\n";
}
bool CPU(vector <Card> hand){
    int val = calculate(hand);
    if (val < 17){
        return true;
    }
    else{
        return false;
    }
}
bool soft(vector <Card> hand){
    for(int i = 0; i<hand.size(); i++){
        if (hand[i].name == "Ace"){
            return true;
        }
    }
    return false;
}
bool PlayerMove(vector <Card> hand, Card dealer){
    int val = calculate(hand);
    if(soft(hand)){
        //cout << "SOFT\n";
        if (val <=17){
            return true;
        }
        else if(val == 18 && (dealer.value == 9 || dealer.value == 10 )){
            return true;
        }
        else{
            return false;
        }
    }
    
        if (val <=11){
            return true;
        }
        else if(val == 12){
            if(dealer.value <=3 || dealer.value >= 7){
                return true;
            }
            else{
                return false;
            }
        }
        else if(val >= 13 && val <= 16){
            if(dealer.value < 7){
                return false;
            }
            else{
                return true;
            }
        }
        else{
            return false;
        }
}
int winner(vector<Player> p){
    int highesthand = 0;
    int index = -1;
    for(int i = 0; i<p.size(); i++){
        if(calculate(p[i].hand) <= 21 && calculate(p[i].hand) > highesthand){
            highesthand = calculate(p[i].hand);
            index = i;
        }
    }
    if (index == -1){
        index = 0;
    }
    return index;
}
int main(){
    srand ( time(NULL) );
    int k;
    cout << "How many games do you want to simulate? \n";
    cin >> k;
    int numofPlayers = 1;
    cout << "Please enter the number of players (not including the dealer): ";
    cin >> numofPlayers;
    vector <int> Winners(numofPlayers+1);
    for(int g = 0; g<k; g++){
        cout << "*************** " << g << " **************\n";
        int index = 0;
        vector <Card> d = createDeck();
        shuffleDeck(&d);
        vector <Player> players;
        while(numofPlayers>20){
            cout << "Too many players \n";
            cin >> numofPlayers;
        }
        for(int i = 0; i<=numofPlayers; i++){
            Player x;
            x.playerNum = i;
            x.cont = true;
            for(int j = 0; j<2; j++){
                x.hand.push_back(d[index]);
                index = index + 1;
            }
            players.push_back(x);
        }
        bool game = true;
        while(game){
            game = false;
            for(int i = 1; i<=numofPlayers; i++){
                if(PlayerMove(players[i].hand, players[0].hand[0])){
                        game = true;
                        players[i].hand.push_back(d[index]);
                        index = index + 1;
                }
            }
            while(CPU(players[0].hand)){
                players[0].hand.push_back(d[index]);
                index = index + 1;
            }
        }
        for(int i = 0; i<=numofPlayers; i++){
            printPlayer(players[i]);
        }
        cout << "The winner of this game is Player ";
        printPlayer(players[winner(players)]);
        Winners[winner(players)] += 1;

    }
    cout << "\n";
    cout << "*********************\n";
    for(int g = 0; g <Winners.size(); g++){
        cout << Winners[g] << " " ;
    }
    cout << "\n*********************\n";


}

