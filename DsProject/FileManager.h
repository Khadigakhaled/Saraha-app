#pragma once
#include<vector>
#include "User.h"

class FileManager
{
public: 
		void readAllUsersFromFiles();
		void writeAllUsersToFiles();
		void readAllContactsFromFiles();
		void writeAllContactsToFiles();
		void readAllSentMessagesFromFiles();
		void writeAllSentMessagesToFiles();
public :
	void readDataFromFiles();
	void writeDataToFiles();
};

