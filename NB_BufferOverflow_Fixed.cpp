// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	const std::string account_number = "CharlieBrown42";
	char user_input[20];

	bool valid_input = false;

	while (!valid_input) {
		try {
			std::cout << "Enter a value: ";
			std::cin.getline(user_input, sizeof(user_input));

			// cin fails if the input received exceeds the limit declared using sizeof()
			if (std::cin.fail()) {
				std::cin.clear(); // clear the fail state
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the input buffer

				std::cout << "\nYou entered: " << user_input << std::endl;
				throw std::runtime_error("The entered value is too long. Please input a value with less than 20 characters.\n");
			}
			else {
				valid_input = true; // input is valid, exit the loop
			}

		}
		catch (const std::exception& e) {
			std::cerr << "ERROR: " << e.what() << std::endl;
		}
	}

	std::cout << "\nYou entered: " << user_input << std::endl;
	std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
