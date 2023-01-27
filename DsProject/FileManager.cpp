#include "FileManager.h"
#include <iostream>
#include <fstream>
#include "GlobalVariables.h"
#include "User.h"
#include <sstream>
using namespace std;

void FileManager::readAllContactsFromFiles()

{
	ifstream contactsFile("Contacts.txt");
	int numberOfcontacts;
	int numberOfUsers;
	string contactID;
	string temp;
	getline(contactsFile, temp);

	stringstream ss;
	ss << temp;
	ss >> numberOfUsers;
	ss.clear();

	for (int i = 0; i < numberOfUsers; i++)
	{
		getline(contactsFile, temp);

		ss << temp;
		ss >> numberOfcontacts;
		ss.clear();

		for (int j = 0; j < numberOfcontacts; j++)
		{
			
			if (j == numberOfcontacts - 1)
				getline(contactsFile, contactID);
			else
				getline(contactsFile, contactID ,',');

			for ( int k = 0; k < GlobalVariables::users.size(); k++)
			{
				if ( GlobalVariables::users[k].ID == contactID )
				{
					GlobalVariables::users[i].contacts.push_back(GlobalVariables::users[k]);
				}
			}
		}
	}


	contactsFile.close();
}

void FileManager::readAllUsersFromFiles() {
	ifstream usersFile("Users.txt");

	int numberOfUsers;
	string temp;
	getline(usersFile, temp);

	stringstream ss;
	 ss<<temp;
	 ss >> numberOfUsers;
	 ss.clear();

	for (int i = 0; i < numberOfUsers; i++)
	{
		User newUser;

		getline(usersFile, newUser.ID, ',');
		getline(usersFile, newUser.Username, ',');
		getline(usersFile, newUser.Password);


		GlobalVariables::users.push_back(newUser);
	}


	usersFile.close();
}

void FileManager::readDataFromFiles() {
	readAllUsersFromFiles();
	readAllContactsFromFiles();
	//readAllSentMessagesFromFiles();
}
void FileManager::writeAllUsersToFiles() {
	fstream usersFile("Users.txt",ios_base::out | ios_base::trunc);

	usersFile << GlobalVariables::users.size()<<endl;

	for (int i = 0; i < GlobalVariables::users.size(); i++)
	{
		usersFile << GlobalVariables::users[i].ID << ',';
		usersFile << GlobalVariables::users[i].Username << ',';
		usersFile << GlobalVariables::users[i].Password << '\n';
	}
	usersFile.close();
}



void FileManager::writeAllContactsToFiles()
{
	fstream contactsFile("Contacts.txt", ios_base::out | ios_base::trunc);

	contactsFile << GlobalVariables::users.size() << '\n';
	for (int j = 0; j < GlobalVariables::users.size(); j++)
	{
		contactsFile << GlobalVariables::users[j].contacts.size()<<'\n';
		for (int i = 0; i < GlobalVariables::users[j].contacts.size(); i++)
		{
			contactsFile << GlobalVariables::users[j].contacts[i].ID ;
			if (i != GlobalVariables::users[j].contacts.size() - 1)
				contactsFile << ',';
			else
				contactsFile << '\n';
		}

	}
	contactsFile.close();
}

void FileManager::writeDataToFiles() {
	writeAllUsersToFiles();
	writeAllContactsToFiles();
	//writeAllSentMessagesToFiles();
}

void FileManager::readAllSentMessagesFromFiles()
{
	ifstream SentFile("SentMessages.txt");
	int numberOfSentMsgs;
	int numberOfUsers;
	string SentMsg;
	string temp;
	getline(SentFile, temp);

	stringstream ss;
	ss << temp;
	ss >> numberOfUsers;
	ss.clear();

	for (int i = 0; i < numberOfUsers; i++)
	{
		getline(SentFile, temp);

		ss << temp;
		ss >> numberOfSentMsgs;
		ss.clear();

		for (int j = 0; j < numberOfSentMsgs; j++)
		{

			if (j == numberOfSentMsgs - 1)
				getline(SentFile, SentMsg);
			else
				getline(SentFile, SentMsg, ',');

			for (int k = 0; k < GlobalVariables::users.size(); k++)
			{
				for (int l = 0; l < GlobalVariables::users[k].Sent_msgs.size(); l++)
				{
					if (GlobalVariables::users[k].Sent_msgs.top().content == SentMsg)
					{
						Message newMessage;
						newMessage.content = GlobalVariables::users[k].Sent_msgs.top().content;
						newMessage.senderID = GlobalVariables::users[k].ID;
						GlobalVariables::users[i].Sent_msgs.push(newMessage);
					}
				}
			}
		}
	}


	SentFile.close();
}

void FileManager::writeAllSentMessagesToFiles()
{
	fstream SentFile("SentMessages.txt", ios_base::out | ios_base::trunc);
	SentFile << GlobalVariables::users.size() << '\n';
	for (int j = 0; j < GlobalVariables::users.size(); j++)
	{
		SentFile << GlobalVariables::users[j].Sent_msgs.size() << '\n';
		for (int i = 0; i < GlobalVariables::users[j].Sent_msgs.size(); i++)
		{
			SentFile << GlobalVariables::users[j].Sent_msgs.top().content;
			if (i != GlobalVariables::users[j].Sent_msgs.size() - 1)
				SentFile << ',';
			else
				SentFile << '\n';
		}
	}

	SentFile.close();
}