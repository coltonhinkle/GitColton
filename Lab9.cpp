#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <limits.h>
#include <vector>
#include <sstream>

using namespace std;
//class declaration
class Signal { 
	private:
		double maxnum;
		double avgnum;
		void populate(string);
	public:
		int length;
		vector<double> data;//vector for data
		//operations
		void getAverage(void);
		void getMax(void);
		void offset(double);
		void scale(double);
		void center(void);
		void normalize(void);
		void statistics(void);
		void Sig_info(void);
		void Save_file(string);
		void menu(void);//displays menu
		Signal();
		Signal(int filenum);
		Signal(string filename);
		void operator+(double);
		void operator*(double);
};
//operator function for offsetting
void Signal::operator+(double offset) {
	for(int i=0; i<length; i++)
	{
		data[i] = data[i] + offset;
	}
}

//operator function for scaling
void Signal::operator*(double scale) {
	for(int i=0; i<length; i++)
	{
		data[i] = data[i] * scale;
	}
}

Signal operator+(const Signal &signal1, const Signal &signal2) {
	if(signal1.length != signal2.length)//length error checking
	{
		cout << "Object lengths are not equal." << endl;
		exit(-1);
	}
	else
	{
		Signal sum;
		sum.length = signal1.length;//setting length variable for for loop
		for(int i=0; i<sum.length; i++)
		{
			sum.data.push_back(signal1.data[i]);//vector function so increase size
			sum.data[i] = sum.data[i] +signal2.data[i];//adding data into sum.data
		}
		sum.getAverage();
		sum.getMax();
		return sum;//return new signal
	}
}
//function for help menu
int help_menu(char **argv) {
	cout << "Invalid arguments. Needs ./a.out -f *filename*" << endl;
	return 0;
}

//function to print menu
void Signal::menu(void) {
	while(1)
	{
		int choice;//choice variable
		//choices
		cout << "\n1) Offset " << endl;
		cout << "2) Scale" << endl;
		cout << "3) Center" << endl;
		cout << "4) Normalize" << endl;
		cout << "5) Stats" << endl;
		cout << "6) Print Signal" << endl;
		cout << "7) Save Signal" << endl;
		cout << "8) Exit" << endl;
		cout << "Select an option: ";
		cin >> choice;
		switch(choice)
		{
			case 1: { 	cout << "\nEnter the offset value: ";
					double input;
					cin >> input;
					offset(input);//call offset
					break;
				}
			case 2: { 	cout << "\nEnter the scale value: ";
				        double input;
					cin >> input;
					scale(input);
					break; 
				}
			case 3: { 	
					center(); 
					break;	
				}
			case 4: { 	
					normalize();
					break;
				}
			case 5: {	
					statistics();
					break;
				}
			case 6: {	
					Sig_info();
					break;
				}
			case 7:	{	
					cout << "Enter a filename: ";
					string newfile;
					cin >> newfile;
					Save_file(newfile);
					break;
				}
			case 8: {
					exit(EXIT_SUCCESS);
				}
			default: { 	 cout << "Invalid option" << endl; 
					 break;
				 }
		}
	}
}

int main(int argc, char **argv)
{
	//command line arguments
	if(argc == 2)//error check
		help_menu(argv);

	if(argc > 2)
	{
		if(!(strcmp(argv[1], "-f"))) // checking to see if comand line arguemt was -f
		{
			string filename(argv[2]);
			Signal OpSig1 = Signal(filename);
			OpSig1.Sig_info();
			OpSig1.menu();
		}
		else if(!(strcmp(argv[1], "-n"))) //checkingto see if it is a -n
		{
			Signal OpSig1 = Signal(atoi(argv[2])); // converting argv to integer
			OpSig1.Sig_info();
			OpSig1.menu();
		}
	}
	else {
		Signal OpSig2 = Signal(1);
		Signal OpSig3 = Signal(2);
		Signal OpSig4 = OpSig2 + OpSig3; 
		OpSig4.Sig_info();

		Signal OpSig1 = Signal();
		OpSig1.Sig_info();
		OpSig1.menu();
	}
	
	
	return 0;	
}

Signal::Signal() {
	length=0; // constructor
	maxnum=0.0;
	avgnum=0.0;
}
	
void Signal::offset(double offset_val) {
	this->operator+(offset_val); // offset number
	getAverage();
	getMax();
}

void Signal::scale(double scale_val) {
	this->operator*(scale_val); // scaling numbers
	getAverage();
	getMax();
}

void Signal::center(void) {
	int i=0;
	getAverage();
	for(i=0; i<length; i++)
	{
		data[i] = data[i]-avgnum; // storing new centered number
	}
	getAverage();
	getMax();
}

void Signal::normalize(void) {
	int i=0;
	getMax();// get new max
	for(i=0; i<length; i++)
	{
		data[i] = data[i]/maxnum; // storing new normalized number
	}
	getAverage();
	getMax();
}

void Signal::Sig_info(void) {
/* Display length, current maximum, current average */
	cout << "\nSignal length: " << length << endl;
	cout << "Maximum val:" << maxnum << endl;
	cout << "Average val:" << avgnum << endl;
}

void Signal::statistics(void) { // prints stats
	cout << "\nAverage: " << avgnum << endl;
	cout << "Max value: " << maxnum << endl;
}

void Signal::populate(string filename) {
	FILE *filepointerr = fopen(filename.c_str(), "r"); // opening file
	if(filepointerr == NULL)
	{
		cout << "Error opening file" << endl;
	}
	else
	{
		fscanf(filepointerr, "%d %lf", &length, &maxnum); // scaning data
		int i=0;
		double tmp;
		for(i=0; i<length; i++)
		{
			fscanf(filepointerr, "%lf", &tmp); // scaning data
			data.push_back(tmp); // pushing on vector
		}
		fclose(filepointerr); // closing file
	}
}

void Signal::Save_file(string filename) {
	FILE *filepointerw = fopen(filename.c_str(), "w"); // opening the file
	if(filepointerw != NULL) // checking to see if null
	{	
		fprintf(filepointerw, "%d %0.4lf\n", length, maxnum); // printing stats
		for(int i=0; i<length; i++)
		{
			fprintf(filepointerw, "%0.4lf\n", data[i]); // printing to file
		}
		fclose(filepointerw);
	}
}


void Signal::getMax(void) {
	maxnum = 0;
	int i=0;
	for(i=0; i<length; i++)
	{
		if( data[i] > maxnum )//checking for max
		{
			maxnum = data[i]; // setting new max
		}
	}
}	

void Signal::getAverage(void) {
	int i=0;
	avgnum = 0;
	for(i=0; i<length; i++)
	{
		avgnum = avgnum + data[i]; // adding numbers together
	}
	avgnum = avgnum / (double)length;// finding the avg
}

Signal::Signal(int filenum) {
	
	char buffer[32];
	sprintf(buffer, "Raw_data_%02d.txt", filenum); //puting file number into buffer
	string filename(buffer);
	populate(filename);
	getAverage();
	getMax();
}

Signal::Signal(string filename) {
	populate(filename); // fillingthe signal
	getAverage();
	getMax();
}