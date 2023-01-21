#include <iostream>
#include "radix_tree.h"
using namespace std;

int main(){
    RadixTree rt;
    rt.insert("water", "water");
    rt.insert("watch", "watch");
    rt.insert("waste", "waste");
    rt.insert("watermelon", "watermelon");
    rt.insert("wait", "wait");
    rt.insert("waiter", "waiter");
    rt.insert("slower", "slower");
    rt.insert("slow", "slow");
    rt.view();
    
    cout << endl;
    cout << rt.get("water") << endl;
    cout << rt.get("slower") << endl;
    cout << rt.get("slow") << endl;
    cout << rt.get("watermelon") << endl;
    return 0;
}