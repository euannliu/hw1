#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <stdio.h>
using namespace std;
int main(int argc, char *argv[])
{
	//Declarations
	int num_lines;
	int num_words = 0;
	char *token = NULL;
	string linetoken;
	string hold;
	string word;
	string *storedlines = NULL;
	stringstream ss;
	ifstream file;

	if(argc<2)
	{
		cout << "This program requires an argument from the command line.\n";
		cout << "Please type into the command line: \"./<name of your file> <name of your text file>\"\n";
	}
	else
	{
		file.open(argv[1]);

		if(file.fail())
		{
			cout << "File opening has failed.\n";
		}
		else
		{
			//Grabbing the number of lines
			getline(file,linetoken);
			ss << linetoken;
			ss >> num_lines;
			ss.clear();

			if(num_lines<=0)
			{
				cout << "Incorrect file contents\n";
			}

			else
			{
				storedlines = new string[num_lines];

				//Storing each line into a string array
				for(int counter=0;counter<num_lines;counter++)
				{
					getline(file,linetoken);
					storedlines[counter]=linetoken;
				}
				//Counts how many words are in a line using strtok
				for(int counter=num_lines-1;counter>=0;counter--)
				{
					num_words = 0;
					hold = storedlines[counter];
					token = strtok(&hold[0]," \n");
					while(token != NULL)
					{
						num_words++;
						token = strtok(NULL," \n");
					}
					cout << num_words << endl;
					//deallocate
					delete [] token;
					token = NULL;
				}
				//deallocate
				file.close();
				delete [] storedlines;
				storedlines = NULL;
			}
		}
	}
	return 0;
}