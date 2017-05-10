#ifndef command_hh
#define command_hh

#include "RShellBase.hh"
#include <string>
#include <vector>

using namespace std;

class Command: public RShellBase {
	protected:
		string userInput;
		vector<string> arguments;
		char * argArr[256];
		bool pass;
	public:
		Command() { };
		Command(string input) : userInput(input) { };
		void execute();
		void setInput(string input);
		void parse();
		void printInput();
		void printArgs();
		string getInput();
		vector<string> getArgs();
		char ** getArr();
		void passed();
		void failed();
		bool getPass();
};

#endif
