#include <iostream>
#include <string>
#include "FileHandler.h"

using namespace std;

int main()
{
    string filePath;

    cout << "Path: ";
    cin >> filePath;
    FileHandler* handler = new FileHandler(filePath);
    handler->parser();
    handler->output();
}