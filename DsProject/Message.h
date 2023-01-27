#pragma once
#include <iostream>
using namespace std;
class Message
{
	public:
		string senderID;
		string receiverID;
		string content;
		int count=0;
		int content_count = 0;
		//Date sentDate;
		Message();
		Message(string from, string to, string c);
		string getContent();
		string getSenderID();
		string getReceiverID();
		void displayMessage();
};

