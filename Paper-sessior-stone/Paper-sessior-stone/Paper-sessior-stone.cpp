// Paper-sessior-stone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cstdlib>
using namespace std;

enum enGame {
    scissors = 1,
    paper = 2,
    stone = 3
};

enum enWinner {
    user = 1,
    computer = 2,
    draw = 3
};

struct strRoundInfo {
    short RoundNumber = 0;
    enGame PlayerChoice1;
    enGame ComputerChoice1;
    enWinner gamewinner;
    string winnername = "";

};

struct strWinner {
    short Playerwin = 0;
    short Computerwin = 0;
    short Gameround = 0;
    short draw = 0;
    string winnername;
    enWinner gamewinner;
};

int ReadPositiveNumber(string message, int from, int to) {
    int number = 0;
    do {
        cout << message << '\n';
        cin >> number;
    } while (number < from || number > to);
    return number;
}

int RandomNumber(int from, int to) {
    int randnum = rand() % (to - from + 1) + from;
    return randnum;
}

enGame UserChoice() {
    int number2 = ReadPositiveNumber("Choose number [1]: scissors, [2]: paper, [3]: stone : ", 1, 3);
    return (enGame)number2;
}

enGame ComputerChoice() {
    return (enGame)RandomNumber(1, 3);
}

enWinner whowin(strRoundInfo roundinfo) {
    if (roundinfo.PlayerChoice1 == roundinfo.ComputerChoice1) {
        return enWinner::draw;
    }

    switch (roundinfo.ComputerChoice1) {
    case enGame::stone:
        if (roundinfo.PlayerChoice1 == enGame::paper) {
            return enWinner::user;
        }
        break;
    case enGame::scissors:
        if (roundinfo.PlayerChoice1 == enGame::stone) {
            return enWinner::user;
        }
        break;
    case enGame::paper:
        if (roundinfo.PlayerChoice1 == enGame::scissors) {
            return enWinner::user;
        }
        break;
    }

    return enWinner::computer;
}
void Reset() {
    system("cls");
    system("color 0F");
}

void setcolorscreencolor(enWinner win) {
    switch (win) {
    case enWinner::computer:
        system("Color 4F");
        break;
    case enWinner::user:
        system("Color 2F");
        break;
    default:
        system("Color 6F");
        break;
    }
}

string Tab(short number) {
    string t = "";
    for (short i = 0; i < number + 1; i++) {
        t += "\t";
    }
    return t;
}


string winnername(enWinner win) {
    string arrnamewinner[3] = { "Player", "Computer", "No winner" };
    return arrnamewinner[win - 1];

}

string gamename(enGame game) {
    string arrgame[3] = { "scissors", "paper", "stone" };
    return arrgame[game - 1];
}

enWinner CheckWinner(short Computerwin, short Playerwin) {

    if (Computerwin > Playerwin) {
        return enWinner::computer;
    }
    else if (Computerwin < Playerwin) {
        return enWinner::user;
    }
    else {
        return enWinner::draw;
    }
}

void ShowRoundGameResult(strRoundInfo gamewinner1) {

    cout << Tab(2) << "______________[Round Result]__________________\n";
    cout << Tab(2) << "Round number: " << gamewinner1.RoundNumber << endl;
    cout << Tab(2) << "Computer choice: " << gamename(gamewinner1.ComputerChoice1) << endl;
    cout << Tab(2) << "Player choice: " << gamename(gamewinner1.PlayerChoice1) << endl;
    cout << Tab(2) << "Winner: " << winnername(gamewinner1.gamewinner) << endl;
    setcolorscreencolor(gamewinner1.gamewinner);

}

strWinner ShowFinalGameResults(short Computerwin, short Playerwin, short draw, short round, string finalwinner) {
    strWinner gameresult;
    strRoundInfo gamewinner;
    cout << Tab(2) << "_____________[Game Results]_________________" << endl;
    gameresult.Computerwin = Computerwin;
    gameresult.Playerwin = Playerwin;
    gameresult.draw = draw;
    gameresult.Gameround = round;
    gameresult.winnername = finalwinner;
    cout << Tab(2) << "Round number: " << gameresult.Gameround << endl;
    cout << Tab(2) << "Computer won: " << gameresult.Computerwin << endl;
    cout << Tab(2) << "Player won: " << gameresult.Playerwin << endl;
    cout << Tab(2) << "Draws: " << gameresult.draw << endl;
    if (Computerwin > Playerwin) {
        gameresult.winnername = "Computer";
    }
    else if (Computerwin < Playerwin) {
        gameresult.winnername = "Player";
    }
    else {
        gameresult.winnername = "No winner";
    }
    cout << Tab(2) << "Final winner: " << gameresult.winnername << endl;

    return gameresult;
}

strWinner startgame(short round) {
    strRoundInfo gamewinner2;
    strWinner winner;
    short Computerwin = 0;
    short Playerwin = 0;
    short draw = 0;
    string finalwinner = "";
    for (short Gameround = 1; Gameround <= round; Gameround++) {

        gamewinner2.RoundNumber = Gameround;
        gamewinner2.ComputerChoice1 = ComputerChoice();
        gamewinner2.PlayerChoice1 = UserChoice();
        gamewinner2.gamewinner = whowin(gamewinner2);


        if (gamewinner2.gamewinner == enWinner::computer) {
            Computerwin++;
        }
        else if (gamewinner2.gamewinner == enWinner::user) {
            Playerwin++;
        }
        else if (gamewinner2.gamewinner == enWinner::draw) {
            draw++;
        }

        ShowRoundGameResult(gamewinner2);

    }

    return ShowFinalGameResults(Computerwin, Playerwin, draw, round, finalwinner);
}

void showGameOverScreen() {
    cout << Tab(2) << "__________+++++[Game Over]+++++______________\n";
    cout << Tab(2) << "_____________________________________________\n";
}

void StartGame() {
    char start = 'y';
    do {
        startgame(ReadPositiveNumber("Choose number of rounds between 1 and 10: ", 1, 10));
        cout << "Do you want to play again (y/n)?\n";
        cin >> start;
        Reset();
    } while (start == 'y' || start == 'Y');
    showGameOverScreen();
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
