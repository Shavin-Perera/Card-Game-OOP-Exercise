#include <iostream>
#include <string>
#include<fstream>
#include <vector>
#include <sstream>
#include "CCard.cpp"
#include "CStudent.cpp"
using namespace std;


// Function to read files
void ReadFile(string fileName, vector<CCard*>& deckNumber) {
    string data;
    ifstream dataFile(fileName);
    while (getline(dataFile, data)) {
        int type;
        string name;
        string lastName;
        int power;
        int resilience;

        // Extract the values from the data string (assuming space-separated)
        stringstream ss(data);
        ss >> type >> name>>lastName >> power >> resilience;
        name = name + " " + lastName;

        // Create a CCard object and push it into the vector

        if (type != 1) {
            deckNumber.push_back(new CCard(type, name, power));
        }
        else {
            deckNumber.push_back(new CStudent(type, name, power,resilience));
        }
    }
}

//Function To decide winner
void GetWinner(string name, int profPlagiarist,string name2, int profPiffle) {
    if (profPlagiarist <= 0) {
        cout <<endl<< name << " has no prestige and is sacked\n";
        exit(0);
    }
    if (profPiffle <= 0) {
        cout << endl << name2 << " has no prestige and is sacked\n";
        exit(0);
    }
}
    //Structure for professors
    struct SProfessor
    {
        string professorName;
        int prestige;
    };
    //Random Function which is provided
    int Random(int max)
    {
        return int(float(rand()) / (RAND_MAX + 1) * float(max));
    }


int main()
{
    //memory leak detection
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int  prestigeAmount = 30;

	//vectors
	vector <CCard*>deckOne;
	vector <CCard*>deckTwo;
    vector <CCard*>plagiaristTable;
    vector <CCard*>piffleTable;

    //calling the function to read the files
	ReadFile("plagiarist.txt",deckOne);
	ReadFile("piffle-paper.txt",deckTwo);

    //creating professors from the struct
    SProfessor* plagiarist = new SProfessor{ "Professor Plagiarist",prestigeAmount };
    SProfessor* pifflePaper = new SProfessor{ "Professor piffle-paper",prestigeAmount };

    //Seed text
    int seed;
    ifstream seedTxtFile("seed.txt");
    seedTxtFile >> seed;
    seedTxtFile.close();
    //srand(seed);

    //welcome message
    cout << "**********************************************\n";
    cout << "Welcome to U-Can't. Let the winnowing begin..." << endl;
    cout << "**********************************************\n";

    //getting starting card
    //select cardone from the deck (Plagiarist)
    vector<CCard*> plagiaristCardOne;
    plagiaristCardOne.push_back(deckOne.front());
    //after getting the first card from the deck delete it
    deckOne.erase(deckOne.begin());

    //out put the starting card
    cout << endl<<plagiarist->professorName<<" start with " << plagiaristCardOne.front()->getName();


    //select cardone from the deck (Piffle)
    vector <CCard*> piffleCardOne;
    piffleCardOne.push_back(deckTwo.front());
    //after getting the first card from the deck delete it
    deckTwo.erase(deckTwo.begin());

    //out put the starting card
    cout <<endl<<pifflePaper->professorName<< " start with " << piffleCardOne.front()->getName() << endl;


    //30 round simulation
    for (int roundNumber = 1; roundNumber <= 30; roundNumber++) {
        //round number
        cout << "\n\n\nRound " << roundNumber<<endl;
        cout << "**********************************************\n";


        //Plagiarist's part (drawing the card from the deck)
        vector<CCard*> plagiaristCardTwo;
        plagiaristCardTwo.push_back(deckOne.front());
        deckOne.erase(deckOne.begin());
        cout << plagiarist->professorName << " draws " << plagiaristCardTwo.front()->getName() << endl;

        //Piffle-paper's part (drawing the card from the deck)
        vector <CCard*> piffleCardTwo;
        piffleCardTwo.push_back(deckTwo.front());
        deckTwo.erase(deckTwo.begin());
        cout << pifflePaper->professorName << " draws " << piffleCardTwo.front()->getName() << endl;
        cout << endl;


        if (Random(2)==0) {
            //pull the card from hand one
            cout << plagiarist->professorName << " plays " << plagiaristCardOne.front()->getName() << endl;
            if (plagiaristCardOne.front()->getType() == 1) {
                //Move to the table
                plagiaristTable.insert(plagiaristTable.begin(), plagiaristCardOne.front());

            }

            //In the beginning of the loop Card two renews therefore card two was taken to cardone to stop spilling unused card
            plagiaristCardOne = plagiaristCardTwo;
        }
        else
        {
            //if random number equals to 1 pull this card
            cout << plagiarist->professorName << " plays " << plagiaristCardTwo.front()->getName() << endl;
            if (plagiaristCardTwo.front()->getType() == 1) {
                //Move to the table
                plagiaristTable.insert(plagiaristTable.begin(), plagiaristCardTwo.front());

            }
        }

        if (deckOne.empty()) {
            cout << "\n \n" << pifflePaper->professorName << " Wins \n";
        }



        //Game Logic Player-Piffle
        if (Random(2)==0) {
            cout << pifflePaper->professorName << " plays " << piffleCardOne.front()->getName() << endl;
            if (piffleCardOne.front()->getType() == 1) {
                //Move to the table
                piffleTable.insert(piffleTable.begin(), piffleCardOne.front());

            }
            piffleCardOne = piffleCardTwo;

        }
        else
        {
            cout << pifflePaper->professorName << " plays " << piffleCardTwo.front()->getName() << endl;
            if (piffleCardTwo.front()->getType() == 1) {
                //Move to the table
                piffleTable.insert(piffleTable.begin(), piffleCardTwo.front());
            }
        }
        if (deckTwo.empty()) {
            cout << "\n \n" << plagiarist->professorName << " Wins \n";
        }
        // Output the vector(cards on table)
        for (int count = 0; count < plagiaristTable.size(); count++) {
            if (count == 0) {
                cout << "\n\nCards on table: " << plagiaristTable[count]->getName() << " (" << plagiaristTable[count]->getResilience() << "), ";
            }
            else {
                cout << plagiaristTable[count]->getName() << " (" << plagiaristTable[count]->getResilience() << "), ";
            }
        }

        for (int count = 0; count < piffleTable.size(); count++) {
            if (count == 0) {
                cout << "\n\nCards on table: " << piffleTable[count]->getName() << " (" << piffleTable[count]->getResilience() << "), ";
            }
            else {
                cout << piffleTable[count]->getName() << " (" << piffleTable[count]->getResilience() << "), ";
            }
        }


        cout << endl;
        cout << endl;
        cout << endl;


        if (!piffleTable.empty()) {
            int newResilience = piffleTable.front()->getResilience() - plagiaristTable.front()->getPower();
            piffleTable.front()->setResilience(newResilience);
            cout << plagiaristTable.front()->getName() << " attacks " << piffleTable.front()->getName() << " " << piffleTable.front()->getName() << "’s resilience is now" << piffleTable.front()->getResilience() << endl;
        }


        if (!piffleTable.empty() && piffleTable.front()->getResilience() <= 0) {
            cout << plagiaristTable.front()->getName() << " attacks " << piffleTable.front()->getName() << " is defeated\n";
            piffleTable.erase(piffleTable.begin());
        }

        cout << endl;
        //cout << piffleTable.front()->getName();


        GetWinner(plagiarist->professorName,plagiarist->prestige,pifflePaper->professorName,pifflePaper->prestige);
    }
    return 0;
}
