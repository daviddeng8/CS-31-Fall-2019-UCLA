// Suggested fine calculation

#include <iostream>
#include <string>
using namespace std;

int main()
{
      // Get and validate defendant

    cout << "Defendant: ";
    string defendant;
    getline(cin, defendant);
    if (defendant == "")
    {
        cout << "---\nYou must enter a defendant name." << endl;
        return 1;
    }

      // Get and validate amount paid

    cout << "Amount paid (in thousands): ";
    double amt;
    cin >> amt;
    cin.ignore(10000, '\n');
    if (amt < 0)
    {
        cout << "---\nThe amount paid must not be negative." << endl;
        return 1;
    }

      // Get and validate fake athlete status

    cout << "Fake athlete? (y/n): ";
    string fakeAth;
    getline(cin, fakeAth);
    if (fakeAth != "y"  &&  fakeAth != "n")
    {
        cout << "---\nYou must enter y or n." << endl;
        return 1;
    }

      // Amount paid cutoff points and fine rates

    const double BASE_FINE          =   20;
    const double BRACKET_CUTOFF_1   =   40;
    const double BRACKET_CUTOFF_2   =  250;
    const double RATE_1             = 0.66;
    const double RATE_2_NO_FAKE_ATH = 0.10;
    const double RATE_2_FAKE_ATH    = 0.22;
    const double RATE_3             = 0.14;

      // Compute fine

    double fine = BASE_FINE;

    if (amt <= BRACKET_CUTOFF_1)
        fine += amt * RATE_1;
    else
    {
          // Compute additional fine for the portion of amt in first bracket

        fine += BRACKET_CUTOFF_1 * RATE_1;

          // Determine rate for second bracket

        double rate_2 = RATE_2_NO_FAKE_ATH;
        if (fakeAth == "y")
            rate_2 = RATE_2_FAKE_ATH;

        if (amt <= BRACKET_CUTOFF_2)
        {
              // Add fine for remainder of amt (in 2nd bracket)

            fine += (amt - BRACKET_CUTOFF_1) * rate_2;
        }
        else
        {
              // Add fine for the portion of amt in 2nd bracket
              // and the remainder of amt (in 3rd bracket)

            fine += (BRACKET_CUTOFF_2 - BRACKET_CUTOFF_1) * rate_2 +
                    (amt - BRACKET_CUTOFF_2) * RATE_3;
        }   
    }

      // Print fine

    cout.setf(ios::fixed);
    cout.precision(1);
    cout << "---\nThe suggested fine for " << defendant << " is $" << fine
         << " thousand." << endl;
}
