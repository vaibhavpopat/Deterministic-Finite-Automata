/*
For giving user defined-input, format:
Number of symbols
Symbols used in DFA
Number of grammar rules
Grammar rules in {} for each symbol
String 
Start symbol 
Number of final states
Final state
*/
#include<bits/stdc++.h>
using namespace std;

int valid(string s,unordered_set<char> symbols)							//checks if the input string has symbols only used from the given set
{
    int flag=1,len=s.length();
    while(len && flag)
    {
        len--;
        if(symbols.find(s[len])==symbols.end()) flag=0;
    }
    return flag;
}

bool accepts(int num_states,vector<char> **dfa,string s,int start_state,vector<int> final )		//this function checks if the given string is accepted. 
{
    int i,j;
    int curr=start_state;																		//curr variable is set to the start state
    bool flag1=true,flag2=false;
    int len=s.length();
    for(i=0;i<len && flag1;i++)																	//Every variable is traversed by traversing the string.  
    {
        flag2=false;
        for(j=0;j<num_states && !flag2;)
        {
            if(find(dfa[curr][j].begin(),dfa[curr][j].end(),s[i])!=dfa[curr][j].end()) flag2=true;		//next state is found here to move to it.
            else j++;
        }
        if(flag2==false) flag1=false;
        else curr=j;
    }
    if(flag1 && find(final.begin(),final.end(),curr)!=final.end()) return true;					//curr variable is checked if it belongs to the final state.
    else return false;
}

int main()
{
    int num_symbols;
    unordered_set <char> symbols;			//to store symbols used in DFA
    int num_states;							//store number of states
    int i,j;
    char input;								
    vector<char> v;	
    v.clear();
    vector<char> **dfa;						//to store DFA Matrix
    string s;	
    int start_state,num_final_states;
    vector<int> final;						//stores final states.
    int temp;
    int choice;
    cout<<"1)to take input from file"<<endl;	
    cout<<"2)to take user input"<<endl;
    cin>>choice;
    if(choice==1)
    {
    	ifstream infile; 
        infile.open("toc.txt");
	    infile>>num_symbols;				//input number of symbols
	    for(i=0;i<num_symbols;i++)
	    {
		infile>>input;
		symbols.insert(input);				//Taking symbols used in DFA
	    }
	    infile>>num_states;					//Number of states
	    dfa=new vector<char> *[num_states];
	    for(i=0;i<num_states;i++)			//Storing DFA represented as a matrix
	    {
		dfa[i]=new vector<char>[num_states];
		for(j=0;j<num_states;j++)
		{
		    infile>>input;
		    if(input=='{')
		    {
		        infile>>input;
		        while(input!='}')
		        {
		          dfa[i][j].push_back(input);
		          infile>>input;
		        }
		    }
		}
	    }
	    infile>>s;							//Taking input string
	    infile>>start_state;				//Inputting Start state
	    infile>>num_final_states;			//Inputting number of final states	
	    while(num_final_states)				//Inputting final states
	    {
		infile>>temp;
		final.push_back(temp);
		num_final_states--;
	    }
         
    }
    if(choice==2)							//Taking all the above input, just from the user 
    {
	    cout<<"Enter number of symbols"<<endl;
	    cin>>num_symbols;
	    cout<<"Enter symbols"<<endl;
	    for(i=0;i<num_symbols;i++)
	    {
		cin>>input;
		symbols.insert(input);
	    }
	    cout<<"Enter number of states"<<endl;
	    cin>>num_states;
	    dfa=new vector<char> *[num_states];
	    cout<<"Enter states:"<<endl;
	    for(i=0;i<num_states;i++)			//Taking user defined input in the correct format.
	    {
		dfa[i]=new vector<char>[num_states];
		for(j=0;j<num_states;j++)
		{ 
		    cin>>input;
		    if(input=='{')
		    {
		        cin>>input;
		        while(input!='}')
		        {
		          dfa[i][j].push_back(input);		//pushing input in dfa matrix
		          cin>>input;
		        }
		    }
		}
	    }
	    cout<<"Enter String"<<endl;					//taking some other input parameters
	    cin>>s;	
	    cout<<"Enter start state "<<endl;
	    cin>>start_state;
	    cout<<"Enter number of final states"<<endl;
	    cin>>num_final_states;
	    cout<<"Enter final states"<<endl;
	    while(num_final_states)
	    {
		cin>>temp;
		final.push_back(temp);
		num_final_states--;
	    }
     }
    if(valid(s,symbols)==0) return 0;									//checks if the input string has symbols only used from the given set
    if(accepts(num_states,dfa,s,start_state,final)) cout<<"String "<< s <<"  "<<"is accepted by DFA"<<endl;			//accepts function checks if the string is accepted.
    else cout<<"String "<<s<<" is not accepted by DFA"<<endl;

    return 0;
}

