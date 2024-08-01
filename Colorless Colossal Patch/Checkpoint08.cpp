#include <algorithm>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <map>

	// -----------------------
	// FUNCTION 1 REQUIREMENTS
	// -----------------------
	// Process the transaction records in the given text file so you can maintain all current stock prices
	// Only process the file up to AND INCLUDING the time value passed along as the function parameter
	// Each file record is in sequential time order so you can safely stop reading when the time passes
	// Each file record consists of three fields:
	//				TIME (integer) the transaction was made
	//				COMPANY (string) name 
	//				PRICE (double) the stock is now currently at
	// Example lines from the stocks.txt text file:
	// 				0     AAPL 183.05
	//				0     AMZN 187.48
	// 				0     ASML 930.29
	//				0     AVGO 1332.8
	//
	// If the text file can't open for any reason, simply return an empty map structure
	//
	// If the time parameter is less than zero, then treat time as if it was zero
	//
	// If this matters to you, please note that not every stock changes their prices every time unit
	// The stock price will represent the value of the last transaction made, whenever that was
	//
	// With the stocks.txt file, your map would contain 20 elements since there are 20 stocks listed throughout the file
	// AAPL  AMZN  ASML  AVGO  BRK.B  GOOGL  JPM  LLY  MA  META  MSFT  NVDA  NVO  PG  TSLA  TSM  UNH  V  WMT  XOM
	// HOWEVER, you can't just hardcode this since each file will obviously have different stocks in them

std::map<std::string, double> GetAllCompanyStockPricesAtSpecificTime(const std::string& filename, int time)
{
		std::map<std::string, double> stockPrices;

		std::ifstream file(filename);
		if (file.fail())
		{
				std::cerr << "Failed to open file: " << filename << std::endl;
				return stockPrices; // Return an empty map if file opening fails
		}

		if (time < 0)
				time = 0; // Treat negative time as zero

		int fileTime;
		std::string company;
		double price;

		while (file >> fileTime >> company >> price)
		{
				if (fileTime > time)
						break; // Stop processing if time in the file exceeds the given time

				stockPrices[company] = price; // Update or insert the stock price for the company
		}

		file.close();
		return stockPrices;
}

	// -----------------------
	// FUNCTION 2 REQUIREMENTS
	// -----------------------
	// Use the previous function to get the status of the entire stock market at the time value passed along as the function parameter
	// Then use the map to get the current stock price of the specific company asked for in the other function parameter
	// If the specific company asked for cannot be found in the map, return -1.0 as the value 
	// 
	// If this matters to you, please note that not every stock changes their prices every time unit
	// The stock price will represent the value of the last transaction made, whenever that was
	//
	// With the stocks.txt file, your map would contain 20 elements since there are 20 stocks listed throughout the file
	// AAPL  AMZN  ASML  AVGO  BRK.B  GOOGL  JPM  LLY  MA  META  MSFT  NVDA  NVO  PG  TSLA  TSM  UNH  V  WMT  XOM
	// HOWEVER, you can't just hardcode this since each file will obviously have different stocks in them
double GetSpecificCompanyStockPriceAtSpecificTime(const std::string& filename, const std::string& company, int time)
{
		std::map<std::string, double> stockPrices = GetAllCompanyStockPricesAtSpecificTime(filename, time);

		if (stockPrices.find(company) != stockPrices.end())
				return stockPrices[company];
		else
				return -1.0; // Return -1.0 if the company is not found in the map
}

	// -----------------------
	// FUNCTION 3 REQUIREMENTS
	// -----------------------
	// Use the previous functions to get the values of each and every company's stock price at the two time values passed along as the function parameters
	// Then use the two maps to get difference percentages in stock prices for each specific company
	// DIFFERENCE PERCENTAGE = (newerValue - olderValue) * 100.0 / olderValue;
	// Deduce the company with the largest difference percentage and print it out as follows, and this is only an example:
	// "BRAD GAINED THE MOST BETWEEN THESE TIMES, CHANGING FROM 150.02 TO 200.12, A CHANGE OF 25.03%"
	// If no stock listings can be found, print "THERE DOES NOT APPEAR TO BE A STOCK VALUE LISTING FOR ANY COMPANY"
	// 
	// If this matters to you, please note that not every stock changes their prices every time unit
	// The stock price will represent the value of the last transaction made, whenever that was
	//
	// With the stocks.txt file, your map would contain 20 elements since there are 20 stocks listed throughout the file
	// AAPL  AMZN  ASML  AVGO  BRK.B  GOOGL  JPM  LLY  MA  META  MSFT  NVDA  NVO  PG  TSLA  TSM  UNH  V  WMT  XOM
	//
	// HOWEVER, you can't just hardcode this since each file will obviously have different stocks in them
	// How could you find all the company names from a map data structure?

void DetermineAndPrintStockWithBestPerformance(const std::string& filename, int time1, int time2)
{
		std::map<std::string, double> stockPrices1 = GetAllCompanyStockPricesAtSpecificTime(filename, time1);
		std::map<std::string, double> stockPrices2 = GetAllCompanyStockPricesAtSpecificTime(filename, time2);

		if (stockPrices1.empty() || stockPrices2.empty())
		{
				std::cout << std::endl << "THERE DOES NOT APPEAR TO BE A STOCK VALUE LISTING FOR ANY COMPANY" << std::endl << std::endl;
				return;
		}

		std::string bestCompany;
		double bestPercentage = -1.0;

		for (const auto& pair : stockPrices1)
		{
				const std::string& company = pair.first;
				double price1 = pair.second;
				double price2 = stockPrices2[company];

				double percentage = (price2 - price1) * 100.0 / price1;

				if (percentage > bestPercentage)
				{
						bestPercentage = percentage;
						bestCompany = company;
				}
		}

		std::cout << std::endl << bestCompany << " GAINED THE MOST BETWEEN THESE TIMES, CHANGING FROM "
							<< stockPrices1[bestCompany] << " TO " << stockPrices2[bestCompany] << ", A CHANGE OF "
							<< std::fixed << std::setprecision(2) << bestPercentage << "%" << std::endl << std::endl;
}



// -----------------------------------------------------------
// YOU MAY NOT MODIFY ANY OF THE CODE FOUND BELOW THIS MESSAGE
// -----------------------------------------------------------

void PrintAllTransactionsBySpecificCompany(const std::string& filename, const std::string& specificCompany)
{
	std::cout << std::endl;
	std::ifstream file(filename);
	if (file.fail() == true)
	{
		std::cout << filename << " FILE DOES NOT EXIST - PLEASE CHECK YOUR WORKING FOLDER" << std::endl;
	}
	else
	{
		std::cout << "COMPANY   TIME    VALUE" << std::endl;
		std::cout << "-------   ----    -----" << std::endl;
		while (file.eof() == false)
		{
			int time;
			std::string company;
			double value;
			file >> time >> company >> value;
			if (company == specificCompany)
			{
				std::cout << std::left << std::setw(5) << company;
				std::cout << std::right << std::setw(9) << time;
				std::cout << std::right << std::setw(9) << std::fixed << std::setprecision(2) << value << std::endl;
			}
		}
	}
	file.close();
}

int PrintMainMenuAndGetSelection()
{
	std::cout << "----------------------" << std::endl;
	std::cout << "       MAIN MENU" << std::endl;
	std::cout << "----------------------" << std::endl;
	std::cout << "1) PRINT ALL TRANSACTIONS FOR A SPECIFIC STOCK" << std::endl;
	std::cout << "2) GET STOCK PRICE AT SPECIFIC TIME" << std::endl;
	std::cout << "3) GET CHANGE IN STOCK PRICE OVER TIME" << std::endl;
	std::cout << "4) DETERMINE STOCK WITH BEST PERFORMANCE OVER TIME" << std::endl;
	std::cout << "5) EXIT PROGRAM" << std::endl << std::endl;

	int choice;
	do
	{
		std::cout << "CHOICE? ";
		std::cin >> choice;
	} while ((choice < 1) || (choice > 5));

	return choice;
}

void HandleMenuChoice1()
{
	std::cout << std::endl << "WHICH COMPANY? ";
	std::string s;
	std::cin >> s;

	for (char& c : s)
		c = toupper(c);

	PrintAllTransactionsBySpecificCompany("stocks.txt", s);
	std::cout << std::endl;
}

void HandleMenuChoice2()
{
	std::cout << std::endl << "WHICH COMPANY? ";
	std::string s;
	std::cin >> s;

	for (char& c : s)
		c = toupper(c);

	std::cout << "AT WHAT TIME?  ";
	int t;
	std::cin >> t;
	double value = GetSpecificCompanyStockPriceAtSpecificTime("stocks.txt", s, t);

	if (value != -1.0)
		std::cout << std::endl << "THE STOCK VALUE AT THAT TIME IS: $" << value << std::endl;
	else
		std::cout << std::endl << "THERE DOES NOT APPEAR TO BE A STOCK VALUE LISTING FOR THAT COMPANY" << std::endl;

	std::cout << std::endl;
}

void HandleMenuChoice3()
{
	std::cout << std::endl << "WHICH COMPANY? ";
	std::string s;
	std::cin >> s;

	for (char& c : s)
		c = toupper(c);

	std::cout << "AT WHAT START TIME? ";
	int t1;
	std::cin >> t1;
	std::cout << "AT WHAT END TIME?   ";
	int t2;
	std::cin >> t2;

	double value1 = GetSpecificCompanyStockPriceAtSpecificTime("stocks.txt", s, t1);
	double value2 = GetSpecificCompanyStockPriceAtSpecificTime("stocks.txt", s, t2);
	if ((value1 != -1.0) && (value2 != -1.0))
	{
		std::cout << std::endl << "THE STARTING STOCK VALUE IS: $" << value1 << std::endl;
		std::cout << "THE ENDING STOCK VALUE IS:   $" << value2 << std::endl;
		double diff = (value2 - value1) / value1 * 100.0;
		std::cout << std::endl << "THE DIFFERENCE IN PRICE IS:  " << diff << "%" << std::endl;
	}
	else
		std::cout << std::endl << "THERE DOES NOT APPEAR TO BE A STOCK VALUE LISTING FOR THAT COMPANY" << std::endl;

	std::cout << std::endl;
}

void HandleMenuChoice4()
{
	std::cout << std::endl << "AT WHAT START TIME? ";
	int t1;
	std::cin >> t1;
	std::cout << "AT WHAT END TIME?   ";
	int t2;
	std::cin >> t2;
	DetermineAndPrintStockWithBestPerformance("stocks.txt", t1, t2);
}

int main()
{
	int choice = 0;
	while (choice != 5)
	{
		choice = PrintMainMenuAndGetSelection();

		if (choice == 1)
			HandleMenuChoice1();
		else if (choice == 2)
			HandleMenuChoice2();
		else if (choice == 3)
			HandleMenuChoice3();
		else if (choice == 4)
			HandleMenuChoice4();
	}

	return 0;
}