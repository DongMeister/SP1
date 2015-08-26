#include "Dialogue.h"

std::string dialog[10];

std::string Text[] = {"So many walls...But I see an exit","Something opened in the distance","Nothing happened...I feel like pressing more though","That's the second switch, I wonder what will happen ","That's the third one","The last one...Something opened in the distance"};


void WriteDialogue(std::string Stuff)
{
	for (int i = 0;i < 10;++i)
	{
		console.writeToBuffer(0,21+i,dialog[i],0x06);
	}
	console.writeToBuffer(40-Stuff.length()/2,24,Stuff,0x06);
}


void LoadDialogue()
{
	std::string line;
	std::ifstream myfile ("Map/dialog.txt");
	
	if (myfile.is_open())
	{
		int y= 0;
		 while ( getline (myfile,line) )
		 {
			if (y < 10)
			{
				dialog[y] = line;
				++y;
			}
		 }
	}
	myfile.close();
}

std::string choosedialog(int i)
{
	return Text[i];
}