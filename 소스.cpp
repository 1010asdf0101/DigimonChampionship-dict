#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <locale>
#include <Windows.h>
using namespace std;

class status {
public:
	int hp, tp, size, atk, def, intel, agil;
	status() {
		hp = tp = size = atk = def = intel = agil = 0;
	}
	status(int h, int t, int s, int a, int d, int in, int ag) {
		hp = h;
		tp = t;
		size = s;
		atk = a;
		def = d;
		intel = in;
		agil = ag;
	}
};

class mons {
public:
	status stat;
	wstring name, level, type, attribute;
	bool operator<(const class mons& t) {
		if (name.compare(t.name) < 0) return true;
		return false;
	}
	bool operator==(const class mons& t) {
		if (name.compare(t.name) == 0) return true;
		return false;
	}
	mons() {
		name = level = type = attribute = L"";
		stat = status();
	}
	mons(wstring nm, wstring lev, wstring tp, wstring att) {
		name = nm;
		level = lev;
		type = tp;
		attribute = att;
		stat = status();
	}
	mons(wstring nm, wstring lev, wstring tp, wstring att, status st) {
		name = nm;
		level = lev;
		type = tp;
		stat = st;
		attribute = att;
	}
};

typedef struct _att {
	wstring att;
	int val;
} Attribute;

class evol {
public:
	wstring name;
	vector<Attribute> attribute;
	int penalty, battle, rate, egg;
	bool b_time;
	evol() {
		name = L"";
		b_time = false;
		penalty = battle = rate = egg = 0;
	}

	evol(wstring nm){
		name = nm;
		penalty = battle = rate = egg = 0;
		b_time = false;
	}	
	evol(wstring nm, bool t) : name(nm), b_time(t) {
		penalty = battle = rate =  egg = 0;
	}
	evol(wstring nm, int p) : name(nm), penalty(p){

		battle = rate = egg = 0;
		b_time = false;
	}
	evol(wstring nm, bool t, int p) : name(nm), b_time(t), penalty(p) {
		battle = rate =  egg = 0;
	}
	evol(wstring nm, int b, int br) : name(nm), battle(b), rate(br) {
		penalty =  egg = 0;
		b_time = false;
	}
	evol(wstring nm, int b, int br, int e) : name(nm), egg(e), battle(b), rate(br) {
		penalty =  0;
		b_time = false;
	}
	evol(wstring nm, wstring att, int am) : name(nm), b_time(false) {
		penalty = battle = rate = egg = 0;
		attribute.push_back({ att, am });
	}
	evol(wstring nm, int b, int br, wstring att, int am, int e) : name(nm), battle(b), rate(br), penalty(0), b_time(false), egg(e){
		attribute.push_back({ att, am });
	}
	evol(wstring nm, wstring att1, int am1, wstring att2, int am2) : name(nm), b_time(false){
		battle = rate = penalty = egg = 0;
		attribute.push_back({ att1, am1 });
		attribute.push_back({ att2, am2 });
	}
	evol(wstring nm, wstring att1, int am1, wstring att2, int am2, int b, int br) : name(nm), b_time(false), battle(b), rate(br) {
		penalty = egg = 0;
		attribute.push_back({ att1, am1 });
		attribute.push_back({ att2, am2 });
	}
};

class Dictionary {
public:
	map<wstring, mons> mp_mons;
	map<wstring, vector<evol> > mp_ev;
	void find_with_lev(wstring str) {
		for (map<wstring, mons>::iterator iter = mp_mons.begin(); iter != mp_mons.end();iter++) {
			if (iter->second.level.compare(str) == 0) {
				wcout << L"이름 : " << iter->second.name << endl;
				wcout << L"세대 : " << iter->second.level << endl;
				wcout << L"종족 : " << iter->second.type << L", 속성 : " << iter->second.attribute << endl;
				wcout << L"능력치 : " << L"ATK : " << iter->second.stat.atk << L" TP : " << iter->second.stat.tp 
					<< L" HP : " << iter->second.stat.hp << L" SIZE : " << iter->second.stat.size << endl;
				cout << endl;
			}
		}
		cout << "끝..." << endl << endl;
	}
	void find_with_name(wstring str) {
		map<wstring, mons>::iterator iter = mp_mons.find(str);
		if (iter != mp_mons.end()) {
			wchar_t cmd;
			wcout << L"\t이름 : " << iter->second.name << endl;
			wcout << L"\t세대 : " << iter->second.level << endl;
			wcout << L"\t종족 : " << iter->second.type << L", 속성 : " << iter->second.attribute << endl;
			wcout << L"\t능력치 : " << "ATK : " << iter->second.stat.atk << " / TP : " << iter->second.stat.tp
			 << " / HP : " << iter->second.stat.hp << " / SIZE : " << iter->second.stat.size << endl;
			wcout << L"\t추가적인 정보를 보려면 'X' 를 입력하세요. 그만 보려면 다른 문자를 입력하세요. : ";
			wcin >> cmd;
			if (cmd == 'X')
				cout << "\tDEF: " << iter->second.stat.def << " / INTEL : " << iter->second.stat.intel << " / AGIL : " << iter->second.stat.agil << endl;
		}
		else wcout << L"몬스터가 없습니다." << endl;
		cout << endl;
	}
	void show_mon(wstring str) {
		wstring lev_lst[6] ={L"유년기1", L"유년기2", L"성장기", L"성숙기", L"완전체", L"궁극체" };
		for (int i = 0; i < 6; ++i) 
			if (lev_lst[i].compare(str) == 0) {
				find_with_lev(str);
				return;
			}
		find_with_name(str);
	}
	void show_evol(wstring str) {
		map<wstring, vector<evol> >::iterator iter = mp_ev.find(str);
		map<wstring, mons>::iterator tmp = mp_mons.find(str);
		if (tmp != mp_mons.end() && tmp->second.level.compare(L"궁극체") == 0)
			wcout << L"궁극체는 더 이상 진화 할 수 없습니다." << endl;
		else if (iter != mp_ev.end()) {
			for (vector<evol>::iterator t = iter->second.begin(); t != iter->second.end(); t++) {
				wcout << L"\t이름 : " << t->name << endl;
				if (t->penalty) wcout << L"\t\t패널티 : " << t->penalty << L"회" << endl;
				if (t->b_time) wcout << L"\t\t시간진화" << endl;
				if (t->battle) wcout << L"\t\t" << L"배틀 : " << t->battle << L"회" << L", 승률 : " << t->rate << L"%" << endl;
				if (t->attribute.size() > 0) 
					for(vector<Attribute>::iterator it=t->attribute.begin(); it!=t->attribute.end(); it++)
						wcout << L"\t\t" << L"속성 : " << it->att << L", 값 : " << it->val << endl;
				if (t->egg) wcout << L"\t\t" << L"디지에그 : " << t->egg << L"회" << endl;
			}
		}
		else wcout << L"몬스터가 없습니다." << endl;
		wcout << endl;
	}
};

Dictionary Dic;

void init()
{
	wifstream file("database.txt");
	wstring n, l, t, att;
	int hp, tp, si, at, de, in, ag;
	wchar_t cmd;
	while (file) {
		file >> n >> l >> t >> att >> hp;
		if (hp == -1) {
			Dic.mp_mons.insert(make_pair(n, mons(n, l, t, att)));
		}
		else {
			file >> tp >> si >> at >> de >> in >> ag;
			Dic.mp_mons.insert(make_pair(n, mons(n, l, t, att, status(hp, tp, si, at, de, in, ag))));
		}
		file >> cmd;
		if (cmd == 'c') {
			pair< map<wstring, vector<evol> >::iterator, bool> ret = Dic.mp_ev.insert(make_pair(n, NULL));
			if (ret.second) ret.first->second = vector<evol>();
			do {
				int flag = 0, b, br, am, e=0, p, am2;
				wstring ev_n, option, att, att2;
				file >> ev_n >> option;
				b = count(option.begin(), option.end(), 'a');
				if (b > 0) {
					file >> att >> am;
					if (b == 2) {
						file >> att2 >> am2;
						flag += 32;
					}
					else flag += 2;
				}
				if (option.find('b') != string::npos) {
					file >> b >> br;
					flag += 1;
				}
				if (option.find('e') != string::npos) {
					file >> e;
					flag += 4;
				}
				if (option.find('p') != string::npos) {
					file >> p;
					flag += 16;
				}
				if (option.find('t') != string::npos) flag += 8;
				if (flag == 1) ret.first->second.push_back(evol(ev_n, b, br));
				else if (flag == 2) ret.first->second.push_back(evol(ev_n, att, am));
				else if (flag == 3) ret.first->second.push_back(evol(ev_n, b, br, att, am, 0));
				else if (flag == 4) ret.first->second.push_back(evol(ev_n, 0, 0, e));
				else if (flag == 5) ret.first->second.push_back(evol(ev_n, b, br, e));
				else if (flag == 7) ret.first->second.push_back(evol(ev_n, b, br, att, am, e));
				else if (flag == 8) ret.first->second.push_back(evol(ev_n, true));
				else if (flag == 16) ret.first->second.push_back(evol(ev_n, p));
				else if (flag == 24) ret.first->second.push_back(evol(ev_n, true, p));
				else if (flag == 32) ret.first->second.push_back(evol(ev_n, att, am, att2, am2));
				else if (flag == 33) ret.first->second.push_back(evol(ev_n, att, am, att2, am2, b, br));
				file >> cmd;
			} while (cmd == 'C');
		}
	}
	file.close();
}

int main()
{	
	locale::global(locale("ko_KR.UTF-8"));
	wcin.imbue(locale("kor"));
	init();
	while (1) {
		int cmd;
		wstring str;
		wcout << L"-1 : 프로그램 종료" << L",   0 : 몬스터 찾기" << L",   1 : 몬스터 진화 조건확인" << L",  2 : 화면 지우기\tcmd : ";
		cin >> cmd;
		if (cmd == -1) break;
		else if (cmd == 0) {
			wcout << L"세대 혹은 이름 입력 : ";
			wcin >> str;
			Dic.show_mon(str);
		}
		else if (cmd == 1) {
			wcout << L"이름 입력 : ";
			wcin >> str;
			Dic.show_evol(str);
		}
		else if (cmd == 2) system("cls");
	}
	return 0;
}