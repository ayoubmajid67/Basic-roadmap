#include <iostream>
using namespace std;

int main()
{

    cout << "-------------------------------------" << endl;
    cout << (12 >= 12) << "   " << !(12 >= 12) << "   " << (1 && 1) << "   " << ((7 == 7) && (7 > 5)) << "\n";
    cout << (12 > 7) << "   " << !(12 < 7) << "   " << (true && 0) << "   " << ((7 == 7) && (7 < 5)) << "\n";
    cout << (8 < 6) << "   " << !(8 < 6) << "   " << (0 || 1) << "   " << ((7 == 7) || (7 < 5)) << "\n";
    cout << (8 == 8) << "   " << !(8 == 8) << "   " << (0 || 0) << "   " << ((7 < 7) || (7 > 5)) << "\n";
    cout << (12 <= 12) << "   " << !(12 <= 12) << "   " << !(0) << "   " << !((7 == 7) && (7 < 5)) << "\n";
    cout << (7 == 5) << "   " << !(7 == 5) << "   " << !(1 || 0) << "   " << ((7 == 7) && !(7 < 5)) << "\n";

    cout << "-------------------------------------" << endl;
    cout << (((5 > 6) && (7 == 7)) || (1 || 0)) << "\n";
    cout << (!(5 > 6 && 7 == 7) || (1 || 0)) << "\n";
    cout << (!(5 > 6 && 7 == 7) || !(1 || 0)) << "\n";
    cout << (!(5 > 6 || 7 == 7) && !(1 || 0)) << "\n";
    cout << (((5 > 6 && 7 <= 8) || (8 > 1 && 4 <= 4)) && true) << "\n";
    cout << (((5 > 6 && !(7 <= 8)) && (8 > 1 || 4 <= 3)) || true) << endl;

    return 0;
}