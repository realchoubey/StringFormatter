#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std; 


vector<string> split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while(getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}


string pseudo_string_formatter(string format_string, vector<string> list_of_parameters)
{
	int idx_number;
	int format_string_len = format_string.length();
	int num_of_string_to_replace = list_of_parameters.size();

	string final_string;

	for(int idx = 0; idx < format_string_len; idx++)
	{
		bool replace_character = true;
		if(format_string[idx] == '{')
		{
			// Get string index number.
			int next_idx = idx;
			while(format_string[next_idx] != '}')
			{
				next_idx++;
				if( (!isdigit(format_string[next_idx]) && format_string[next_idx] != '}') 
				   or next_idx == format_string_len)
				{
					next_idx = 0;
					break;
				}
			}

			if(next_idx - idx > 1)
			{
				string sub = format_string.substr(idx + 1, next_idx - idx - 1);
				stringstream str_to_int(sub); 
				str_to_int >> idx_number;

				if(idx_number < num_of_string_to_replace)
				{
					final_string.append(list_of_parameters[idx_number].c_str());
					idx += next_idx - idx;
					replace_character = false;
				}
			}
		}
		
		if(replace_character)
		{
			final_string.push_back(format_string[idx]);
		}
	}
	return final_string;
}


int main(int argc, char** argv)
{
	vector<string> list_replace_str;

	if(argc > 1)
	{
		if(argc > 2)
		{
		    list_replace_str = split(argv[2], ',');
		}

		string formatted_string = pseudo_string_formatter(argv[1], list_replace_str);
		cout << formatted_string << endl;
	}
	else
	{
		cout << "Please provide valid inputs. Expecting minimum 1 arguments" << endl;
	}

	return 0;
}
