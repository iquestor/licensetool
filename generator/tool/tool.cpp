// tool.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "../license.h"

int main(int argc, char * argv[])
{
	char company[512] = { 0 };
	char dev[5] = { 0 } ;
	int devices = 0; 

	std::cout << "Enter Company Name:" << std::endl;

	std::cin.getline(company, sizeof(company));

	// test for numeric, non-zero number of devices. 
	while(!atoi(dev))
	{
	std::cout << "Number devices:" << std::endl;
	std::cin.getline(dev, sizeof(dev));
	devices = atoi(dev);
	}

	char master_key[512] = { 0 };

	std::cout << "Enter Master Key:" << std::endl;

	std::cin.getline(master_key, sizeof(master_key));

	char * license = generate_license(devices, company, master_key);

	std::cout << "Your License Key:" << license << std::endl;

	std::cin.get();

	return 0;
}

