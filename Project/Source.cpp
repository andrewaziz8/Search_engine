#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<fstream>
using namespace std;

void lowercase(string& word) {
	for (int i = 0; i < word.size(); i++) {
		if (word[i] >= 'A' && word[i] <= 'Z')
			word[i] += 32;
	}
}

bool isquotations(string key) {
	if (key[0] == '"' && key[key.length() - 1] == '"')
		return true;
	else
		return false;
}
void quot(string& key) {
	key.erase(key.begin());
	key.erase(key.end() - 1);
}
void ForQuotations(multimap<string, string> keyword, unordered_map<string, double> score, string text, vector<string>& res, unordered_map<string, double>& impres) {
	quot(text);
	auto it = keyword.find(text);
	if (it != keyword.end()) {
		auto result = keyword.equal_range(text);
		int count = 0;
		cout << "\nSearch results:" << endl;
		map<double, string> order;
		for (auto i = result.first; i != result.second; i++) {
			order[score[i->second]] = i->second;
		}
		for (auto it = order.rbegin(); it != order.rend(); it++) {
			++impres[it->second];
			cout << ++count << ". " << it->second << endl;
			res.push_back(it->second);
		}
	}
	else
		cout << "\nWebpage is not found" << endl;
}

bool isAND(string key,int& start,int& end) {
	string word = "and";
	int c = 0;
	for (int i = 1; i < key.size(); i++) {
		c = 0;
		if (key[i] != ' ' && key[i - 1] == ' ') {
			start = i;
			for (int j = 0; j < 3; j++) {
				if (word[j] == key[i + j])
					++c;
				else
					break;
			}
		}
		if (c == 3 && key[i + 3] == ' ') {
			end = i + 2;
			return true;
		}
	}
	start = 0;
	end = 0;
	return false;
}
void keyand(string& key,string& k1,string& k2,int start,int end) {
	for (int i = 0; i < start-1; i++) 
		k1.push_back(key[i]);

	for (int i = end + 2; i < key.size(); i++)
		k2.push_back(key[i]);
}
void ForAND(multimap<string, string> keyword, unordered_map<string, double> score, string text, vector<string>& res, int s, int e, unordered_map<string, double>& impres) {
	string s1, s2;
	keyand(text, s1, s2, s, e);
	auto it1 = keyword.find(s1);
	auto it2 = keyword.find(s2);
	if (it1 != keyword.end() && it2 != keyword.end()) {
		auto result1 = keyword.equal_range(s1);
		auto result2 = keyword.equal_range(s2);
		int count = 0;
		cout << "\nSearch results:" << endl;
		map<double, string> order, order1;
		for (auto i = result1.first; i != result1.second; i++)
			order1[score[i->second]] = i->second;

		for (auto j = result2.first; j != result2.second; j++) {
			if (order1[score[j->second]] == j->second)
				order[score[j->second]] = j->second;
		}

		for (auto it = order.rbegin(); it != order.rend(); it++) {
			++impres[it->second];
			cout << ++count << ". " << it->second << endl;
			res.push_back(it->second);
		}
		if (res.empty())
			cout << "\nWebpage is not found" << endl;
	}
	else
		cout << "\nWebpage is not found" << endl;
}

bool isOR(string key,int& start,int& end) {
	string word = "or";
	int c = 0;
	for (int i = 1; i < key.size(); i++) {
		c = 0;
		if (key[i] != ' ' && key[i - 1] == ' ') {
			start = i;
			for (int j = 0; j < 2; j++) {
				if (word[j] == key[i + j])
					++c;
				else
					break;
			}
		}
		if (c == 2 && key[i + 2] == ' ') {
			end = i + 1;
			return true;
		}
	}
	start = 0;
	end = 0;
	return false;
}
void keyor(string& key, string& k1, string& k2, int start, int end) {
	for (int i = 0; i < start - 1; i++)
		k1.push_back(key[i]);

	for (int i = end + 2; i < key.size(); i++)
		k2.push_back(key[i]);
}
void ForOR(multimap<string, string> keyword, unordered_map<string, double> score, string text, vector<string>& res, int s, int e, unordered_map<string, double>& impres) {
	string s1, s2;
	keyor(text, s1, s2, s, e);
	auto it1 = keyword.find(s1);
	auto it2 = keyword.find(s2);
	if (it1 != keyword.end() || it2 != keyword.end()) {
		auto result1 = keyword.equal_range(s1);
		auto result2 = keyword.equal_range(s2);
		int count = 0;
		cout << "\nSearch results:" << endl;
		map<double, string> order;
		for (auto i = result1.first; i != result1.second; i++)
			order[score[i->second]] = i->second;

		for (auto j = result2.first; j != result2.second; j++) {
			order[score[j->second]] = j->second;
		}

		for (auto it = order.rbegin(); it != order.rend(); it++) {
			++impres[it->second];
			cout << ++count << ". " << it->second << endl;
			res.push_back(it->second);
		}
	}
	else
		cout << "\nWebpage is not found" << endl;
}

void nothing(string key, string& k1,string& k2) {
	int start = 0;
	for (int i = 0; i < key.size() - 1; i++) {
		if (key[i] != ' ' && key[i + 1] == ' ') {
			start = i + 1;
			break;
		}
	}
	for (int i = 0; i < start; i++)
		k1.push_back(key[i]);
	for (int i = start + 1; i < key.size(); i++)
		k2.push_back(key[i]);
}
void ForNothing(multimap<string, string> keyword, unordered_map<string, double> score, string text, vector<string>& res,unordered_map<string,double>& impres) {
	string s1, s2;
	nothing(text, s1, s2);
	auto it1 = keyword.find(s1);
	auto it2 = keyword.find(s2);
	if (it1 != keyword.end() || it2 != keyword.end()) {
		auto result1 = keyword.equal_range(s1);
		auto result2 = keyword.equal_range(s2);
		int count = 0;
		cout << "\nSearch results:" << endl;
		map<double, string> order;
		for (auto i = result1.first; i != result1.second; i++)
			order[score[i->second]] = i->second;

		for (auto j = result2.first; j != result2.second; j++) {
			order[score[j->second]] = j->second;
		}

		for (auto it = order.rbegin(); it != order.rend(); it++) {
			++impres[it->second];
			cout << ++count << ". " << it->second << endl;
			res.push_back(it->second);
		}
	}
	else
		cout << "\nWebpage is not found" << endl;
}

void pagerank(unordered_map<string, double>& PRnorm, multimap<string, string> WepagesPointingTo, unordered_map<string, double> links) {
	for (int i = 0; i < 100; i++) {
		for (auto iter = PRnorm.begin(); iter != PRnorm.end(); iter++) {
			auto pointing = WepagesPointingTo.equal_range(iter->first);
			double sum = 0;
			for (auto x = pointing.first; x != pointing.second; x++) {
				sum += PRnorm[x->second] / links[x->second];
			}
			PRnorm[iter->first] = (0.15 / 30.0) + 0.85 * sum;
		}
	}
}
void ctr(unordered_map<string, double>& CTR, unordered_map<string, double> impres, unordered_map<string, double> click) {
	for (auto it = impres.begin(); it != impres.end(); it++)
		CTR[it->first] = (click[it->first] / it->second);
}
void SCORE(unordered_map<string, double>& score, unordered_map<string, double> CTR, unordered_map<string, double> PRnorm, unordered_map<string, double> impres) {
	for (auto it = CTR.begin(); it != CTR.end(); it++) {
		double num = (0.1 * impres[it->first]) / (1 + 0.1 * impres[it->first]);
		score[it->first] = 0.4 * PRnorm[it->first] + ((1 - num) * PRnorm[it->first] + num * it->second) * 0.4;
	}
}
void update(unordered_map<string,double> impres, unordered_map<string, double> click) {
	ofstream outfile;
	outfile.open("Updated number file.csv");
	for (auto it = impres.begin(); it != impres.end(); it++)
		outfile << it->first << ',' << it->second << ',' << click[it->first] << '\n';
	outfile.close();
}
int main() {

	ifstream infile;
	infile.open("Keyword File.csv");
	string first, second, third, four, five, six;
	multimap<string, string> keyword;
	unordered_map<string, double> PRnorm;
	while (getline(infile, first, ',')) {
		PRnorm[first] = 1.0 / 30.0;
		getline(infile, second, ',');
		keyword.insert({ second,first });

		getline(infile, third, ',');
		keyword.insert({ third,first });

		getline(infile, four, ',');
		keyword.insert({ four,first });

		getline(infile, five, ',');
		keyword.insert({ five,first });

		getline(infile, six, '\n');
		keyword.insert({ six,first });
	}
	infile.close();
	

	ifstream infile2;
	infile2.open("Web graph file.csv");
	unordered_map<string, double> links;
	multimap<string, string> WepagesPointingTo;
	string name, name2;
	while (getline(infile2, name, ',')) {
		++links[name];
		getline(infile2, name2, '\n');
		WepagesPointingTo.insert({ name2,name });
	}
	infile2.close();
	pagerank(PRnorm, WepagesPointingTo, links);

	ifstream infile3;
	infile3.open("Updated number file.csv");
	unordered_map<string, double> impres, click;
	string nameweb;
	double impressions = 0, cli = 0;
	if (infile3.is_open()) {
		while (getline(infile3, nameweb, ',')) {
			infile3 >> impressions;
			impres[nameweb] = impressions;
			infile3.ignore(1, ',');
			infile3 >> cli;
			click[nameweb] = cli;
			infile3.ignore(1, '\n');
		}
		infile3.close();
	}
	else {
		infile3.open("Number of impressions file.csv");
		while (getline(infile3, nameweb, ',')) {
			infile3 >> impressions;
			impres[nameweb] = impressions;
			click[nameweb] = 0;
			infile3.ignore(1, '\n');  
		}
		infile3.close();
	}
	unordered_map<string, double> CTR;
	unordered_map<string, double> score;
	
	cout << "Welcome!" << endl;
	cout << "What would you like to do?" << endl;
	cout << "1. New search" << endl << "2. Exit" << endl << endl;
	cout << "Type in your choice: ";
	int num = 0, num2 = 0, num3 = 1, webnum = 0;
	string text;
	vector<string> res;
	cin >> num;
	while (num > 2 || num < 1) {
		cout << "Please enter 1 or 2: ";
		cin >> num;
	}
	if (num == 2) {
		update(impres, click);
		cout << "\nGoodBye! Have a good day" << endl;
		return 0;
	}
	while (num == 1 || num2 == 2 || num3 == 2) {
		ctr(CTR, impres, click);
		SCORE(score, CTR, PRnorm, impres);
		/*for (auto it = score.begin(); it != score.end(); it++)
			cout << it->first << "  " << it->second << endl;*/
		num3 = 1;
		res.clear();
		cout << "\nEnter your keywords: ";
		cin.ignore(1, '\n');
		getline(cin, text);
		lowercase(text);
		int start = 0, end = 0;
		if (isquotations(text)) {
			ForQuotations(keyword, score, text, res, impres);
		}
		else if (isAND(text, start, end)) {
			ForAND(keyword, score, text, res, start, end, impres);
		}
		else if (isOR(text, start, end)) {
			ForOR(keyword, score, text, res, start, end, impres);
		}
		else
			ForNothing(keyword, score, text, res, impres);
		cout << "\nWould you like to" << endl;
		cout << "1. Choose a webpage to open (if found)" << endl;
		cout << "2. New search" << endl;
		cout << "3. Exit" << endl;
		cout << "\nType in your choice: ";
		cin >> num2;
		while (num2 < 1 || num2>3) {
			cout << "PLease enter 1 or 2 or 3: ";
			cin >> num2;
		}
		if (num2 == 3) {
			update(impres, click);
			cout << "\nGoodBye! Have a good day" << endl;
			return 0;
		}
		if (num2 == 2)
			continue;
		while (num3 == 1) {
			if (num2 == 1 && !res.empty()) {
				cout << "\nType the number of the webpage that you want to open: ";
				cin >> webnum;
				if (webnum > 0 && webnum <= res.size()) {
					cout << "\nYou're now viewing " << res[webnum - 1] << "." << endl;
					++click[res[webnum - 1]];
				}
				else
					cout << "\nNo webpage has this number" << endl;
			}
			else {
				int count = 0;
				if (res.empty())
					cout << "\nWbpage is not found" << endl;
				else {
					cout << "\nSearch results:" << endl;
					for (int x = 0; x < res.size(); x++)
						cout << ++count << ". " << res[x] << endl;
					cout << "\nType the number of the webpage that you want to open: ";
					cin >> webnum;
					if (webnum > 0 && webnum <= res.size()) {
						cout << "\nYou're now viewing " << res[webnum - 1] << "." << endl;
						++click[res[webnum - 1]];
					}
					else
						cout << "\nNo webpage has this number" << endl;
				}
			}
			cout << "Would you like to " << endl;
			cout << "1. Back to search results" << endl;
			cout << "2. New search" << endl;
			cout << "3. Exit" << endl;
			cout << "\nType in your choice: ";
			cin >> num3;
			while (num3 < 1 || num3>3) {
				cout << "Please enter 1 or 2 or 3: ";
				cin >> num3;
			}
			if (num3 == 3) {
				update(impres, click);
				cout << "\nGoodBye! Have a good day" << endl;
				return 0;
			}
			num2 = 0;
		}
	}
	return 0;
}