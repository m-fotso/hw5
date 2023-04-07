
#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateSetCombo(std::string str, size_t l, size_t r, std::set<std::string> dict, int incnt, std::vector<char> vin, std::set<std::string>& test, std::set<std::string>& combo, std::string f, size_t inNum);
void testCombo(size_t size, std::string s, std::set<std::string> dict, int incnt, std::vector<char> vin, std::set<std::string>& temp, std::string f);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
	std::vector<char> v(in.begin(), in.end());
	std::vector<char> vin = v;
	int ji = 0;
	std::set<std::string> comb;
	std::vector<char> vfloat(floating.begin(), floating.end());
	
	size_t ic = 0;
	size_t fcount = 0;
	
	for(size_t i=0; i<v.size(); i++) {
		if(v[i] == '-') {
			//cout << "where" << endl;
			if(fcount < vfloat.size()) {
				v[i] = vfloat[fcount];
				vin[i] = 'f';
				fcount++;
			}
			else {
				vin[i] = '0';
				ji++;
			}
		} else if(vin[i] != 'f'){
			ic++;
			vin[i] = '1';
		}
		
	}
	
	//cout << vin[0] << endl;
	if((vfloat.size() == 0)) {
		cout << "no" << endl;
		cout << v.size() << endl;
		cout << in << endl;
		testCombo(v.size(), in, dict, ji, vin, comb, floating);
		return comb;
	}
	std::string s(v.begin(), v.end());
	std::string s2(vin.begin(), vin.end());
	cout << s2 << endl;
	cout << ji << endl;
	std::set<std::string> test;
	
	generateSetCombo(s, 0, v.size()-1, dict, ji, vin, test, comb, floating, ic);
	//std::set<std::string> comb = generateSetCombo(v.size(), in, v, j, floating, dict);
	return comb;

}

// Define any helper functions here

void testCombo(size_t size, std::string s, std::set<std::string> dict, int incnt, std::vector<char> vin, std::set<std::string>& temp, std::string f) {
	std::vector<char> v(s.begin(), s.end());
	std::vector<char> vfloat(f.begin(), f.end());
	cout << incnt << endl;
	if(size == 0) {
		return;
	} else if(incnt == 0) {
		//cout << "entered" << endl;
		if(dict.find(s) != dict.end()) {
			temp.insert(s);
		}
		return;
	}
	int ccnt = 0;
	while(ccnt != incnt) {
		ccnt = 0;
		for(size_t i = 0; i<size; i++) {
			if(vin[i] == '0') {
				if(v[i] == '-') {
					v[i] = 'a';
				}
				else if(v[i] == 'z') {
					v[i] = 'a';
					ccnt++;
					if(ccnt == incnt) {
						return;
					}
				}
				else {
					v[i]++;
					break;
				}
			}
		}
		std::string combos(v.begin(), v.end());
		//cout << combos << endl;
		if(vfloat.empty()) {
			//std::string combos(v.begin(), v.end());
			if((dict.find(combos) != dict.end())) {
				temp.insert(combos);
			}
		} 
		else if(dict.find(combos) != dict.end()) {
			//cout << combos << endl;
			testCombo(size, combos, dict, incnt, vin, temp, f);
			temp.insert(combos);
			return;
		}
	}
	
	return;
	
}


void generateSetCombo(std::string str, size_t l, size_t r, std::set<std::string> dict, int incnt, std::vector<char> vin, std::set<std::string>& test, std::set<std::string>& combo, std::string f, size_t inNum)
{
		std::vector<char> v(str.begin(), str.end());
		
		if (l == r)
		{
			
			if(test.find(str) == test.end()) {
				test.insert(str);
				if(incnt != 0) {
					cout << str << endl;
					testCombo(v.size(), str, dict, incnt, vin, combo, f);
				} else if(inNum == 0 && str.compare(f) != 0) {
						combo.insert(str);
					} else if(inNum != 0) {
						combo.insert(str);
					}
				//cout << "wor" << endl;
				return;
				//return combo;

				
				//combos.insert(c.begin(), c.end());
				//cout <<*(c.begin()) << endl;
				//std::set<std::string> temp;
				//std::merge(c.begin(), c.end(), combos.begin(), combos.end(), std::inserter(temp, temp.begin()));
			}

			
		}
	else
		{
		for(size_t i = l; i <= r; i++)
		{
			if((vin[i] != '1' && vin[l] != '1' ) && (v[i] != '-' || v[l] != '-')) {
			
			char temp = v[l];
			v[l] = v[i];
			v[i] = temp;
			std::string s(v.begin(), v.end());
			char temp1 = vin[l];
			vin[l] = vin[i];
			vin[i] = temp1;
			//cout << s << " " << r << " " << l << endl;
			generateSetCombo(s, l+1, r, dict, incnt, vin, test, combo, f, inNum);

			//backtrack

				char temp2 = v[l];
				v[l] = v[i];
				v[i] = temp2;
				char temp3 = vin[l];
				vin[l] = vin[i];
				vin[i] = temp3;
			
			} else if(vin[l] == '1' || (vin[i] == '0' && vin[l] == '0')) {
				generateSetCombo(str, l+1, r, dict, incnt, vin, test, combo, f, inNum);
			}
			
			
		}
		}
		//std::set<std::string> c;
		//c.insert(combos.begin(), combos.end());
		//std::merge(combos.begin(), c.end(), combos.begin(), combos.end(), std::inserter(temp, temp.begin()));
		return ;
}