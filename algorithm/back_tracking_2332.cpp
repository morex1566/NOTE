#include <vector>
#include <string>
#include <iostream>
#include <map>

struct Hash
{
	std::vector<std::vector<char>> table;
	
	void insert(int key, std::string data)
	{
		for (int i = 0; i < data.size(); i++)
		{
			table[key].push_back(data[i]);
		}
	}

	bool find(int key, char data)
	{
		for (int i = 0; i < table[key].size(); i++)
		{
			if (table[key][i] == data) { return true; }
		}

		return false;
	}
};

int main()
{
	Hash					 hash;
	std::string				 phone_number;
	int						 word_count;
	int						 corrected_count;
	std::vector<std::string> corrected_buffer;

	hash.insert(0, "oqz");
	hash.insert(1, "ij");
	hash.insert(2, "abc");
	hash.insert(3, "def");
	hash.insert(4, "gh");
	hash.insert(5, "kl");
	hash.insert(6, "mn");
	hash.insert(7, "prs");
	hash.insert(8, "tuv");
	hash.insert(9, "wxy");

	std::cin >> phone_number;
	std::cin >> word_count;
	corrected_count = 0;

	for (int i = 0; i < word_count; i++)
	{
		std::string string;
		std::cin >> string;	

		bool corrected = true;
		for (int i = 0; i < string.size(); i++)
		{
			if (!hash.find(phone_number[i], string[i]))
			{
				corrected = false;
				break;
			}
		}

		if (corrected)
		{
			corrected_count++;
			corrected_buffer.push_back(string);
		}
	}

	if (corrected_count == 0)
	{
		std::cout << 0 << "\nNo solution.";
	}
	else
	{
		std::cout << corrected_count << std::endl;
		for (int i = 0; corrected_buffer.size(); i++)
		{
			std::cout << corrected_buffer[i] << std::endl;
		}
	}
}