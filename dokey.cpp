
// Pokey dokey, a program that has a main menu, and can show you a credits screen, 
// provide you with a poker machine simulation/game, or allow you to quit.
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <ctype.h>
using namespace std;

const int STARTING_CASH = 2000;

//numbers for menu choices
 enum menuChoice {
  NO_CHOICE = -1,
  PLAY_SLOTS = 1,
  QUIT,
  CREDITS,
 };
	
 //numbers for win multipliers
 enum WinMultiplier {
	 NO_WIN = 0,
	 TWO_OF_KIND = 3,
	 THREE_OF_KIND = 5,
	 JACKPOT = 10
 };

 // Ask the user to bet and then return the bet as an integer
// The bet must be more than nothing (>0) and no more than
// the total cash they actually have (<=totalCash)
 int getValidBet(int cashTotal)
 {

	 int bet = 0;
	 string betError;
	
	 do {
		 std::cout << R"(
    
     .----------------. .----------------. .----------------. .----------------. .----------------. 
    | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
    | |    _______   | | |   _____      | | |     ____     | | |  _________   | | |    _______   | |
    | |   /  ___  |  | | |  |_   _|     | | |   .'    `.   | | | |  _   _  |  | | |   /  ___  |  | |
    | |  |  (__ \_|  | | |    | |       | | |  /  .--.  \  | | | |_/ | | \_|  | | |  |  (__ \_|  | |
    | |   '.___`-.   | | |    | |   _   | | |  | |    | |  | | |     | |      | | |   '.___`-.   | |
    | |  |`\____) |  | | |   _| |__/ |  | | |  \  `--'  /  | | |    _| |_     | | |  |`\____) |  | |
    | |  |_______.'  | | |  |________|  | | |   `.____.'   | | |   |_____|    | | |  |_______.'  | |
    | |              | | |              | | |              | | |              | | |              | |
    | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
     '----------------' '----------------' '----------------' '----------------' '----------------' 
                                                            
    )" << '\n';

		 cout << "                                         YOU HAVE $" << cashTotal << "\n\n";
		 if (betError != "")
		 {
			 cout << betError << "\n";
		 }
		 
		 cout << "                                         PLACE YOUR BET :  ";
		 cin >> bet;

		 if (bet < 1 || bet > cashTotal)
		 {
			 
			 betError = "\n                             PLACE A BET OR BET UNDER YOUR BANK DUDE!!\n";
		 }
		 else {
			 betError = "";
		 }
		 system("cls");
	 } while (betError != "");
	
	 return bet;
 }

//Tells the user to enter m to return to main menu
//waits for m and then return to main
 void returnMenu() {

	 int ch;

	 _cputs("                        Type 'M' to return to main menu: ");
	 do
	 {
		 ch = _getch();
		 ch = toupper(ch);
	 } while (ch != 'M');

	 _putch(ch);
	 _putch('\r');    // Carriage return
	 _putch('\n');    // Line feed
 }

//displays the main menu with choices of different screens
// also displays the remaining cash
//returns the choice value as int
 int displayMenu(int cashTotal)

 {
	int choice;	
	string error = "";
	
	do {
		std::cout << R"(
    
     .----------------. .----------------. .----------------. .----------------. .----------------. 
    | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
    | |    _______   | | |   _____      | | |     ____     | | |  _________   | | |    _______   | |
    | |   /  ___  |  | | |  |_   _|     | | |   .'    `.   | | | |  _   _  |  | | |   /  ___  |  | |
    | |  |  (__ \_|  | | |    | |       | | |  /  .--.  \  | | | |_/ | | \_|  | | |  |  (__ \_|  | |
    | |   '.___`-.   | | |    | |   _   | | |  | |    | |  | | |     | |      | | |   '.___`-.   | |
    | |  |`\____) |  | | |   _| |__/ |  | | |  \  `--'  /  | | |    _| |_     | | |  |`\____) |  | |
    | |  |_______.'  | | |  |________|  | | |   `.____.'   | | |   |_____|    | | |  |_______.'  | |
    | |              | | |              | | |              | | |              | | |              | |
    | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
     '----------------' '----------------' '----------------' '----------------' '----------------' 
                                                            
    )" << '\n';

		cout << "                         --------------------CASH: $" << cashTotal << "-----------------\n\n" << endl;
		cout << "                                1. PLAY SLOTS  2.QUIT  3.CREDITS\n";
		cout << "\n";

		//show error message if they messed up 
		//if error messsage is empty dont show it
		if (error != "")
		{
			cout << error << "\n";
		}

		cout << "                                 ENTER YOUR CHOICE : ";
		//Get Choice
		cin >> choice;

		//Check if valid choice
		//if its not a valid choice
		//set the error message to "Choose a number between 1 and 3"
		if (choice < 1 || choice > 3) {
			error = "                     ----------ERROR: Please select a number from 1 to 3---------\n";
		}
		//set the error message to empty
		else {
			error = "";
		}
		system("cls");
	} while (error != "");
	//loop back to beginning if error message isnt empty.

    return choice;
 }

 // Check the three wheels and see if we won (pair, three of a kind etc
// store a multiplyer (0x, 3x, 5x, 10x) for that kind of win or loss.
 int checkForWins(int wheel1, int wheel2, int wheel3) {


	 if (wheel1 == wheel2 && wheel2 == wheel3 && wheel1 == 7)
	 { 
		 return JACKPOT;
	 }
	 else if (wheel1 == wheel2 && wheel2 == wheel3)
	 {
		 return THREE_OF_KIND;
	 }
	 else if (wheel1 == wheel2 || wheel2 == wheel3 || wheel1 == wheel3) 
	 {
		 return TWO_OF_KIND;
	 }
	 else if (wheel1 != wheel2 && wheel2 != wheel3)
	 {
		 return NO_WIN;
	 }
 }

//lets you bet on a slot machine to win or loose.
//you come in with an amount of money you either loose or win and come up with a new total.
//returns the new cash total
 int playSlots(int cashTotal) 

 {
	 int bet = getValidBet(cashTotal);

	 std::cout << R"(
    
     .----------------. .----------------. .----------------. .----------------. .----------------. 
    | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
    | |    _______   | | |   _____      | | |     ____     | | |  _________   | | |    _______   | |
    | |   /  ___  |  | | |  |_   _|     | | |   .'    `.   | | | |  _   _  |  | | |   /  ___  |  | |
    | |  |  (__ \_|  | | |    | |       | | |  /  .--.  \  | | | |_/ | | \_|  | | |  |  (__ \_|  | |
    | |   '.___`-.   | | |    | |   _   | | |  | |    | |  | | |     | |      | | |   '.___`-.   | |
    | |  |`\____) |  | | |   _| |__/ |  | | |  \  `--'  /  | | |    _| |_     | | |  |`\____) |  | |
    | |  |_______.'  | | |  |________|  | | |   `.____.'   | | |   |_____|    | | |  |_______.'  | |
    | |              | | |              | | |              | | |              | | |              | |
    | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
     '----------------' '----------------' '----------------' '----------------' '----------------' 
                                                            
    )" << '\n';
		 
		 cashTotal -= bet;
	
	     //generate random number
		 srand (time(0));
		 int wheel1 = rand() % 7 + 2;
		 int wheel2 = rand() % 7 + 2;
		 int wheel3 = rand() % 7 + 2;
		 
		 //display results

		 cout << " \n || " << wheel1 << " || " << wheel2 << " || " << wheel3 << " || \n\n ";

		 //call check for win function
		 int multiplier = checkForWins(wheel1, wheel2, wheel3);

	cashTotal += bet * multiplier; // new cash total
	
	//check multiplier and display message accordingly
	if (multiplier == THREE_OF_KIND) {
		cout << "!!THREE OF A KIND!! YOU NOW HAVE $" << cashTotal << "\n\n";
	}
	else if(multiplier == NO_WIN)
	{
		cout << "!!YOU LOST!!, YOU NOW HAVE $" << cashTotal << "\n\n";
	}
	else if (multiplier == TWO_OF_KIND) 
	{
		cout << "!!TWO OF A KIND!!, YOU NOW HAVE $" << cashTotal << "\n\n";
	}
	else if (multiplier == JACKPOT) 
	{
		cout << "!!!!!!!JACKPOT!!!!!!!, YOU NOW HAVE $" << cashTotal << "\n\n";
	}
	
	return (cashTotal);
		
 }

//display list of people who worked on the game
 void displayCredits() 

 {

	 std::cout << R"(        
                                                                                                     
         
                   _  .-')    ('-.  ('-.    .-') _              _  .-')   .-')    
                  ( \( -O ) _(  OO)( OO ).-(  OO) )            ( \( -O ) ( OO ).  
            .-----.,------.(,------/ . --. /     '._ .-'),-----.,------.(_)---\_) 
           '  .--./|   /`. '|  .---| \-.  \|'--...__( OO'  .-.  |   /`. /    _ |  
           |  |('-.|  /  | ||  | .-'-'  |  '--.  .--/   |  | |  |  /  | \  :` `.  
          /_) |OO  |  |_.' (|  '--\| |_.'  |  |  |  \_) |  |\|  |  |_.' |'..`''.) 
          ||  |`-'||  .  '.'|  .--'|  .-.  |  |  |    \ |  | |  |  .  '..-._)   \ 
         (_'  '--'\|  |\  \ |  `---|  | |  |  |  |     `'  '-'  |  |\  \\       / 
            `-----'`--' '--'`------`--' `--'  `--'       `-----'`--' '--'`-----'                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
                                                   
     )" << '\n';

	Sleep(1000);
	cout << "              Designer: Ashutosh Bogati\n" << endl;

	Sleep(1000);
	cout << "              Creatuve Director: Ashutosh Bogati\n" << endl;

	Sleep(1000);
	cout << "              Ashutosh Bogati\n" << endl;
	
	Sleep(1000);
	cout << "              Ashutosh Bogati\n" << endl;

	Sleep(1000);
	cout << "              Ashutosh Bogati\n" << endl;

	returnMenu();
	
	return;
 }

//shows the amount the player won or lost
 //show win loss message according to players winnings or loss
 void displayQuit(int finalCash)

 {
	 int winLoss = finalCash - STARTING_CASH;//final amount
	 cout << "\n YOUR TOTAL WIN/LOSS $ = " << winLoss << "\n" << endl;
 
	 // win loss message according to the win or loss
	 if (winLoss >= 3000)
	 {
		 cout << "\n CONGRULATION HIGHROLLER, YOU WIN\n";
		 std::cout << R"(        
                                                                                                     
         
       
     /$$   /$$ /$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$   /$$$$$$  /$$       /$$       /$$$$$$$$ /$$$$$$$ 
    | $$  | $$|_  $$_/ /$$__  $$| $$  | $$| $$__  $$ /$$__  $$| $$      | $$      | $$_____/| $$__  $$
    | $$  | $$  | $$  | $$  \__/| $$  | $$| $$  \ $$| $$  \ $$| $$      | $$      | $$      | $$  \ $$
    | $$$$$$$$  | $$  | $$ /$$$$| $$$$$$$$| $$$$$$$/| $$  | $$| $$      | $$      | $$$$$   | $$$$$$$/
    | $$__  $$  | $$  | $$|_  $$| $$__  $$| $$__  $$| $$  | $$| $$      | $$      | $$__/   | $$__  $$
    | $$  | $$  | $$  | $$  \ $$| $$  | $$| $$  \ $$| $$  | $$| $$      | $$      | $$      | $$  \ $$
    | $$  | $$ /$$$$$$|  $$$$$$/| $$  | $$| $$  | $$|  $$$$$$/| $$$$$$$$| $$$$$$$$| $$$$$$$$| $$  | $$
    |__/  |__/|______/ \______/ |__/  |__/|__/  |__/ \______/ |________/|________/|________/|__/  |__/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
                                                   
     )" << '\n';

	 }
	 else if (winLoss >= 1000) 
	 {
		 cout << "\n CONGRULATIONS CHAMP, YOU WIN\n";
		 std::cout << R"(        
                                                                                                     
      
      /$$$$$$  /$$   /$$  /$$$$$$  /$$      /$$ /$$$$$$$  /$$$$$$  /$$$$$$  /$$   /$$
     /$$__  $$| $$  | $$ /$$__  $$| $$$    /$$$| $$__  $$|_  $$_/ /$$__  $$| $$$ | $$
    | $$  \__/| $$  | $$| $$  \ $$| $$$$  /$$$$| $$  \ $$  | $$  | $$  \ $$| $$$$| $$
    | $$      | $$$$$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$$$/  | $$  | $$  | $$| $$ $$ $$
    | $$      | $$__  $$| $$__  $$| $$  $$$| $$| $$____/   | $$  | $$  | $$| $$  $$$$
    | $$    $$| $$  | $$| $$  | $$| $$\  $ | $$| $$        | $$  | $$  | $$| $$\  $$$
    |  $$$$$$/| $$  | $$| $$  | $$| $$ \/  | $$| $$       /$$$$$$|  $$$$$$/| $$ \  $$
     \______/ |__/  |__/|__/  |__/|__/     |__/|__/      |______/ \______/ |__/  \__/
                                                                                                                                                              

     )" << '\n';

	 }
	 else if (winLoss < 1000 && winLoss > 0)
	 {
		 cout << "\n CONGRULATIONS BUD, YOU SURVIVED\n";

		 std::cout << R"( 
                                                                                         
                                                                                          
      .--.--.                 ,-.----.                 ,---,                ,---,.,-.----.    
     /  /    '.          ,--, \    /  \        ,---.,`--.' |       ,---.  ,'  .' |\    /  \   
    |  :  /`. /        ,'_ /| ;   :    \      /__./||   :  :      /__./|,---.'   |;   :    \  
    ;  |  |--`    .--. |  | : |   | .\ : ,---.;  ; |:   |  ' ,---.;  ; ||   |   .'|   | .\ :  
    |  :  ;_    ,'_ /| :  . | .   : |: |/___/ \  | ||   :  |/___/ \  | |:   :  |-,.   : |: |  
     \  \    `. |  ' | |  . . |   |  \ :\   ;  \ ' |'   '  ;\   ;  \ ' |:   |  ;/||   |  \ :  
      `----.   \|  | ' |  | | |   : .  / \   \  \: ||   |  | \   \  \: ||   :   .'|   : .  /  
      __     \  \  |:  | | :  ' ; ;   | |  \  ;   \  ' .'   :  ;  ;   \  ' .|   |  |-,;   | |  \  
     /  /`--'  /|  ; ' |  | ' |   | ;\  \  \   \   '|   |  '   \   \   ''   :  ;/||   | ;\  \ 
    '--'.     / :  | : ;  ; | :   ' | \.'   \   `  ;'   :  |    \   `  ;|   |    \:   ' | \.' 
      `--'---'  '  :  `--'   \:   : :-'      :   \ |;   |.'      :   \ ||   :   .':   : :-'   
                :  ,      .-./|   |.'         '---" '---'         '---" |   | ,'  |   |.'     
                 `--`----'    `---'                                     `----'    `---'                                                                                                  
                                                    
     )" << '\n';

	 }
	 else if (winLoss < 0 && winLoss > -2000) {
		 cout << "\n LOSER, TRY AGAIN NEXT TIME\n";
		 std::cout << R"( 

       ,--,                                             
    ,---.'|                                             
    |   | :                                             
    :   : |                                             
    |   ' :      ,---.                          __  ,-. 
    ;   ; '     '   ,'\   .--.--.             ,' ,'/ /| 
    '   | |__  /   /   | /  /    '     ,---.  '  | |' | 
    |   | :.'|.   ; ,. :|  :  /`./    /     \ |  |   ,' 
    '   :    ;'   | |: :|  :  ;_     /    /  |'  :  /   
    |   |  ./ '   | .; : \  \    `. .    ' / ||  | '    
    ;   : ;   |   :    |  `----.   \'   ;   /|;  : |    
    |   ,/     \   \  /  /  /`--'  /'   |  / ||  , ;    
    '---'       `----'  '--'.     / |   :    | ---'     
                          `--'---'   \   \  /           
                                      `----'            
                                                    
     )" << '\n';
	 }
	 else if (winLoss == -2000) {
		 cout << "\n GET OUT, YOU ARE BROKE\n";
		 std::cout << R"(
       ,--,                                             
    ,---.'|                                             
    |   | :                                             
    :   : |                                             
    |   ' :      ,---.                          __  ,-. 
    ;   ; '     '   ,'\   .--.--.             ,' ,'/ /| 
    '   | |__  /   /   | /  /    '     ,---.  '  | |' | 
    |   | :.'|.   ; ,. :|  :  /`./    /     \ |  |   ,' 
    '   :    ;'   | |: :|  :  ;_     /    /  |'  :  /   
    |   |  ./ '   | .; : \  \    `. .    ' / ||  | '    
    ;   : ;   |   :    |  `----.   \'   ;   /|;  : |    
    |   ,/     \   \  /  /  /`--'  /'   |  / ||  , ;    
    '---'       `----'  '--'.     / |   :    | ---'     
                          `--'---'   \   \  /           
                                      `----'                                                               
)" << '\n';
	 }
	 
 }

 //ask if player wants to play again
 bool playerPlayAgain(int TrueFalse) {
	 
	 cout << "\n ENTER 1 TO PLAY AGAIN OR ANY OTHER NUMBER TO RETURN TO MAIN MENU ";
	 cin >> TrueFalse;
	 if (TrueFalse == 1 ) {
		 return true;
	 }
	 else 
	 {
		 return false;
	 }
	
 }

 int main()
 {
	// cashLeft = (player's remaining money)
	int cashLeft = STARTING_CASH;
	int choice = NO_CHOICE;

	// Start loop
	do {
		system("cls");
		choice = displayMenu(cashLeft); //DISPLAY main menu
		
		if (choice == PLAY_SLOTS)
		{
			bool playAgain = false;
			do
			{
				system("cls");
				cashLeft = playSlots(cashLeft); //display play slots
				 if (cashLeft > 0)
				{
				  
				  playAgain = playerPlayAgain(playAgain); //function for play again option
				} 
				 else 
				{
					 playAgain = false;
					 choice = QUIT;
				}
			} while (playAgain == true);
			
		}

		else if (choice == CREDITS)
		{
			system("cls");
		 displayCredits();
			
		}
			
	} 
	while (choice != QUIT); //player didnt choose quit
	
	//quit screen
	system("cls");

	std::cout << R"(
           
        _           _   _        _         _           _            _                  _          _          
       / /\        / /\/\ \     /\_\      /\ \        /\ \     _   / /\               /\ \       / /\        
      / /  \      / /  \ \ \   / / /     /  \ \      /  \ \   /\_\/ /  \             /  \ \     / /  \       
     / / /\ \__  / / /\ \ \ \_/ / /     / /\ \ \    / /\ \ \_/ / / / /\ \           / /\ \ \   / / /\ \      
    / / /\ \___\/ / /\ \ \ \___/ /     / / /\ \ \  / / /\ \___/ / / /\ \ \         / / /\ \_\ / / /\ \ \     
    \ \ \ \/___/ / /  \ \ \ \ \_/     / / /  \ \_\/ / /  \/____/ / /  \ \ \       / / /_/ / // / /  \ \ \    
     \ \ \    / / /___/ /\ \ \ \     / / /   / / / / /    / / / / /___/ /\ \     / / /__\/ // / /___/ /\ \   
 _    \ \ \  / / /_____/ /\ \ \ \   / / /   / / / / /    / / / / /_____/ /\ \   / / /_____// / /_____/ /\ \  
/_/\__/ / / / /_________/\ \ \ \ \ / / /___/ / / / /    / / / /_________/\ \ \ / / /\ \ \ / /_________/\ \ \ 
\ \/___/ / / / /_       __\ \_\ \_/ / /____\/ / / /    / / / / /_       __\ \_/ / /  \ \ / / /_       __\ \_\
 \_____\/  \_\___\     /____/_/\/_\/_________/\/_/     \/_/\_\___\     /____/_\/_/    \_\\_\___\     /____/_/
                                                                                                             
     
                                                  
   )" << '\n';

     displayQuit(cashLeft);

 }