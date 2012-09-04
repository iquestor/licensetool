// tool.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

#include "../license.h"

int main(int argc, char * argv[])
{
	char company[512] = { 0 };
	
	std::cout << "Company Name:" << std::endl;

	std::cin.getline(company, sizeof(company));

	char master_key[512] = { 0 };

	std::cout << "Master Key:" << std::endl;

	std::cin.getline(master_key, sizeof(master_key));

	char * license = generate_license(1, company, master_key);

	std::cout << license << std::endl;

	std::cin.get();

	return 0;
}

