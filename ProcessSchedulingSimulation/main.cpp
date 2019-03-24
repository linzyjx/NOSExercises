//
// Created by linzy on 2019/03/21.
//

/**

 5
 1 0 3
 2 4 6
 3 4 4
 4 6 5
 5 8 2

 */
#include <iostream>
#include "system.h"
#include <unistd.h>

using namespace std;

int main() {
    int n;
    cout << "Enter process num:";
    cin >> n;
    vector<inProcess> ps;
    cout << "Enter precesses:" << endl;
    while (n--) {
        inProcess i;
        cin >> i.pid >> i.arrTime >> i.sevTime;
        ps.push_back(i);
    }

    cout << endl << "insert done" << endl;
    cout << endl << "Choose a scheduling algorithm :" << endl;
    cout << "  1.FCFS" << endl << "  2.SJF" << endl << "  3.HRF" << endl << "  4.TimeSlice" << endl << "  0.exit"
         << endl << "?>";

    while (n != 0) {
        int ch = 0;
        cin >> ch;
        if (ch == 1) {
            FCFS tasks(ps);
            tasks.system(25);
            cout << "run done." << endl << endl;
            cout<<"FCFS"<<endl;
            tasks.printProcessList();
        } else if (ch == 2) {
            SJF tasks(ps);
            tasks.system(25);
            cout << "run done." << endl << endl;
            cout<<"SJF"<<endl;
            tasks.printProcessList();
        } else if (ch == 3) {
            HRF tasks(ps);
            tasks.system(25);
            cout << "run done." << endl << endl;
            cout<<"HRF"<<endl;
            tasks.printProcessList();
        } else if (ch == 4) {
            TimeSlice tasks(ps);
            tasks.system(30);
            cout << "run done." << endl << endl;
            cout<<"TimeSlice"<<endl;
            tasks.printProcessList();
        } else {
            break;
        }
        cout << endl << "?>";
    }
}