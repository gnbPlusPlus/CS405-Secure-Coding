// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// 
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// 
/// <returns>transformed string</returns>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    // get lengths now instead of calling the function every time.
    // this would have most likely been inlined by the compiler, but design for perfomance.
    const auto key_length = key.length();
    const auto source_length = source.length();

    // assert that our input data is good
    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // loop through the source string char by char
    for (size_t i = 0; i < source_length; ++i)
    {
      // transform each character based on an xor of the key modded constrained to key length using a mod
		output[i] = source[i] ^ key[i % key_length];
    }

    // our output length must equal our source length
    assert(output.length() == source_length);

    // return the transformed string
    return output;
}

std::string read_file(const std::string& filename)
{
    std::string file_text;

    // Open the file
    std::ifstream file(filename);

    // Check for successful file opening
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;

        return "John Q. Smith\nThis is my test string";  // Return default string if file fails to open
    }

    // Use a loop + getline() to read each line from the file and append it to file_text
    std::string line;
    while (std::getline(file, line)) {
        file_text += line + "\n";
    }

    // Close the file
    file.close();

    return file_text;
}

std::string get_student_name(const std::string& string_data)
{
    std::string student_name;

    // find the first newline
    size_t pos = string_data.find('\n');
    // did we find a newline
    if (pos != std::string::npos)
    { // we did, so copy that substring as the student name
        student_name = string_data.substr(0, pos);
    }

    return student_name;
}

void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
    //  Open the file
    std::ofstream file(filename);

    // Check for successful file opening
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;

		return;  // Exit the function if file opening fails
    }

    //  Line 1: student name
    file << student_name << std::endl;

    //  Line 2: timestamp (yyyy-mm-dd)
    time_t timestamp = time(nullptr);
    struct tm time_info;
    localtime_s(&time_info, &timestamp);

    file << std::put_time(&time_info, "%Y-%m-%d") << std::endl;

    //  Line 3: key used
    file << key << std::endl;

    //  Line 4+: data
    file << data << std::endl;  // Since multi-lined data is handled in read_file(), it's fine to use one line here

    // Close the file
    file.close();

}

int main()
{
    std::cout << "Encyption Decryption Test!" << std::endl;

    // Input file format:
    // Line 1: <student's name>
    // Line 2: <Lorem Ipsum Generator website used>
    // Lines 3+: <lorem ipsum generated with 3 paragraphs> 
   
    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrypteddatafile.txt";
    const std::string source_string = read_file(file_name);
    const std::string key = "password";

    // get the student name from the data file
    const std::string student_name = get_student_name(source_string);

    // encrypt sourceString with key
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // save encrypted_string to file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // decrypt encryptedString with key
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // save decrypted_string to file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;

    // students submit input file, encrypted file, decrypted file, source code file, and key used
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
