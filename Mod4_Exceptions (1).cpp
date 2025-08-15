// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>


// Custom exception class is structured using Geeks for Geeks example (https://www.geeksforgeeks.org/cpp/how-to-throw-custom-exception-in-cpp/)
class CustomException : public std::exception {
private:
    std::string errorMessage;

public:
	CustomException(const std::string& message) : errorMessage(message) {}

	// Override the what() function to return the custom error message
	const char* what() const noexcept {
		return errorMessage.c_str();
	}
};

// Function to simulate catching a logic error
bool do_even_more_custom_application_logic()
{
    // Throw any standard exception
    
    // Simulate an exception found in CPP Standard Library (logic_error)
    try {
        std::cout << "\nRunning Even More Custom Application Logic." << std::endl;
		std::cout << "----------------------------------------------" << std::endl;
		
        throw std::logic_error("A logic error occurred when running EVEN MORE custom application logic. Time for some unit testing?");

    }
    // Catch block is tailored to logic_error exceptions
    catch (const std::logic_error& e) { 
        std::cout << e.what() << std::endl;
    }

    return true;
}

// Function to simulate catching any standard exception -- in this case, an invalid_argument
void do_custom_application_logic()
{
    // Wrap the call to do_even_more_custom_application_logic()
    // with an exception handler that catches std::exception, displays
    // a message and the exception.what(), then continues processing
    std::cout << "\nRunning Custom Application Logic." << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    try {
        if (do_even_more_custom_application_logic())
        {
            // Simulate an error by throwing a standard exception
            throw std::invalid_argument("An invalid argument error occurred when running custom application logic. Time for some unit testing?");
        }
    }
    // Catch block is tailored to standard exceptions
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\nException Testing for the Custom Application Logic Succeeded." << std::endl;

    // Throw a custom exception derived from std::exception
    // and catch it explictly in main
    try {
        std::cout << "\nLeaving Custom Application Logic." << std::endl;
        std::cout << "----------------------------------------------" << std::endl;

		throw CustomException("A custom exception occurred when leaving custom application logic. Any questions?");
    }
    catch (const CustomException& e) {
        std::cout << e.what() << std::endl;
    }

}

float divide(float num, float den)
{
    // Throw an exception to deal with divide by zero errors using
    // a standard C++ defined exception
    if (den == 0) {
        throw std::runtime_error("STOP! Denominator (den) cannot be zero. Division by zero is undefined, which is a no-no.");
    }

    // Division can safely proceed because of exception catching in do_division()
    return (num / den);
}

void do_division() noexcept
{
    // Create an exception handler to capture ONLY the exception thrown
    // by divide.

    float numerator = 10.0f;
    float denominator = 0;

    std::cout << "\nRunning Division Logic." << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    // Try/Catch block catches exception implemented and thrown in divide()
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
}

int main()
{
    std::cout << "\nExceptions Tests!" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    // Create exception handlers that catch (in this order):
    // your custom exception
    // std::exception
    // uncaught exception 
    // that wraps the whole main function, and displays a message to the console.
    try {
        do_division();
        do_custom_application_logic();

        // Uncomment one at a time to simulate one of the three catch blocks
        
        // throw CustomException("A custom exception occurred in main(). Any questions?");
		// throw std::runtime_error("A runtime error occurred in main(). Time for some unit testing?");
        throw "strange error";
    }
    catch (const CustomException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "An errant exception was caught by the catch-all. Time to do some digging." << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
