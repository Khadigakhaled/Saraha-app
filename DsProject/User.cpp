#include "User.h"
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include <string>
#include<string.h>
#include "GlobalVariables.h"
#include "FileManager.h"

using namespace std;

User::User(string id, string n, string p)
{
	ID = id;
	Username = n;
	Password = p;
}

User::User(string id, string n)
{
	ID = id;
	Username = n;
}
User::User()
{
}

void User::MainPage()
{
	char choice;
	do
	{

		int x;
		cout << " ***Welcome to Saraha, please choose what operation you want: ***" << endl;
		cout << "                                                                                     " << endl;
		cout << "1- Add a user to your contacts. " << endl; //done
		cout << "2- Send a message to a contact. " << endl; //done
		cout << "3- Undo the last sent message. " << endl; //done
		cout << "4- Search a contact. " << endl; //done
		cout << "5- View all contacts of a specific user." << endl; //done
		cout << "6- View all the sent messages. " << endl;  //done
		cout << "7- View all the received messages from specific contact. " << endl; //done
		cout << "8- Put a message in favorites. " << endl; 
		cout << "9- Remove the oldest message from favorites." << endl; //done
		cout << "10- View all favorites messages." << endl; //done
		cout << "11- Log Out." << endl;
		cin >> x;
		cout << "You chosed option: " << x << " " << endl;
		cout << "                                                                                         " << endl;
		if (x == 1)
			Add_user();
		else if (x == 2)
			Send_msg();
		else if (x == 3)
			Undo_msg();
		else if (x == 4)
			Search_contact();
		else if (x == 5)
			View_allconts();
		else if (x == 6)
			Show_sent();
		else if (x == 7)
			show_Allrec();
		else if (x == 8)
			Add_favs();
		else if (x == 9)
			Remove_favs();
		else if (x == 10)
			View_favs();
		else if (x == 11)
			break;
		cout << "Do you want to do another operation? " << endl;
		cin >> choice;
	} while (choice == 'y');
}

void User::Add_user()
{
	string c_name, c_ID;
	char choice;
	
	FileManager fileManager;
	
	do
	{
		cout << "Enter contact's ID. " << endl;
		cin >> c_ID;
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].ID == c_ID)
			{
				cout << "User Already exists in contacts! "<<endl;
				return;
			}
		}

		if (c_ID == ID)
		{
			cout << "You can't add yourself, Please add a proper contact. " << endl;
			Add_user();
		}
		else
		{
			for (int i = 0; i < GlobalVariables::users.size(); i++)
			{
				if (GlobalVariables::users[i].ID == c_ID)
				{
					cout << "Added successfully! " << endl;
					contacts.push_back(GlobalVariables::users[i]);
					fileManager.writeAllContactsToFiles();
					break;
				}
			}
		}
		cout << "Do you want to add another user? " << endl;
		cin >> choice;

	} while (choice == 'y');

}


void User::Send_msg()
{
	//FileManager fm;
	char choice;
	do
	{
		string ContactID, sent_msg;
		cout << "Enter contact's ID: \n";
		cin >> ContactID;
		cout << "Enter your message: \n";
		cin.ignore();
		getline(cin, sent_msg);
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].ID == ContactID)
			{

				for (int j = 0; j < GlobalVariables::users.size(); j++)
				{
					if (GlobalVariables::users[j].ID == ContactID)
					{
						
						Message newMessage(ID, GlobalVariables::users[j].ID, sent_msg);

						Sent_msgs.push(newMessage);
						GlobalVariables::users[j].rec_msgs.push(newMessage);
						//fm.writeAllSentMessagesToFiles();
					}
				}
			}
		}
		cout << "Do you want to send another message? " << endl;
		cin >> choice;
	} while (choice == 'y');
}




void User::Undo_msg()
{
	char choice;
	do
	{
		if (!Sent_msgs.empty())
		{
			cout << "You'll delete : " << Sent_msgs.top().getContent() << endl;
			Sent_msgs.pop();
		}
		else
		{
			cout << "There are no sent messages! " << endl;
			break;
		}

		cout << "Do you want to delete another message? " << endl;
		cin >> choice;

	} while (choice == 'y');
}

void User::Search_contact()
{
	bool found = false;
	string contactID;
	char choice='y';

	if (contacts.empty())
	{
		cout << "There are no contacts, please add a contact first. " << endl;
	}

	while(contacts.empty()!=true  && choice=='y')
	{
		cout << "Enter contact's ID: \n ";
		cin >> contactID;
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].ID == contactID)
			{
				found = true;
				break;
			}
			else
			{
				found = false;
			}
		}

		if (found == true)
		{
			cout << "Found" << endl;
		}
		else
			cout << "Not Found" << endl;

		cout << "Do you want to search another contact? " << endl;
		cin >> choice;

	} 
	 
}

void User::show_Allrec()
{
	vector < Message> rec_msgs_temp;
	stack <Message>tempStack=rec_msgs;

	while (!tempStack.empty())
	{
		rec_msgs_temp.push_back(tempStack.top());
		tempStack.pop();
	}

	string id;
	char choice;
	bool found=false;

	do
	{
		found = false;
		cout << "Enter sender Id" << endl;
		cin >> id;

		for (int i = 0; i < rec_msgs_temp.size(); i++) {
			if (rec_msgs_temp[i].senderID == id)
			{
				cout << "The messeges are: " << endl;
				rec_msgs_temp[i].displayMessage();
				found = true;
			}
		}
		if (found == false)
		{
			cout << "You don't have any messages from this user" << endl;
		}
		cout << "Do you want to see another received messages from another user? " << endl;
		cin >> choice;

	} while (choice == 'y'|| choice == 'Y');
}




void User::Show_sent()
{
	int count = 1;

	if (Sent_msgs.empty())
	{
		cout << "There are no sent messages yet, please send ones first. " << endl;
	}

	else
	{
		stack <Message> Sent_msgs_tmp = Sent_msgs;
		cout << "Your sent messages are: " << endl;
		while (!Sent_msgs.empty()) {
			cout << count << "- " << Sent_msgs.top().getContent() << endl;
			Sent_msgs.pop();
			count++;
		}

		Sent_msgs = Sent_msgs_tmp;
	}
}

void User::View_allconts()
{
	string u_ID;
	string U_name;
	char choice;
	bool found = false;

	do
	{
		cout << "Please enter ID of user you want to get their contact : " << endl;
		cin >> u_ID;
		for (int i = 0; i < GlobalVariables::users.size(); i++)
		{
			if (GlobalVariables::users[i].ID == u_ID)
			{

				if (GlobalVariables::users[i].contacts.size() == 0)
				{
					cout << "User doesn't have contacts! " << endl;
					break;
				}
				else
				{
					for (int j = 0; j < GlobalVariables::users[i].contacts.size(); j++)
					{
						cout << j + 1 << "- ID: " << GlobalVariables::users[i].contacts[j].ID << endl;
						cout << j + 1 << "- Username: " << GlobalVariables::users[i].contacts[j].Username << endl;
					}
				}
			}
		}

		cout << "Do you want to search for another user's contacts? " << endl;
		cin >> choice;

	} while (choice == 'y');
}

void User::Add_favs()
{

	if (rec_msgs.empty())
	{
		cout << "You have no messages to put in favourites! " << endl;
	}
	else
	{
		string senderID;
		cout << "Enter ID of sender: " << endl;
		cin >> senderID;
		vector < Message> senderMessages;

		stack <Message> temp = rec_msgs;

		while (!temp.empty())
		{
			if (temp.top().senderID == senderID)
			{
				senderMessages.push_back(temp.top());

			}
			temp.pop();
		}

		cout << "Sender Messages:" << endl;
		for (int i = 0; i < senderMessages.size(); i++)
		{
			cout << i + 1 << "-Message content:" << senderMessages[i].content << endl;
		}
		cout << "Enter the message number:";

		int selectedMessageNumber;
		cin >> selectedMessageNumber;
		selectedMessageNumber--;

		if (selectedMessageNumber >= 0 && selectedMessageNumber < senderMessages.size())
			favs.push(senderMessages[selectedMessageNumber].content);
		else
			cout << "Wrong message number. Please try again!!";
	}
}

void User::Remove_favs()
{

	if (favs.empty())
	{
		cout << "You have no favourite messages to delete! " << endl;
	}
	else
	{
		cout << "You'll delete : " << favs.front() << endl;
		favs.pop();
	}
}

void User::View_favs()
{
	queue<string> favs_tmp = favs;
	if (favs.empty())
	{
		cout << "You have no favourite messages to view! " << endl;
	}
	else
	{
		while (!favs_tmp.empty())
		{
			cout << "Your favourite messages are: \n";
			cout << favs_tmp.front() << endl;
			favs_tmp.pop();
		}
	}
}
