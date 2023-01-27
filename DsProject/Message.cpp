#include "Message.h"
using namespace std;
Message::Message(string from, string to, string c)
{
	senderID = from;
	receiverID = to;
	content = c;
	count++;
}
Message::Message(){}
string Message::getContent()
{
	return content;
}
string Message::getReceiverID()
{
	return receiverID;
}
string Message::getSenderID()
{
	return senderID;
}
void Message::displayMessage() {
	cout << "Sender ID: " << senderID << endl;
	cout << "Receiver ID: " << receiverID<< endl;
	cout << "Message content: " << content<< endl;
}