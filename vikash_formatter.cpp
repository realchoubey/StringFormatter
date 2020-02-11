#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std; 


vector<std::string> split(const std::string& s, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}


string get_replaced_string(string format_string, vector<string> list_of_parameters)
{
	int idx_number;
	int format_string_len = format_string.length();
	string final_string;
	for( int idx = 0; idx < format_string_len; idx ++)
	{
		if(format_string[idx] == '{')
		{
			if(format_string[idx + 2] == '}')
			{
				idx_number = (int)format_string[idx + 1] - 48;
				final_string.append(list_of_parameters[idx_number].c_str());
				idx += 2;
			}
			else
			{
				final_string.push_back(format_string[idx]);
			}
		}
		else
		{
			final_string.push_back(format_string[idx]);
		}
	}
	return final_string;
}


int main(int argc, char** argv) 
{
    vector<string> list_replace_str = split(argv[2], ',');

    cout << get_replaced_string(argv[1], list_replace_str) << endl;

    return 0; 
}