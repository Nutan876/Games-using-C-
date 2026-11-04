#include <iostream>
#include <string>
#include <ctime>
using namespace std;

char player1, player2;
int mode;

void robotfirst(int board[3][3]);

void signchoose()
{
    cout << "Choose ('X' OR 'O') for Represent you : ";
    cin >> player1;
    cout << endl;

    if (player1 == 'X')
        player2 = 'O';
    else
        player2 = 'X';
}

void printboard(int board[3][3])
{
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                cout << " ";
            else
                cout << (char)board[i][j];
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
        if (i < 2)
            cout << "---------" << endl;
    }
    cout << endl;
}

void winner(int board[3][3])
{
    string who;
    if (mode == 1)
    {
        who = "Robot";
    }
    else
    {
        who = "Player 2";
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0)
        {
            cout << endl
                 << "Winner is : " << ((char)board[i][0] == player1 ? "Player 1" : who) << endl;
            printboard(board);
            exit(0);
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0)
        {
            cout << endl
                 << "Winner is : " << ((char)board[0][i] == player1 ? "Player 1" : who) << endl;
            printboard(board);
            exit(0);
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0)
    {
        cout << endl
             << "Winner is : " << ((char)board[0][0] == player1 ? "Player 1" : who) << endl;
        printboard(board);
        exit(0);
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0)
    {
        cout << endl
             << "Winner is : " << ((char)board[0][2] == player1 ? "Player 1" : who) << endl;
        printboard(board);
        exit(0);
    }
}

void fillboard(int board[3][3], int pos, char player)
{
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;

    if (player1 == player)
    {
        board[row][col] = player1;
    }
    else
    {
        board[row][col] = player2;
    }
    winner(board);
}

int boardisfilled(int board[3][3], int pos, string playername);

void sortdesending(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int boardisfilled(int board[3][3], int pos, string playername)
{
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;

    if (board[row][col] != 0)
    {
        if (playername != "robot")
            cout << "Position is already filled. Please choose another position." << endl;
        return 1; // Position is filled
    }
    return 0; // Position is not filled
}
// find the position in a row for the robot's move
int robotposrow(int board[3][3], int row)
{
    for (int j = 0; j < 3; j++)
    {
        if (board[row][j] == 0)
        {
            return 3 * row + j + 1;
        }
    }
    return -1;
}
// find the position in a column for the robot's move
int robotposcol(int board[3][3], int col)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][col] == 0)
        {
            return 3 * i + col + 1;
        }
    }
    return -1;
}

void robotlogic(int board[3][3])
{
    int pos = -1;
    // row and column check

    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == board[i][1] && board[i][2] == 0) && board[i][0] != 0 ||
            (board[i][1] == board[i][2] && board[i][0] == 0) && board[i][1] != 0 ||
            (board[i][0] == board[i][2] && board[i][1] == 0) && board[i][0] != 0)
        {
            pos = robotposrow(board, i);
        }
        if ((board[0][i] == board[1][i] && board[2][i] == 0) && board[0][i] != 0 ||
            (board[1][i] == board[2][i] && board[0][i] == 0) && board[1][i] != 0 ||
            (board[0][i] == board[2][i] && board[1][i] == 0) && board[0][i] != 0)
        {
            pos = robotposcol(board, i);
        }
    }

    // diagonal check

    if ((board[0][0] == board[1][1] && board[2][2] == 0) && board[0][0] != 0 ||
        (board[1][1] == board[2][2] && board[0][0] == 0) && board[1][1] != 0 ||
        (board[0][0] == board[2][2] && board[1][1] == 0) && board[0][0] != 0)
    {
        if (board[0][0] == 0)
            pos = 1;
        else if (board[1][1] == 0)
            pos = 5;
        else
            pos = 9;
    }
    if ((board[0][2] == board[1][1] && board[2][0] == 0) && board[0][2] != 0 ||
        (board[1][1] == board[2][0] && board[0][2] == 0) && board[1][1] != 0 ||
        (board[0][2] == board[2][0] && board[1][1] == 0) && board[0][2] != 0)
    {
        if (board[0][2] == 0)
            pos = 3;
        else if (board[1][1] == 0)
            pos = 5;
        else
            pos = 7;
    }
    if (pos != -1)
    {
        cout << "Robot Choose Position : " << pos << endl;
        fillboard(board, pos, player2);
    }
    if (pos == -1)
    {
        robotfirst(board);
    }
}

int arr1[4] = {1, 3, 7, 9};
int arr2[4] = {2, 4, 6, 8};
int num1 = 4, num2 = 4;
void robotfirst(int board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 0)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (arr1[k] == 3 * i + j + 1)
                    {
                        arr1[k] = 0;
                    }
                    if (arr2[k] == 3 * i + j + 1)
                    {
                        arr2[k] = 0;
                    }
                }
            }
        }
    }

    sortdesending(arr1, 4);
    sortdesending(arr2, 4);

    for (int i = 0; i < 4; i++)
    {
        if (arr1[i] == 0)
        {
            num1 = i;
        }
        if (arr2[i] == 0)
        {
            num2 = i;
        }
    }

    srand(time(0));

    int chance = rand() % 10 + 1;
    int pos;

    if (chance <= 5 && board[1][1] == 0)
    {
        pos = 5;
        cout << "Robot Choose Position : " << pos << endl;
        fillboard(board, pos, player2);
    }
    else if ((5 < chance && chance <= 7) && board[1][1] == 0)
    {
        pos = arr2[rand() % num2];
        cout << "Robot Choose Position : " << pos << endl;
        fillboard(board, pos, player2);
    }
    else if (chance > 7 && board[1][1] == 0)
    {
        pos = arr1[rand() % num1];
        cout << "Robot Choose Position : " << pos << endl;
        fillboard(board, pos, player2);
    }
    else if (chance <= 8 && board[1][1] != 0)
    {
        pos = arr1[rand() % num1];
        cout << "Robot Choose Position : " << pos << endl;
        fillboard(board, pos, player2);
    }
    else if (chance > 8)
    {
        pos = arr2[rand() % num2];
        cout << "Robot Choose Position : " << pos << endl;
        fillboard(board, pos, player2);
    }
    else
    {
        pos = arr1[rand() % num1];
        cout << "Robot Choose Position : " << pos << endl;
        fillboard(board, pos, player2);
    }
}

void Enterposition()
{
    int board[3][3] = {0};
    int remening = 9;
    int pos;

    while (remening > 0)
    {
        do
        {
            cout << "Enter the position for your sign : ";
            cin >> pos;
        } while ((pos < 1 || pos > 9) || boardisfilled(board, pos, "player"));

        fillboard(board, pos, player1);
        remening--;

        if (mode == 1 && remening > 1)
        {
            cout << "Robot is Playing" << endl;
            robotlogic(board);
            remening--;
        }
        else if (mode == 2 && remening > 1)
        {
            do
            {
                cout << "Enter the position for your sign : ";
                cin >> pos;
            } while ((pos < 1 || pos > 9) || boardisfilled(board, pos, "player"));

            fillboard(board, pos, player2);
            remening--;
        }

        printboard(board);
        cout << endl;
    }
    cout << "Game Draw" << endl;
}

int main()
{
    do
    {
        cout << "Enter 1 for Robot and 2 for Human: ";
        cin >> mode;
    } while (mode != 1 && mode != 2);

    cout << endl;

    if (mode == 1)
    {
        signchoose();
        cout << "Your sign is : " << player1 << " and Robot sign is : " << player2;
    }
    else
    {
        cout << "Note : if Player1 Choose 'X' then 'O' is Assigned Automaticaly Alayer2" << endl;
        signchoose();
        cout << "Your sign is : " << player1 << " and player2 sign is : " << player2;
    }

    cout << endl;
    cout << "Remember This Position" << endl;
    cout << "1 | 2 | 3" << endl;
    cout << "4 | 5 | 6" << endl;
    cout << "7 | 8 | 9" << endl;

    cout << endl;

    Enterposition();
    return 0;
}