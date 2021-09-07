// PA2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//


#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <map>
using namespace std;
int call =0;

// Merge
void Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
	// Function : Merge two sorted subvector
	vector<int> L;
	vector<int> R;
	for (int i = low; i <= middle1; i++) {
		L.push_back(data[i]);
	}
	for (int i = middle2; i <= high; i++) {
		R.push_back(data[i]);
	}
	L.push_back(10000010);//超過1000000我看記憶體直接爆掉。
	R.push_back(10000010);
	int la = 0;
	int ra = 0;
	for (int i = low; i <= high; i++) {
		if (L[la] <= R[ra]) {
			data[i] = L[la];
			la++;
		}
		else {
			data[i] = R[ra];
			ra++;
		}

	}
}

void MergeSortSubVector(vector<int>& data, int low, int high) {


	if (low < high) {
		int q = (low + high) / 2;
		int qa = q + 1;
		MergeSortSubVector(data, low, q);
		MergeSortSubVector(data, q + 1, high);
		Merge(data, low, q, qa, high);
	}
}
void MergeSort(vector<int>& data) {
	MergeSortSubVector(data, 0, data.size() - 1);
}



void find_chordset(int max,int min,vector<vector<char>> &zeroset, vector<int> &chord, vector<int> &chord_set){   //只讀取從上而下看下來maxset真的有改變的情況。
	while (max > min+1) {

		if (zeroset[max][min] == '3') {
			chord_set.push_back(chord[max]);
			find_chordset(max - 1, chord[max]+1, zeroset, chord, chord_set);
			max = chord[max] - 1;
		}
		else if (zeroset[max][min] == '2') {
			chord_set.push_back(chord[max]);
			find_chordset(max - 1, min+1, zeroset, chord, chord_set);
			max = min - 1;
		}
		else {
			max--;
		}


	}
}
int find_needset(int max, int min, vector<int> &chord, vector<vector<short>> &needset, vector<int> &check, vector<int> &conj, bool left, bool right, vector<vector<char>> &zeroset) {

	if (needset[max][min] != -1) {
		return needset[max][min];

	}
	
	if (min >= max) {
		return 0;
	}

	if (chord[max] > max or chord[max] < min) {
		if (max - 1 > min) {
			if (needset[max - 1][min] == -1) {
				needset[max][min] = find_needset(max - 1, min, chord, needset, check, conj,left,right,zeroset);

			}
			else {
				needset[max][min] = needset[max - 1][min];
				
			}

			return needset[max][min];
		}

		return 0;

		
	}

	else if (chord[max] == min) {
		if (max-1 > min+1) {
			if (needset[max - 1][min + 1] == -1) {
				needset[max][min] = find_needset(max - 1, min + 1, chord, needset, check, conj,left,right,zeroset)+1;
			}
		else {
			needset[max][min] = needset[max-1][min+1]+1;
		}

			zeroset[max][min] = '2';
		}
		else {
			needset[max][min] = 1;
			zeroset[max][min] = '2';
		}

		return needset[max][min];

	}

	else {
		vector<int> q;
		vector<int> e;
		vector<int> f;
		bool ao =0;
		bool bo =0;
		int jo = 0;
		int mo = 1;
		if (max - 1 > min ) {
			if (needset[max - 1][min] == -1) {
				jo = find_needset(max - 1, min, chord, needset, check, conj,true,false,zeroset);
				
			}
			else {

				jo = needset[max - 1][min];

			}
		}

		if (max - 1 > chord[max] + 1){
			
			if (needset[max - 1][chord[max] + 1] == -1) {
				mo +=find_needset(max - 1, chord[max] + 1, chord, needset, check, conj,false,true,zeroset);
			}
			else {
				mo += needset[max-1][chord[max] + 1];
			}

		}
		if (chord[max] -1  > min) {
			if (needset[chord[max] - 1][min] !=- 1) {
				mo += needset[chord[max] - 1][min];

			}
			else {
				
				mo += find_needset(chord[max] - 1, min, chord, needset, check, conj, false, true, zeroset);
			}


		}



		if (mo>jo) {
			needset[max][min] = mo;
			zeroset[max][min] = '3';
		}
		else {

			needset[max][min] = jo;
		}

		}
		

		return needset[max][min];
	}
	

	





int main(int argc, char* argv[])
{
	if (argc != 3) {
		cout << "3";
		return 0;
	}
	fstream fin(argv[1]);
	fstream fout;
	fout.open(argv[2], ios::out);

	int num;

	vector<int> data;
    
	int k = 0;
	while (!fin.eof())
	{
		k += 1;
		if (k > 1000000){
			
			break;
		}
		fin >> num;
		//cout << num;
		data.push_back(num);
	}
	if (k > 1000000) {
		return 0;
	}
	//以上是讀入，從pa1修改來的

	int max_e = data[0] - 1;
	
	vector<int> chord(data[0],0);
	vector<vector<pair<int,int>>> maxset;
	vector<vector<short>> needset(data[0]);
	vector<vector<char>> mumiset(data[0]);
	vector<pair<int,int>> row;
	vector<int> case_equal(data[0], 0);
	vector<int> aka;
	vector<int> baka;
	aka.reserve(100);
	baka.reserve(100);
	
	row.assign(1, make_pair(0,0));
	maxset.assign(data[0], row);
	for (int i = 1; i < data[0] ; i++) {
		needset[i].assign(i,-1);
		mumiset[i].assign(i, -1);
	}



	for (int i = 1; i < data.size()-2; i += 2) {
		if (data[i] == 143) {
			cout << "s" << endl;
		}
		chord[data[i]] = data[i + 1];
		chord[data[i+1]] = data[i];



	}

	int conj = 0;
	int check = 0;
	

	

	find_needset(data[0]-1, 0, chord, needset, aka, baka,1,0,mumiset);
	int ans = needset[data[0] - 1][0];
	needset.clear();
	cout << needset.capacity() << endl;
	find_chordset(data[0] - 1, 0, mumiset, chord, aka);

	MergeSort(aka);


	cout <<ans<< endl;
	cout << aka.size() << endl;


	fout << ans<< endl;;

	for (int i = 0; i < aka.size(); i++) {
		fout << aka[i] << " " << chord[aka[i]]<<endl;
	}
	cout << endl;

	fin.close();
	fout.close();
	return 0;

    
}

