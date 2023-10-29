#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

const int row = 10;
char board[row][row];

class Player {
public:
    char publicBoard[row][row] = {0};
    char privateBoard[row][row] = {0};
    int smallShips = 3;
    int mediumShips = 2;
    int hugeShips = 1;
    int points = 0;
    bool winner = false;

    void publicBoardCreate() {
        publicBoard[0][0] = ' ';
        for (int i = 1; i < row; i++) {
            publicBoard[0][i] = 'a' + i - 1;
        }
        for (int i = 1; i < row; i++) {
            publicBoard[i][0] = i + '0';
        }
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < row; j++) {
                publicBoard[i][j] = '?';
            }
        }
    }

    void privateBoardCreate() {
        privateBoard[0][0] = ' ';
        for (int i = 1; i < row; i++) {
            privateBoard[0][i] = 'a' + i - 1;
        }
        for (int i = 1; i < row; i++) {
            privateBoard[i][0] = '0' + i;
        }
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < row; j++) {
                privateBoard[i][j] = 'o';
            }
        }
    }

    void setUpBoard() {
        int x, y, lastX = 0, lastY = 0;
        for (int i = 0; i < smallShips; i++) {
            privateBoardView();
            cout << "Podaj koordynaty " << i + 1 << " malego statku na planszy [9,9]\n";
            cin >> x >> y;
            this_thread::sleep_for(chrono::milliseconds (100));
            if (x < 1 || y < 1) {
                cout << "Koordynaty musza byc wieksze od 0 i mniejsze od 11\n";
                cin >> x >> y;
            }
            if (privateBoard[x][y] == 'o') {
                privateBoard[x][y] = 'x';
            } else if (privateBoard[x][y] == 'x') {
                cout << "Straciles statek! To pole jest zajete przez twoj inny statek\n";
                break;
            } else {
                cout << "Straciles statek, bo wyplynales poza plansze\n";
                break;
            }
        }
        for (int i = 0; i < mediumShips; i++) {
            privateBoardView();
            cout << "Podaj koordynaty dwoch kawalkow " << i + 1 << " sredniego statku na planszy [9,9]\n";
            for (int j = 0; j < 2; j++) {
                cin >> x >> y;
                this_thread::sleep_for(chrono::milliseconds (100));
                if (j == 0 || (abs(lastY - y) < 2 && lastX == x) || (abs(lastX - x) < 2 && lastY == y)) {
                    if (x < 1 || y < 1) {
                        cout << "Koordynaty musza byc wieksze od 0 i mniejsze od 9\n";
                        cin >> x >> y;
                    }
                    if (privateBoard[x][y] == 'o') {
                        privateBoard[x][y] = 'x';
                    } else if (privateBoard[x][y] == 'x') {
                        cout << "Straciles statek! To pole jest zajete przez twoj inny statek\n";
                        break;
                    } else {
                        cout << "Straciles statek, bo wyplynales poza plansze\n";
                        break;
                    }
                } else {
                    cout << "Przerwales lacznosc statku, zatonal\n";
                    break;
                }
                lastX = x;
                lastY = y;
            }
        }
        for (int i = 0; i < hugeShips; i++) {
            privateBoardView();
            cout << "Podaj koordynaty trzech kawalkow jedynego flagowca na planszy 9 na 9\n";
            for (int j = 0; j < 3; j++) {
                cin >> x >> y;
                this_thread::sleep_for(chrono::milliseconds (100));
                if (j == 0 || (abs(lastY - y) < 2 && lastX == x) || (abs(lastX - x) < 2 && lastY == y)) {
                    if (x < 1 || y < 1) {
                        cout << "Koordynaty musza byc wieksze od 0 i mniejsze od 9\n";
                        cin >> x >> y;
                    }
                    if (privateBoard[x][y] == 'o') {
                        privateBoard[x][y] = 'x';
                    } else if (privateBoard[x][y] == 'x') {
                        cout << "Straciles statek! To pole jest zajete przez twoj inny statek\n";
                        break;
                    } else {
                        cout << "Straciles statek, bo wyplynales poza plansze/n";
                        break;
                    }
                } else {
                    cout << "Przerwales lacznosc statku, zatonal\n";
                }
                lastY = y;
                lastX = x;
            }
        }
        cout << "Statki rozmieszczone prawidlowo, pora zagrac w gre\n";
    }

    void autoSetUpBoard() {
        srand(time(NULL));
        int xrand, yrand, ships = 0;
        while (ships < smallShips) {
            xrand = rand() % 9 + 1; // generating random coordinates
            yrand = rand() % 9 + 1; // generating random coordinates
            while (privateBoard[xrand][yrand] == 'x') {
                xrand = rand() % 9 + 1; // generating random coordinates
                yrand = rand() % 9 + 1; // generating random coordinates
            }
            privateBoard[xrand][yrand] = 'x';
            ships++;
        }
        ships = 0;
        while (ships < mediumShips) {
            xrand = rand() % 9 + 1; // generating random coordinates
            yrand = rand() % 9 + 1; // generating random coordinates
            while (privateBoard[xrand][yrand] == 'x' && privateBoard[xrand - 1][yrand] == 'x' &&
                   privateBoard[xrand - 2][yrand] == 'x') {
                xrand = rand() % 9 + 1; // generating random coordinates
                yrand = rand() % 9 + 1; // generating random coordinates
            }
            privateBoard[xrand][yrand] = 'x';
            privateBoard[xrand - 1][yrand] = 'x';
            ships++;
        }
        ships = 0;
        while (ships < hugeShips) {
            xrand = rand() % 9 + 1; // generating random coordinates
            yrand = rand() % 9 + 1; // generating random coordinates
            while (privateBoard[xrand][yrand] == 'x' && privateBoard[xrand][yrand - 1] == 'x' &&
                   privateBoard[xrand][yrand - 2] == 'x') {
                xrand = rand() % 9 + 1; // generating random coordinates
                yrand = rand() % 9 + 1; // generating random coordinates
            }
            privateBoard[xrand][yrand] = 'x';
            privateBoard[xrand][yrand - 1] = 'x';
            privateBoard[xrand][yrand - 2] = 'x';
            ships++;
        }
    }

    void publicBoardView() {
        for (auto &i: publicBoard) {
            for (char j: i) {
                cout.width(5);
                cout << j;
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void privateBoardView() {
        for (auto &i: privateBoard) {
            for (char j: i) {
                cout.width(5);
                cout << j;
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void winnerEvaluate() {
        if (points == 6) {
            winner = true;
        }
    }
};

void shipBombing() {
    int x, y;


}

int main() {
    int x, y;
    Player player1;
    player1.privateBoardCreate();
    player1.publicBoardCreate();
    player1.setUpBoard();
    Player player2;
    player2.publicBoardCreate();
    player2.privateBoardCreate();
    player2.autoSetUpBoard();
    player2.privateBoardView();
    player1.publicBoardView();
    cout << endl << "============================ Czas rozpoczac bitwe ==============================\n\n" << endl
         << endl;
    while (!player1.winner && !player2.winner) {
        cout << "Twoja kolej. Zaatakuj przeciwnika!\n\n Wprowadz koordynaty miejsca ataku\n\n";
        player2.publicBoardView();
        player1.publicBoardView();
        cin >> x >> y;
        this_thread::sleep_for(chrono::milliseconds (200));
        player2.publicBoard[x][y] = player2.privateBoard[x][y];
        while (player2.publicBoard[x][y] == 'x') {
            player2.privateBoard[x][y] = '*';
            if (player1.points == 10) {
                player1.winner = true;
                cout << "Wygrales, gratulacje!";
                break;
            }

            cout << "Trafiles, mozesz ponowic atak, pomijajac ture przeciwnika!\n\n";
            player2.publicBoardView();
            player1.publicBoardView();
            player1.points++;
            cin >> x >> y;
            this_thread::sleep_for(chrono::milliseconds (200));
            player2.publicBoard[x][y] = player2.privateBoard[x][y];
        }
        if (player1.points == 10) {
            player1.winner = true;
            cout << "Wygrales, gratulacje!";
            break;
        }
        cout << "Chybiles, tura twojego przeciwnika\n\n";
        x = rand() % 9 + 1;
        y = rand() % 9 + 1;
        player1.publicBoard[x][y] = player1.privateBoard[x][y];
        this_thread::sleep_for(chrono::milliseconds (500));
        cout << "Przeciwnik strzela w punkt: " << x << " " << y << "\n\n";
        while (player1.publicBoard[x][y] == 'x') {
            player1.privateBoard[x][y] = '*';
            cout << "Przeciwnik trafil, jego tura!\n\n";
            player2.publicBoardView();
            player1.publicBoardView();
            this_thread::sleep_for(chrono::milliseconds (500));
            player2.points++;
            x = rand() % 9 + 1;
            y = rand() % 9 + 1;
            player1.publicBoard[x][y] = player1.privateBoard[x][y];
        }
        if (player2.points == 10) {
            cout << "Niestety, tym razem to ty przegrales!";
            break;
        }
        cout << "Przeciwnik chybil!\n\n";
    }

}
