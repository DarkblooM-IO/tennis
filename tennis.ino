#include <LiquidCrystal.h>
#include <PinButton.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal LCD(7, 8, 9, 10, 11, 12);

PinButton P1_BTN(2);
PinButton P2_BTN(3);

const String SCORE_LIST[5] = {
  "00",
  "15",
  "30",
  "40",
  "AV"
};

class Player {
  public:
    String name;
    int score;
    int game;
    int set;
    int match;
    bool serv;
  
    Player(String name_, bool serv_ = false) {
      name = name_;
      score = 0;
      game = 0;
      set = 0;
      match = 0;
      serv = serv_;
    }
  
    void increment_score() {
      if (score < 4)
        score++;
    }

    void decrement_score() {
      if (score > 0)
        score--;
    }
  
    void set_serv(bool val) {
      serv = val;
    }
};

Player p1("P1");
Player p2("P2");

void display(Player &player);
void display(Player &player) {
  String serv = player.serv ? "X" : " ";
  LCD.print(serv // is player serving
            + " "
            + player.name // player name
            + " "
            + SCORE_LIST[player.score] // player score
            + " "
            + player.game // game
            + " "
            + player.set // set
            + " "
            + player.match); // match
}

void setup() {
  LCD.begin(16, 2);
}

void loop() {
  display(p1);
  LCD.setCursor(0, 1);
  display(p2);
  LCD.setCursor(0, 0);

  P1_BTN.update();
  P2_BTN.update();

  // single click to increment score
  if (P1_BTN.isSingleClick()) {
    p1.increment_score();
  }
  
  if (P2_BTN.isSingleClick()) {
    p2.increment_score();
  }

  // double click to decrement score
  if (P1_BTN.isDoubleClick())
    p1.decrement_score();
    
  if (P2_BTN.isDoubleClick())
    p2.decrement_score();

  // long click to set serving
  if (P1_BTN.isLongClick()) {
    p1.serv = true;
    p2.serv = false;
  }

  if (P2_BTN.isLongClick()) {
    p2.serv = true;
    p1.serv = false;
  }
}
