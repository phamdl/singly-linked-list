
#include <iostream>

#include "SinglyLinkedList.h"

using namespace std;

const int N = 2*1000*1000;

int main(int argc, char* argv[]) {

  SLList<int> list; // empty

  // build up to 1, 2, 0, 4
  list.AddFront(2);
  list.AddBack(0);
  list.AddFront(1);
  list.AddBack(4);

  // Add in the middle
  list.Add(2, 9);

  list.AddFront(-8);

  for (int i = 0; i < list.Size(); i++) {
    cout << "a.Get(i) is " << list.Get(i) << endl;
  }

  // list has -8, 1, 2, 0, 4, 9
  cout << "positives is " << list.CountPositive() << endl;

  // add a lot of elements, confirm this is O(n) not O(n^2)
  cout << "add-to-back test...";
  SLList<float> b;
  for (int i = 0; i < N; i++) {
    b.AddBack(0.0); // O(1)
  } // O(n) for the whole loop
  cout << "done" << endl;

  return 0;
}
