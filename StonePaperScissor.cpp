#include <iostream>
#include <string>
using namespace std;

enum enGameChoice
{Stone = 1, Paper = 2, Scissors = 3};
enum enWinner
{Player = 1, Computer = 2, Draw = 3};

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};
struct stGameResult
{
	short GameRounds = 0;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;

	return RandNum;
}

enGameChoice ReadPlayerChoice()
{
	short PlayerChoice = 0;

	do
	{

		cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissor? ";
		cin >> PlayerChoice;

	} while (PlayerChoice < 1 || PlayerChoice > 3);


	return enGameChoice(PlayerChoice);
}

enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));
}

enWinner WhoWinTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return Draw;

	switch (RoundInfo.PlayerChoice)
	{
	case Stone:
		if (RoundInfo.ComputerChoice == Paper)
			return Computer;
		break;

	case Paper:
		if (RoundInfo.ComputerChoice == Scissors)
			return Computer;
		break;

	case Scissors:
		if (RoundInfo.ComputerChoice == Stone)
			return Computer;
		break;

	default:
		break;
	}

	return Player;
}

string WinnerName(enWinner Winner)
{
	switch (Winner)
	{
	case Player:
		return "Player";

	case Computer:
		return "Computer";

	case Draw:
		return "No Winner";

	default:
		break;
	}
}

enWinner WhoWonTheGame(short PlayerWonTimes, short ComputerWonTimes)
{
	if (PlayerWonTimes > ComputerWonTimes)
		return Player;
	else if (PlayerWonTimes < ComputerWonTimes)
		return Computer;
	else
		return Draw;
}

string GameChoice(enGameChoice GameChoice)
{
	switch (GameChoice)
	{
	case Stone:
		return "Stone";

	case Paper:
		return "Paper";

	case Scissors:
		return "Scissors";

	default:
		break;
	}
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n______________Round [" << RoundInfo.RoundNumber << "]______________\n\n";
	cout << "Player Choice  :" << GameChoice(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice:" << GameChoice(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
	cout << "_____________________________________\n\n";
}

stGameResult FillGameResult(short Rounds, short PlayerWonCounter, short ComputerWonCounter, short DrawCounter)
{
	stGameResult GameResult;

	GameResult.GameRounds = Rounds;
	GameResult.PlayerWonTimes = PlayerWonCounter;
	GameResult.ComputerWonTimes = ComputerWonCounter;
	GameResult.DrawTimes = DrawCounter;
	GameResult.GameWinner = WhoWonTheGame(PlayerWonCounter, ComputerWonCounter);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}

short HowManyRounds()
{
	short GameRounds = 0;

	do
	{
		cout << "\nHow Many Rounds From 1 to 10? ";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

string Tabs(int NumberOfTabs)
{
	string t = "";

	for (int i = 0; i < NumberOfTabs; i++)
	{
		t += "\t";
	}

	return t;
}

void PrintScreenGameOver()
{
	cout << Tabs(2) << "______________________________________________________\n\n";
	cout << Tabs(2) << "             +++  G A M E  O V E R  +++                 \n";
	cout << Tabs(2) << "______________________________________________________\n\n";
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case Player:
		system("color 2F");
		break;

	case Computer:
		system("color 4F");
		cout << "\a";
		break;

	case Draw:
		system("color 6F");
		break;

	default:
		break;
	}
}

stGameResult PlayGame(int HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWonCounter = 0, ComputerWonCounter = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] Begins: \n\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		//Increase Win/Draw Counter
		switch (RoundInfo.Winner)
		{
		case Player:
			PlayerWonCounter++;
			break;

		case Computer:
			ComputerWonCounter++;
			break;

		case Draw:
			DrawTimes++;
			break;

		default:
			break;
		}

		PrintRoundResult(RoundInfo);
		SetWinnerScreenColor(RoundInfo.Winner);
	}

	return FillGameResult(HowManyRounds, PlayerWonCounter, ComputerWonCounter, DrawTimes);
}

void PrintGameResult(stGameResult GameResult)
{
	cout << Tabs(2) << "____________________[Game Result]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds       :" << GameResult.GameRounds << endl;
	cout << Tabs(2) << "Player Won Times  :" << GameResult.PlayerWonTimes << endl;
	cout << Tabs(2) << "Computer Won Times:" << GameResult.ComputerWonTimes << endl;
	cout << Tabs(2) << "Draw Times        :" << GameResult.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner      :" << GameResult.WinnerName << endl;
	cout << Tabs(2) << "______________________________________________________\n\n";
}

void ScreenReset()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ScreenReset();

		stGameResult GameResult = PlayGame(HowManyRounds());

		PrintScreenGameOver();
		PrintGameResult(GameResult);

		cout << Tabs(2) << "Do You Want Play Again? [Y/N] ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();
}