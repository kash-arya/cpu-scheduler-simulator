#include "process.h"
#include <iostream>
using namespace std;

int main() {
    Process P1(1,0,5,1),P2(2,1,6,2),P3(3,2,7,3);
    P1.print_data_of_process();
    P2.print_data_of_process();
    P3.print_data_of_process();
    return 0;
}
