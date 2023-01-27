#include <iostream>
#include "User.h"
#include<string.h>
#include<stack>
#include<queue>
#include<vector>
#include "GlobalVariables.h"
#include "FileManager.h"
using namespace std;

void reg_login()
{

    bool check = false;
    char choice;
    do
    {
        bool found = false;
        int x;
        string n, p;
        string y, z, i;
        cout << "Welcome to Saraha, Enter 1 to Log in or 2 to Sign up :" << endl;
        cin >> x;
        if (x == 1)
        {
            cout << "Username: ";
            cin >> n;
            for (int i = 0; i < GlobalVariables::users.size(); i++)
            {
                if (GlobalVariables::users[i].Username == n)
                {
                    cout << "Password: ";
                    cin >> p;
                    if (GlobalVariables::users[i].Password == p)
                    {
                        cout << " ****************Login Successful!****************** " << endl;
                        found = true;
                        GlobalVariables::users[i].MainPage();
                    }
                }
            }
            if (found == false)
            {
                cout << "Wrong username or password, please retry! " << endl;
                reg_login();
            }
        }

        else if (x == 2)
        {
            cout << "Username: ";
            cin >> y;
            cout << "Password: ";
            cin >> z;
            cout << "ID: ";
            cin >> i;

            for ( int j = 0; j < GlobalVariables::users.size(); j++)
            {
                if ( GlobalVariables::users[j].ID == i)
                {
                    check = true;
                    cout << "User already exists"<<endl;
                    break;
                }
            }

            if (check == false)
            {
                User us(i, y, z);
                GlobalVariables::users.push_back(us);
                FileManager fileManager;
                fileManager.writeDataToFiles();
                cout << "User added, please choose to log in to enter! " << endl;
                reg_login();
            }
            else
                reg_login();
        }

        cout << "Do you want to log out? " << endl;
        cin >> choice;
    } while (choice == 'y');
}


int main()
{
    FileManager fileManager;
    fileManager.readDataFromFiles();

    reg_login();

    return 0;
}
