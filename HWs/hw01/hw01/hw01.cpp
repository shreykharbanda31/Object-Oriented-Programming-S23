//
// hw01.cpp
// Created by Shrey Kharbanda on 1/28/23.
// This program decodes a file encrypted with Caesar cypher
// and prints out the decoded text to the user's terminal
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// setting function parameters

vector<string> createVector(ifstream& encrypted_file);

char decryptChar(const char& encrypted_char, const int& rotation_dist);

void decryptLine(string& encrypted_line, const int& rotation_dist);

void decryptAllLines(vector<string>& encrypted_vector, const int& rotation_dist);

void printDecodedText(const vector<string>& decrypted_vector);

int main() {
    
    ifstream encrypted_file("encrypted.txt");
    // check if file exists
    if (!encrypted_file){
        cout << "File not found!" << endl;
    }
    // extract rotation distance from the file
    int rotation_dist;
    encrypted_file >> rotation_dist;
    // moving the reading pointer to the next line
    string line;
    getline(encrypted_file, line);
    // calling all functions to decrypt and display the text
    vector<string> lines = createVector(encrypted_file);
    encrypted_file.close();
    decryptAllLines(lines, rotation_dist);
    printDecodedText(lines);
    
}

// creates a vector with all the text lines from the encrypted file
vector<string> createVector(ifstream& encrypted_file){
    string line;
    vector<string> lines;
    // reads each line from the encrypted file and adds it to the end of the vector
    while(getline(encrypted_file,line)){
        lines.push_back(line);
    }
    return lines;
}

// decrypts the encrypted character and returns the decrypted
// character based on rotation distance
char decryptChar(const char& encrypted_char, const int& rotation_dist){
    char decrypted_char = encrypted_char;
    // checks if the character is uppercase and decrypts it
    if (encrypted_char>='A' && encrypted_char<='Z'){
        decrypted_char = encrypted_char-rotation_dist;
        if (decrypted_char>'Z'){
            decrypted_char = decrypted_char - 26;
        }
        if (decrypted_char<'A'){
            decrypted_char = decrypted_char + 26;
        }
    }
    // returns the decryoted character, based on the algorithm
    return decrypted_char;
}

// decrypts and modifies all the characters in a line of encrypted text
void decryptLine(string& encrypted_line, const int& rotation_dist){
    // loops over each character in a line and modifies it
    for(size_t index = 0; index < encrypted_line.size(); ++index){
        encrypted_line[index] = decryptChar(encrypted_line[index], rotation_dist);
    }
}

// decrypts and modifies all the lines in a vector of encrypted text
void decryptAllLines(vector<string>& encrypted_vector, const int& rotation_dist){
    // loops over each line in the vector and modifies it
    for(size_t index = 0; index < encrypted_vector.size(); ++index){
        decryptLine(encrypted_vector[index], rotation_dist);
    }
}

// displays the Decrypted Text from the vector to the user in a reverse order
void printDecodedText(const vector<string>& decrypted_vector){
    // loops over each line in the vector in backwards manner
    for (size_t index = decrypted_vector.size(); index>0 ; --index) {
        string decrypted_line = decrypted_vector[index-1];
        cout << decrypted_line << endl;
    }
}
