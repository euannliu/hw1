#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>
using namespace std;

struct Bucket
{
	int *content;
	int num;
	bool empty;
};
int main(int argc, char *argv[])
{
	ifstream file;
	string line;
	string command;
	char* token = NULL;
	int num_buckets, num_lines;
	int bucket_num, num_entries;
	Bucket *bucket = NULL;
	stringstream ss;
	if(argc<2)
	{
		cout << "This program requires an argument from the command line\n";
		cout << "Please type into the command line: \"./<name of your file> <name of your text file>\"\n";
	}
	else
	{
		file.open(argv[1]);
		if(file.fail())
		{
			cout << "Cannot open file\n";
		}
		else
		{
			file >> num_buckets >> num_lines;
			getline(file,line);
			bucket = new Bucket[num_buckets];
			for(int i=0;i<num_buckets;i++)
			{
				bucket[i].empty=true;
			}
			if(num_buckets<=0 || num_lines <=0)
			{
				cout << "Formatting error\n";
			}
			else
			{
				for(int counter=0;counter<num_lines+1;counter++)
				{
					getline(file,line);
					token = strtok(&line[0]," \n");
					ss << token;
					ss >> command;
					ss.clear();
					if(command=="PUT")
					{
						token = strtok(NULL, " \n");
						ss << token;
						ss >> bucket_num;
						ss.clear();
						token = strtok(NULL, " \n");
						ss << token;
						ss >> num_entries;
						ss.clear();
						if(!bucket[bucket_num-1].empty)
						{
							cout << "Error - bucket " << bucket_num << " is not empty\n";
						}
						else if(bucket_num <= 0 || num_entries <=0)
						{
							cout << "Error - Formatting.\n";
							break;
						}
						else
						{
							bucket[bucket_num-1].content = new int[num_entries];
							bucket[bucket_num-1].num = num_entries;
							for(int counter_two=0;counter_two<num_entries;counter_two++)
							{
								token = strtok(NULL, " \n");
								ss << token;
								ss >> bucket[bucket_num-1].content[counter_two];
								ss.clear();
							}
							bucket[bucket_num-1].empty=false;
						}
					}
					else if(command=="EMPTY")
					{
						token = strtok(NULL, " \n");
						ss << token;
						ss >> bucket_num;
						ss.clear();
						if(bucket_num > num_buckets || bucket_num <= 0)
						{
							cout << "Error - bucket " << bucket_num << " does not exist\n";
						}
						else if(bucket[bucket_num-1].empty)
						{
							cout << "Bucket " << bucket_num << " is already empty.\n";
						}
						else
						{
							delete [] bucket[bucket_num-1].content;
							bucket[bucket_num-1].empty = true;
						}
					}
					else if(command=="OUTPUT")
					{
						token = strtok(NULL, " \n");
						ss << token;
						ss >> bucket_num;
						ss.clear();
						if(bucket_num > num_buckets || bucket_num <= 0)
						{
							cout << "Error - bucket " << bucket_num << " does not exist\n";
						}
						else if(bucket[bucket_num-1].empty)
						{
							cout << "empty\n";
						}
						else
						{
							for(int k=0;k<bucket[bucket_num-1].num;k++)
							{
								cout << bucket[bucket_num-1].content[k] << " ";
							}
							cout << endl;
						}						
					}
					else
					{
						cout << "Error command, exiting.\n";
						break;
					}
				}
			}
		}
	}
	delete [] bucket;
	cin.ignore();
	return 0;
}