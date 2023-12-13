#include <iostream>
#include <vector>

enum ValueType
{
	int_type,
	char_type,
	float_type,
	bool_type
};

struct Variable
{
	int Type;
	const char* Name;
	void* Data;
};

static std::vector<Variable> Variables;

#define DECLARE(TYPE, NAME, VALUE) \
TYPE NAME = VALUE; \
Variables.push_back({TYPE ## _type, # NAME, & NAME})

int main()
{
	DECLARE(int, Test, 1);

	for (const auto& Variable : Variables)
	{
		std::cout << Variable.Data << std::endl;
	}

	return 0;
}