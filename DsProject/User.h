#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include  <queue>
#include <string>
#include <utility>
#include "Message.h"
using namespace std;

class User
{
public:
	string ID, Username, Password;

	vector<User> contacts;
	stack<Message> Sent_msgs;
	stack<Message> rec_msgs;
	queue<string> favs;

	User(string id, string n, string p);
	User(string id, string n);
	User();
	void MainPage();

	void Add_user();

	void Send_msg();
	void Undo_msg();
	void Search_contact();
	void View_allconts();
	void Show_sent();
	void show_Allrec();

	void Add_favs();
	void Remove_favs();
	void View_favs();

};

