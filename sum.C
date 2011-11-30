#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void sum() {
  int max=0;
  cout << "Type in upper limit ";
  cin >> max;

  int sum = 0;
  for ( int i = 0; i <= max; ++i) {
    sum += i;
  }

  cout << "The sum of 1.." << max << " is " << sum << endl;
}
