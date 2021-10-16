#include <iostream>
#include <stdlib.h> 
#include <cstring>
#include <math.h>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;

double CalculateExpression(const char s[], int &idx, int level = 1);
double EvaluateTerm(const char s[], int &idx);
double StringToNumber(const char s[], int &idx);
int OperatorPriority(char op);
double CalculateOperator(double left, double right, char op);
void Solve(char s[], int idx, int add, int sub, int mul, int div, int pow, bool seq_pow);
int FindSpace(const char s[], int idx);

const int MAX_EXPR_LENGTH = 100;	  // Maximum number of the characters in a single expression
const int MAX_OPERATOR_LEVEL = 3;	  // Maximum level of the priority of operators
double max_val = -INFINITY;			  // Maximum value of mathematical expressions
char max_s[MAX_EXPR_LENGTH + 1] = ""; // Expression which returns the maximum value
int two_power=0;
vector<string> postfix;

int main()
{
	char s[MAX_EXPR_LENGTH + 1] = "";
	int idx=0;

	 //========================================ORIGINAL CODE===============================
	cout << ">>";
	//cin.getline(s, MAX_EXPR_LENGTH + 1);  // getline member function

	 //READ FROM FILE MODIFICATION
	 
	ifstream file("inputs.txt");
	string readline;
	getline(file, readline);
	for(int i=0; i<readline.length(); i++){
		s[i]=readline[i];
	}

	//ORIGINAL READ S FROM USER INPUT
	
	cout << s << endl;
	if (strcmp(s, "exit") == 0)
	{   //strcmp function
		cout << "Exiting.." << endl;
		exit(1);
	}

	 //TURN ON TO RUN CALCULATOR
	
	double answer=CalculateExpression(s, idx, 1);
	cout<<"answer is : "<<answer<<endl;
	for(const auto& value: postfix) {
    cout << value << " ";
}
	return 0;
	
	int add, sub, mul, div, pow, enter;
	cout << "Number of add sub mul div pow\n>>";
	//cin >> add >> sub >> mul >> div >> pow;
	//READ FROM FILE MODIFICATION
	file>> add >> sub >> mul >> div >> pow;
	
	Solve(s, idx, add, sub, mul, div, pow, false);

	if (isnan(max_val) || isinf(max_val))
	{ // isnan, isinf function, end of c-string = 0
		cout << "Error while evaluating!" << endl;
	}
	else
	{
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
    	cout.precision(6);
		cout << "Maximum Value: " << max_val << endl;
		cout << "Expression: " << max_s << endl;
	}

}

void Solve(char s[], int idx, int add, int sub, int mul, int div, int pow, bool seq_pow)
{

	int old_idx = idx;
	int new_idx = FindSpace(s, idx);

	if (new_idx == -999)
	{
		double currentValue = 0;
		new_idx = 0;
		
		for (int i = 0; i < MAX_EXPR_LENGTH; i++)//PRINT EACH EXPRESSION
		{
			cout << s[i] << " ";
		}
		cout << endl;
		try
		{
			currentValue = CalculateExpression(s, new_idx, 1);
			two_power=0;
		}
		catch (const invalid_argument &e)
		{
			cout << "exception caught, value ignored" << endl;
			seq_pow = true;
		}
		if (currentValue > max_val && !seq_pow)
		{
			strcpy(max_s, s);
			s[old_idx] = ' ';
			max_val = currentValue;
			return;
		}
		s[old_idx] = ' ';
		return;
	}

	for (int options = 0; options < 5; options++)
	{
		if (options == 0 && add > 0)
		{
			s[new_idx] = '+';
			add -= 1;
			Solve(s, new_idx, add, sub, mul, div, pow, seq_pow);
			add +=1;
		}
		else if (options == 1 && sub > 0)
		{
			s[new_idx] = '-';
			sub -= 1;
			Solve(s, new_idx, add, sub, mul, div, pow, seq_pow);
			sub +=1;
		}
		else if (options == 2 && mul > 0)
		{
			s[new_idx] = '*';
			mul -= 1;
			Solve(s, new_idx, add, sub, mul, div, pow, seq_pow);
			mul+=1;
		}
		else if (options == 3 && div > 0)
		{
			s[new_idx] = '/';
			div -= 1;
			Solve(s, new_idx, add, sub, mul, div, pow, seq_pow);
			div+=1;
		}
		else if (options == 4 && pow > 0)
		{
			s[new_idx] = '^';
			pow -= 1;
			Solve(s, new_idx, add, sub, mul, div, pow, seq_pow);
			pow+=1;
		}
	}
	s[old_idx]=' ';


}

int FindSpace(const char s[], int idx)
{
	// It finds the next index of the blank ‘ ’ in string s
	for (int i = idx + 1; i < MAX_EXPR_LENGTH + 1; i++)
	{
		if (s[i] == ' ')
		{
			return i;
		}
	}
	return -999;
}

double StringToNumber(const char s[], int &idx)
{
	char number[MAX_EXPR_LENGTH]="";
	int count=0;
	for(int i=idx; i<MAX_EXPR_LENGTH; i++){
		if(isdigit(s[i]) || s[i]=='.'){
			number[count]=s[i];
			count+=1;
		}
		else{
			break;
		}
	}
	double output=0;
	idx+=count-1;
	output=atof(number);
	return output;
}

double EvaluateTerm(const char s[], int &idx)
{
	// It calculates the expression in parenthesis or converts the string to float number. idx value is updated to the next unread index.
	/*
	To-do
	*/
	double returnValue;
	if (isdigit(s[idx]))
	{ //if input is number
		returnValue = StringToNumber(s, idx);
	}
	if (s[idx] == '(')
	{ //if input is open paranthesis
		idx += 1;
		returnValue = CalculateExpression(s, idx, 1);
		if (s[idx] == ')')
		{
			idx++;
		}
		return returnValue;
	}
	if (s[idx] == '-')
	{ 
		idx+=1;
		returnValue = StringToNumber(s, idx) * -1.0;
	}
	for (int i = idx; i < MAX_EXPR_LENGTH; i++)
	{ //changes idx to index of next operator
		if (isdigit(s[i]) == 0)
		{ 
			if (s[i] == ')')
			{
				idx = i;
			}
			idx = i;
			break;
		}
	}

	return returnValue;
}

int OperatorPriority(char op)
{ 
	// It returns the priority of given operator ‘op’
	if (op == '+' || op == '-')
	{
		return 1;
	}
	if (op == '*' || op == '/')
	{
		return 2;
	}
	if (op == '^')
	{
		return 3;
	}
	else
	{ //return -1 if character is not a operator --> is number
		return -1;
	}

}

double CalculateOperator(double left, double right, char op)
{
	if (op == '+')
	{
		//cout<<left<<" + "<<right<<endl;
		return left + right;
	}
	if (op == '-')
	{
		//cout<<left<<" - "<<right<<endl;
		return left - right;
	}
	if (op == '*')
	{
		//cout<<left<<" * "<<right<<endl;
		return left * right;
	}
	if (op == '/')
	{
		if (right == 0)
		{
			cout << "error divide by zero" << endl;
			throw invalid_argument("divide by zero");
			return -999;
		}
		//cout<<left<<" / "<<right<<endl;
		return left / right;
	}
	if (op == '^')
	{
		//cout<<left<<" ^ "<<right<<endl;
		double powered=pow(left,right);
		if(isinf(powered) || isnan(powered)){
			throw invalid_argument("overflowed because sequential power");
			return 0;
		}
		return pow(left, right);
	}
	else
	{
		return -999;
	}
}

double CalculateExpression(const char s[], int &idx, int level)
{
	/*
	This calculates the expression recursively
	It returns the value calculated from idx to end point of expression
		- s[idx] to end point should be valid expression
		- Ex) *3/2+5 is invalid expression, 3+2*5 is valid expression
	Internally, it computes the value calculated by the results from left-subtree and right-subtree using the given operator s[idx]
	Deeper level operators should be computed first
	*/
	double returnValue = 0;

	if (level > MAX_OPERATOR_LEVEL)//BASE CASE
	{
		if (OperatorPriority(s[idx] < 1))
		{ 
			returnValue = EvaluateTerm(s, idx);
			return returnValue;
		}
	}
	int twice=0;
	returnValue = CalculateExpression(s, idx, level + 1);


	while (OperatorPriority(s[idx]) == level)
	{
		/*
		if (level == 3)
		{
			twice++;
			two_power++;
		}
		if(level!=3){
			two_power=0;
		}
		if (two_power==2)
		{
			cout << "cannot have two ^ in a row" << endl;
			cout<<endl;
			two_power=0;
			throw invalid_argument("two pow in a row");
		}*/
		char oper = s[idx];
		idx += 1;
		
		double operand2 = CalculateExpression(s, idx, level + 1);
		postfix.push_back(to_string(returnValue));
		postfix.push_back(to_string(operand2));
		string op={oper};
		postfix.push_back(op);
		
		

		returnValue = CalculateOperator(returnValue, operand2, oper);

	}
	return returnValue;
}