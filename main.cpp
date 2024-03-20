#include <iostream>
#include <algorithm>

#include "secret.h"

using namespace std;


Secret min(Secret x, Secret y) {
    Secret condition = x < y;
    return (x * condition + !condition * y);
}

Secret max(Secret x, Secret y) {
    Secret condition = x > y;
    return x * condition + !condition * y;
}


void swap_if(Secret x, Secret y, Secret z) {
    //    Clue 3 : Construct swap_if(x, y, z) taking 
    //    3 secret arguments and swaps x and y if z is 1 
    //    when decrypted; and does not swap if z is 0 when decrypted.Assume z corresponds either to 0 or 1.
    Secret temporary = x;
    x = y * z + !z * x;
    y = x * z + !z * y;
}

void secret_sort(std::vector<Secret>& arr) {
   
// ...
    //Clues
    // Clue 1: Construct a function min(x, y) that takes two secret objects
    // and outputs the one corresponding to the minimal value when decrypted.
    //    Clue 2 : Construct max(x, y).
    //    Note : The sorting algorithm can also be implemented
    //    also without creating min() and max() functions separately, but they can be
    //    useful to implement separately to get some practice with data oblivious programming 
    //    before integrating them in the sorting algorithm.
    //    Clue 3 : Construct swap_if(x, y, z) taking 3 secret arguments and swaps x and y if z is 1 
    //    when decrypted; and does not swap if z is 0 when decrypted.Assume z corresponds either to 0 or 1.
   
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            Secret condition = arr[j] < arr[j + 1]; 
            swap_if(arr[j], arr[j + 1], condition); 
        }
    }
}

void shuffle(std::vector<Secret> & arr)
{
    int n = (int)arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if ( arr[j + 1] ^ arr[j] )
                std::swap(arr[j], arr[j + 1] );
}

void test()
{
    auto phrase = encrypt("Some phrase");
    cout << decrypt(phrase) << '\n';
    shuffle(phrase);
    cout << decrypt(phrase) << '\n';
    secret_sort(phrase);
    cout << decrypt(phrase) << '\n';
}
/* this function outputs:
Some phrase
***********
Some phrase
*/


int main()
{
    std::vector<uint> shuffled = { 285518085, 352427273, 687915277, 772094988, 973324812,
                               1023617548, 1023617548, 1375820812, 1996510979, 2046984461, 2164405007,
                               2181047308, 2248146956, 3322173964, 3506702083, 3657463820, 3657463820,
                               3691114251, 3691134731, 3691134731, 3691330311, 3808498700, 3808498700,
                               3892499980, 3926193676, 4060310279
                             };

    auto secret = import_vec(shuffled);

    secret_sort(secret);

    cout << decrypt(secret) << '\n';
}
