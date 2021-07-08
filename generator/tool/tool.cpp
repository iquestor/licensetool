// tool.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../license.h"

int main(int argc, char * argv[])
{
	char company[512] = { 0 };
	char dev[5] = { 0 } ;
	char licType[5] = { 0 };
	char datapoints[5] = { 0 };
	char expiry[10] = { 0 };
	char months[5] = { 0 };
	char master_key[512] = { 0 };
	unsigned int devices = 0;
	unsigned int ilType = 0;
	unsigned int iMonths = 0;
	bool disableData = 0;

	// test for company name. 
	while (strlen(company) < 3)
	{
		std::cout << "Enter your Company Name:" << std::endl;
		std::cin.getline(company, sizeof(company));	
		if (strlen(company) < 3) std::cout << "[" << company << "] isn't a valid Company Name!\n" << std::endl;
	}
	
	// test for numeric, non-zero number of devices. 
	while(!atoi(dev))
	{
	std::cout << "Number devices:" << std::endl;
	std::cin.getline(dev, sizeof(dev));
	devices = atoi(dev);
	}

	// test for Y or N NOT IMPLEMENTED
	while (strcmp(datapoints, "Y") && strcmp(datapoints, "N"))
	{
		std::cout << "Disable Data Points? (Y/N):" << std::endl;
		std::cin.getline(datapoints, sizeof(datapoints));
		disableData = strcmp(datapoints, "N");
		if (!strcmp(datapoints, "Y")) std::cout << "Data Points are DISABLED." << std::endl;
		else if (!strcmp(datapoints, "N")) std::cout << "Data Points are ENABLED." << std::endl;
		else std::cout << "[" << datapoints << "] isn't a valid answer!\n" << std::endl;
	}

	// expiry date
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	// months are 0-11, year is since 1900
	//std::cout << tm.tm_mon + 1 << "/" << tm.tm_mday << "/" << (tm.tm_year + 1900) << std::endl;
	
	while (!atoi(months))
	{
		std::cout << "Todays Date is: " << tm.tm_mon + 1 << "-" << tm.tm_mday << "-" << (tm.tm_year + 1900) << std::endl;
		std::cout << "Add Number Months (ie, 12 to expire license 1 year from today.)" << std::endl;
		std::cin.getline(months, sizeof(months));
		iMonths = atoi(months);
		tm.tm_year = tm.tm_year + iMonths / 12; 
		tm.tm_mon = (tm.tm_mon + iMonths) % 12;
	}
		
	sprintf(expiry,"%0d-%0d-%d\0", tm.tm_mon + 1 ,tm.tm_mday ,(tm.tm_year + 1900));
	std::cout << "License Expiry Date is: " << expiry << std::endl;

	// test for numeric, non-zero number of devices. 
	while (ilType != 1 && ilType != 2)
	{
		std::cout << "License Type (1=Perpetual, 2=Subscription):" << std::endl;
		std::cin.getline(licType, sizeof(licType));
		ilType = atoi(licType);
		if (ilType != 1 && ilType != 2) { std::cout << "[" << ilType << "] isn't a valid type. " << std::endl; }
	}

	if (ilType == 1) std::cout << "License type: Perpetual." << std::endl;
	else std::cout << "License type: Subscription." << std::endl;
	
	while (strlen(master_key) < 10)
	{
		std::cout << "Enter Master Key:" << std::endl;
		std::cin.getline(master_key, sizeof(master_key));
		if (strlen(master_key) < 10) std::cout << "[" << master_key << "] isn't a valid master_key!\n" << std::endl;
	}
	
	char * license = generate_license(devices, company, disableData, expiry, ilType, master_key);
	unsigned int * d = &devices;
	unsigned int * lt = &ilType;
	bool * dataDisabled = 0;
	int res = validate_license(license, d, dataDisabled, expiry, lt, master_key);

	if(!res) std::cout << "License validated!" << std::endl;
	else std::cout<< "Invalid license, code:[" << res << "]" << std::endl;
	std::cout << "Your License Key:" << license << std::endl;
	std::cout << "Press any key to exit.";
	std::cin.get();
	

	return 0;
}

