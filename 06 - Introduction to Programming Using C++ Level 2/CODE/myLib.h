#include <iostream>
#include<string>
using namespace std;
namespace input
{

    int readIntegerNumber()
    {

        int Number;
        cout << "enter an integer :";
        cin >> Number;
        return Number;
    }
    int readIntegerInRange(int min, int max)
    {

        int number = 0;
        do
        {
            number = readIntegerNumber();
        } while (number < min || number > max);
        return number;
    }
    int readPositiveIntegerNumber()
    {

        int number = 0;
        do
        {
            number = readIntegerNumber();
        } while (number < 0);
        return number;
    }
    int readNegativeIntegerNumber()
    {
        int number = 0;
        do
        {
            number = readIntegerNumber();
        } while (number > 0);
        return number;
    }
    string readString(string text="enter a string ")
    {

        string Str;
        cout<<text; 
        getline(cin>>ws,Str);
        return Str;
    }

    string readStrWhileEqualValue(string Value)
    {

        string str = "";
        do
        {
            str = readString();
        } while (str == Value);

        return str;
    }
    float readFloat(string text="enter a  float number  "){
        float num=0; 
       cout<<text;
       cin>>num; 
       return num; 
    }
}

namespace output
{

    void printIntegerResult(string text, int result)
    {

        cout << text << " " << result << endl;
    }

}