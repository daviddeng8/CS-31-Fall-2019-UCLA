1. 
endlendl
grendel

2. 
It prints a triangle. [The problem said to write a brief, simple English sentence; we did not want a paragraph-length blow-by-blow account of what the program was doing.]

3. 
#include <iostream>
using namespace std;

int main()
{
    int side;

    cout << "Enter a number: ";
    cin >> side;

    for (int i = 0; i < side; i++)
    {
	int j = i;
	while (j >= 0)
	{
	    cout << '#';
	    j--;
	}
	cout << "\n";
    }
}

4.
#include <iostream>
using namespace std;

int main()
{
    int side;

    cout << "Enter a number: ";
    cin >> side;

    if (side > 0)  // No output whatsoever if side is nonpositive
    {
	int i = 0;
	do
	{
	    int j = i;
	    while (j >= 0)
	    {
		cout << '#';
		j--;
	    }
	    cout << "\n";
	    i++;
	} while (i < side);
    }
}

5.
switch (codeSection)
{
  case 281:
    cout << "bigamy";
    break;

  case 321:
  case 322:
    cout << "selling illegal lottery tickets";
    break;

  case 383:
    cout << "selling rancid butter";
    break;

  case 598:
    cout << "injuring a bird in a public cemetery";
    break;

  default:
    cout << "some other crime";
}
