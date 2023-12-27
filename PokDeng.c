#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <Windows.h>
#include <math.h>
#include <string.h>

//Create variable zone
char SuitCard[4] = {'\x05', '\x04', '\x03', '\x06'}; //Suit of card
int card[52];                                        //Set of card follow by 0-51
int CardOnHand[17][3];                               //Card on hand at player  card
int SumCardOnHand[17];                               //Amount of player's card
int CardOut = 0;                                     //How many card is out
int SumPlayer;                                       //How many player
int PlayerPoint[17];                                 //Score

//Create function zone
void NumOfCard(int Playernow, int cardnow); //Show card
void Pointcheck(int Playernow);             //Check Point
void ShowPoint(int Playernow);              //Show what you got
void ClearTerminal(int sec);                //Clear Terminal
void Winer(int maxpoint);                   //Show winer
void UnBoxDeck();                           //Unbox card deck
void DrawCard();                            //Draw 2 card
void Playing();                             //Playing
void Shuffle();                             //Shuffle card
void Welcome();                             //Wecome
int AskToPlayAgain();                       //Wanna play again
int Player();                               //Input sum of player
int Result();                               //Out put max point of player

//main zone
int main()
{
    srand(time(NULL));
    system("cls");
    UnBoxDeck();
    Welcome();
    do
    {
        Shuffle();
        system("cls");
        SumPlayer = Player();
        DrawCard();
        Playing();
        Winer(Result());
    } while (AskToPlayAgain());
    printf("\nThx For Playing :)");
}

//edit function zone
void ClearTerminal(int sec)
{
    printf("\nDelete Text in\n\n");
    for (int count = sec; count > 0; count--)
    {
        printf("**%d**\n", count);
        sleep(1);
    }
    system("cls");
}

void NumOfCard(int Playernow, int cardnow)
{
    char NumCard[3] = "as";
    if (CardOnHand[Playernow][cardnow] % 13 + 1 < 10)
        NumCard[0] = '0' + (CardOnHand[Playernow][cardnow] % 13 + 1), NumCard[1] = '\0';
    else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 10)
        strcpy(NumCard, "10");
    else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 11)
        strcpy(NumCard, "J");
    else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 12)
        strcpy(NumCard, "Q");
    else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 13)
        strcpy(NumCard, "K");
    printf("%s %c \n", NumCard, SuitCard[(CardOnHand[Playernow][cardnow]) / 13]);
}

void Pointcheck(int Playernow)
{
    int point = 0, straight = 0;
    point = 0;
    for (int y = 0; y < 2; ++y)
    { //1-2card
        if (!(CardOnHand[Playernow][y] % 13 + 1 > 10))
        {
            point += CardOnHand[Playernow][y] % 13 + 1;
        }
    }
    point %= 10;
    if (SumCardOnHand[Playernow] == 3)
    {
        for (int i = 0; i < 3; i++)
        { //Check straight
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (i == j || i == k || j == k)
                    {
                        continue;
                    }
                    if (CardOnHand[Playernow][i] % 13 == CardOnHand[Playernow][j] % 13 + 1 && CardOnHand[Playernow][j] % 13 + 1 == CardOnHand[Playernow][k] % 13 + 2)
                    {
                        straight = 1;
                    }
                }
            }
        }
    }
    if (point == 9 && SumCardOnHand[Playernow] == 2)
    { //check POK 9
        PlayerPoint[Playernow] = 4000;
    }
    else if (point == 8 && SumCardOnHand[Playernow] == 2)
    { //check POK 8
        PlayerPoint[Playernow] = 3000;
    }
    else if (CardOnHand[Playernow][0] % 13 + 1 == CardOnHand[Playernow][1] % 13 + 1 && CardOnHand[Playernow][1] % 13 + 1 == CardOnHand[Playernow][2] % 13 + 1 && SumCardOnHand[Playernow] == 3)
    { //check TONG
        PlayerPoint[Playernow] = (2000 + (CardOnHand[Playernow][0] % 13 + 1));
    }
    else if (straight)
    { //Straight ?
        if (CardOnHand[Playernow][1] % 13 + 1 == 1 || CardOnHand[Playernow][1] == 13)
        { //Straigh False
            PlayerPoint[Playernow] = 0;
        }
        else
        {
            if (CardOnHand[Playernow][0] / 13 == CardOnHand[Playernow][1] / 13 && CardOnHand[Playernow][1] / 13 == CardOnHand[Playernow][2] / 13)
            { //Check StraightFlush
                PlayerPoint[Playernow] = (1000 + (CardOnHand[Playernow][0] % 13 + 1) + ((CardOnHand[Playernow][0]) / 13 + 1) * 100);
            }
            else
            { //NonFlush
                PlayerPoint[Playernow] = (1000 + (CardOnHand[Playernow][0] % 13 + 1));
            }
        }
    }
    else if (CardOnHand[Playernow][0] % 13 + 1 > 10 && CardOnHand[Playernow][1] % 13 + 1 > 10 && CardOnHand[Playernow][2] % 13 + 1 > 10)
    { //check royal
        PlayerPoint[Playernow] = 500;
    }
    else
    { //Just point
        for (int y = 0; y < SumCardOnHand[Playernow]; y++)
        {
            if (!(CardOnHand[Playernow][y] % 13 + 1 > 10))
            {
                PlayerPoint[Playernow] += CardOnHand[Playernow][y] % 13 + 1;
            }
        }
        PlayerPoint[Playernow] %= 10;
    }
}

void ShowPoint(int Playernow)
{
    PlayerPoint[Playernow] = 0;
    Pointcheck(Playernow);
    if (PlayerPoint[Playernow] == 4000)
        printf("Now you have POK 9\n");
    else if (PlayerPoint[Playernow] == 3000)
        printf("Now you have POK 8\n");
    else if (PlayerPoint[Playernow] > 2000)
        printf("Now you have trips card\n");
    else if (PlayerPoint[Playernow] >= 1100)
        printf("Now you have StraightFlush\n");
    else if (PlayerPoint[Playernow] > 1000)
        printf("Now you have Straight\n");
    else if (PlayerPoint[Playernow] == 500)
        printf("Now you have Yellow\n");
    else
        printf("Now you have %d point\n", PlayerPoint[Playernow]);
}

void Playing()
{
    char WordIn;
    int point;
    for (int Playernow = 0; Playernow < SumPlayer; Playernow++)
    {
        point = 0;
        //wait for see card
        printf("\n\tPlayer %d \n", Playernow + 1);
        printf("\nWrite \'Y\' when you wanna see your cards :");
        do
        {
            scanf(" %s", &WordIn);
            if (!(WordIn == 'Y'))
                printf("Wrong input. Please try again :");
        } while (!(WordIn == 'Y'));
        printf("\n");
        for (int y = 0; y < 2; y++)
            NumOfCard(Playernow, y);

        //wait for write (Y/N)
        ShowPoint(Playernow);
        if (PlayerPoint[Playernow] != 4000 && PlayerPoint[Playernow] != 3000)
        {
            printf("\nDo you wanna draw one more card (Y/N) :");
            do
            {
                scanf(" %s", &WordIn);
                if (!(WordIn == 'Y' || WordIn == 'N'))
                    printf("Wrong input. Please try again (Y/N) :");
            } while (!(WordIn == 'Y' || WordIn == 'N'));
            //if Y draw one more card
            if (WordIn == 'Y')
            {
                CardOnHand[Playernow][2] = card[CardOut++];
                SumCardOnHand[Playernow]++;
                printf("You got : ");
                NumOfCard(Playernow, 2);
                point += CardOnHand[Playernow][2] % 13 + 1;
            }
            ShowPoint(Playernow);
        }
        //wait for SumPlayer finished
        printf("\nWrite \'Y\' when you got finished :");
        do
        {
            scanf(" %s", &WordIn);
            if (!(WordIn == 'Y'))
                printf("Wrong input. Please try again :");
        } while (!(WordIn == 'Y'));
        ClearTerminal(3);
    }
}

void DrawCard()
{
    for (int cardnow = 0; cardnow < 2; cardnow++)
    {
        for (int Playernow = 0; Playernow < SumPlayer; Playernow++)
        {
            CardOnHand[Playernow][cardnow] = card[CardOut++];
            SumCardOnHand[Playernow]++;
        }
    }
}

int AskToPlayAgain()
{
    char WordIn;
    printf("\nDo you want to play again (Y/N) :");
    do
    {
        scanf(" %s", &WordIn);
        if (WordIn == 'Y')
            return 1;
        else if (WordIn == 'N')
            return 0;
        else
            printf("\n\nWrong input. Please try again (Y/N) :");
    } while (!(WordIn == 'Y' || WordIn == 'N'));
    ClearTerminal(3);
}

void UnBoxDeck()
{
    //just set card 0 to 51
    for (int x = 0; x < 52; x++)
        card[x] = x;
}

void Shuffle()
{
    int randvariable, keepvariable;
    CardOut = 0;
    for (int cardnow = 0; cardnow < 52; cardnow++)
    {
        randvariable = rand() % 52;
        keepvariable = card[cardnow];
        card[cardnow] = card[randvariable];
        card[randvariable] = keepvariable;
    }
    //just set up variable
    for (int Playernow = 0; Playernow < 17; Playernow++)
    {
        for (int cardnow = 0; cardnow < 3; cardnow++)
        {
            CardOnHand[Playernow][cardnow] = 0;
        }
        PlayerPoint[Playernow] = 0;
        SumCardOnHand[Playernow] = 0;
    }

    card[0] = 3;
    card[2] = 16;
    card[4] = 25;
}

void Welcome()
{
    printf("Welcome to PokDeng from TNI15 \x03\n");
}

int Player() {
    char p_num[10];
    int p_now, check_p = 0;
    printf("How many player Do you want to play ? (^_^) : ");
    again:
    check_p = 0;
    scanf("%s",p_num);
    for (p_now = 0; p_now < strlen(p_num); ++p_now) {
        if (!(p_num[p_now] >= '0' && p_num[p_now] <= '9')) {
            ++check_p;
        }
    }
    if (!check_p) {
        for (p_now = 0; p_now < strlen(p_num); ++p_now) {
            check_p += (p_num[p_now] - 48) * pow(10,(strlen(p_num) - p_now - 1));
        }
        if (check_p > 17) {
            printf("\nToo many players , Card not Enought!! (-_^) \n\n");
            printf("Please try again : ");
            goto again;
        }
        else if (check_p < 2) {
            printf("\nNot Enought players (T_T) \n\n");
            printf("Please try again : ");
            goto again;
        }
    }
    else {
        printf("\nPlease Enter The Positive Number!!! (>_<) \n\n");
        printf("Please try again : ");
        goto again;
    }
    return check_p;
}

int Result()
{
    int maxpoint = 0;
    for (int Playernow = 0; Playernow < SumPlayer; Playernow++)
        if (PlayerPoint[Playernow] > maxpoint)
            maxpoint = PlayerPoint[Playernow];
    return maxpoint;
}

void Winer(int maxpoint)
{
    char NumCard[3];
    for (int Playernow = 0; Playernow < SumPlayer; Playernow++)
    {
        if (maxpoint == PlayerPoint[Playernow])
        {
            printf("\tPlayer %d Win\n", Playernow + 1);
            for (int y = 0; y < SumCardOnHand[Playernow]; y++)
            {
                if (CardOnHand[Playernow][y] % 13 + 1 < 10)
                    NumCard[0] = '0' + (CardOnHand[Playernow][y] % 13 + 1), NumCard[1] = '\0';
                else if (CardOnHand[Playernow][y] % 13 + 1 == 10)
                    NumCard[0] = '1', NumCard[1] = '0', NumCard[2] = '\0';
                else if (CardOnHand[Playernow][y] % 13 + 1 == 11)
                    NumCard[0] = 'J', NumCard[1] = '\0';
                else if (CardOnHand[Playernow][y] % 13 + 1 == 12)
                    NumCard[0] = 'Q', NumCard[1] = '\0';
                else if (CardOnHand[Playernow][y] % 13 + 1 == 13)
                    NumCard[0] = 'K', NumCard[1] = '\0';
                printf("%s %c \n", NumCard, SuitCard[(CardOnHand[Playernow][y]) / 13]);
            }
        }
    }
}