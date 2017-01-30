#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;



int main() {
	int maxdim = 2000;
	int i;
	int j;
	int k;
	int HEIGHT = maxdim;
	int WIDTH = maxdim;
	int DEPTH = maxdim;

	int latConst;
	latConst = 8;

	enum { Cd, Se, H, Null };
	enum { N, X, Y, Z };
	enum { sphere, faceted };


	vector< vector< int > > crystal3D;
	vector < int > atom_vec (4,0);
	/*crystal3D.resize(HEIGHT);
	for (i = 0; i < HEIGHT; ++i) {
		crystal3D[i].resize(4);
	}*/

	int cellNum = 6;
	float rad = 5.1;
	int SeCnt = 0;
	int CdCnt = 0;
	int counter = 0;
	do {
		/*crystal3D.resize(HEIGHT);
		for (i = 0; i < HEIGHT; ++i) {
			crystal3D[i].resize(4);
		}*/
		counter = 0;
		for (i = 0; i < cellNum; i++)
			for (j = 0; j < cellNum; j++)
				for (k = 0; k < cellNum; k++){
				atom_vec[N] = Cd;
				atom_vec[X] = i * latConst / 2 + j * latConst / 2 - cellNum*latConst / 4 - latConst / 2;
				atom_vec[Y] = i * latConst / 2 + k * latConst / 2 - cellNum*latConst / 4 - latConst / 2;
				atom_vec[Z] = j * latConst / 2 + k * latConst / 2 - cellNum*latConst / 4 - latConst / 2;

				crystal3D.push_back(atom_vec);

				atom_vec[N] = Se;
				atom_vec[X] = latConst / 4 + i * latConst / 2 + j * latConst / 2 - cellNum*latConst / 4 - latConst / 2;
				atom_vec[Y] = latConst / 4 + i * latConst / 2 + k * latConst / 2 - cellNum*latConst / 4 - latConst / 2;
				atom_vec[Z] = latConst / 4 + j * latConst / 2 + k * latConst / 2 - cellNum*latConst / 4 - latConst / 2;

				crystal3D.push_back(atom_vec);
				}
		SeCnt = crystal3D.size() / 2;
		CdCnt = crystal3D.size() / 2;

		bool shape = faceted;
		if (shape != sphere){
			int E111 = 70000;
			int E100 = 10000;
			i = 0;
			bool flag = 1;
			while (i < crystal3D.size()){
				if ((crystal3D[i][X] + crystal3D[i][Y] + crystal3D[i][Z] > E111)
					|| (-crystal3D[i][X] - crystal3D[i][Y] + crystal3D[i][Z] > E111)
					|| (-crystal3D[i][X] + crystal3D[i][Y] - crystal3D[i][Z] > E111)
					|| (crystal3D[i][X] - crystal3D[i][Y] - crystal3D[i][Z] > E111)
					|| (abs(crystal3D[i][X]) > E100)
					|| (abs(crystal3D[i][Y]) > E100)
					|| (abs(crystal3D[i][Z]) > E100)){
					if (crystal3D[i][N] == Cd)
						CdCnt--;
					else
						SeCnt--;
					crystal3D.erase(crystal3D.begin() + i);
					flag = 0;


				}
				if (flag)
					i++;
				flag = 1;
			}
		}
		else
		{
			i = 0;
			bool flag = 1;
			while (i < crystal3D.size()){
				if (pow(crystal3D[i][X] * 1.0, 2.0) + pow(crystal3D[i][Y] * 1.0, 2.0) + pow(crystal3D[i][Z] * 1.0, 2.0) > pow(rad, 2.0)){
					if (crystal3D[i][N] == Cd)
						CdCnt--;
					else
						SeCnt--;
					crystal3D.erase(crystal3D.begin() + i);
					flag = 0;
				}
				if (flag)
					i++;
				flag = 1;
			}

		}
		counter = crystal3D.size();
		int minNNcnt = 0;
		while (minNNcnt < 2){
			minNNcnt = 2;
			for (i = 0; i < counter; i++){
				int NNcnt = 0;
				for (j = 0; j < counter; j++){
					if (crystal3D[i][N] == Cd)
						if ((crystal3D[i][X] - crystal3D[j][X] == -latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == -latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == -latConst / 4)
							|| (crystal3D[i][X] - crystal3D[j][X] == latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == -latConst / 4)
							|| (crystal3D[i][X] - crystal3D[j][X] == latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == -latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == latConst / 4)
							|| (crystal3D[i][X] - crystal3D[j][X] == -latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == latConst / 4))
							NNcnt++;

					if (crystal3D[i][N] == Se)
						if ((crystal3D[i][X] - crystal3D[j][X] == latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == latConst / 4)
							|| (crystal3D[i][X] - crystal3D[j][X] == -latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == -latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == latConst / 4)
							|| (crystal3D[i][X] - crystal3D[j][X] == -latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == -latConst / 4)
							|| (crystal3D[i][X] - crystal3D[j][X] == latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == -latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == -latConst / 4))
							NNcnt++;
				}

				if (NNcnt <= 1){
					if (crystal3D[i][N] == Cd)
						CdCnt--;
					else
						SeCnt--;
					crystal3D.erase(crystal3D.begin() + i);
					counter = crystal3D.size();
				}
				if (NNcnt < minNNcnt)
					minNNcnt = NNcnt;
				
			}
		}
		rad = rad - 0.1;
	} while ((rad >6) && (CdCnt != SeCnt) && (CdCnt > 0) && (SeCnt > 0));
	bool flag1;
	bool flag2;
	bool flag3;
	bool flag4;

	vector<int> Hvec;
	Hvec.assign(4, 0);
	for (i = 0; i < counter; ++i){
		int NNcnt = 0;
		flag1 = 1;
		flag2 = 1;
		flag3 = 1;
		flag4 = 1;
		for (j = 0; j < counter; ++j){
			if (crystal3D[i][N] == Cd){
				if ((crystal3D[i][X] - crystal3D[j][X] == -latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == -latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == -latConst / 4))
					flag1 = 0;

				if ((crystal3D[i][X] - crystal3D[j][X] == latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == -latConst / 4))
					flag2 = 0;

				if ((crystal3D[i][X] - crystal3D[j][X] == latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == -latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == latConst / 4))
					flag3 = 0;

				if ((crystal3D[i][X] - crystal3D[j][X] == -latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == latConst / 4))
					flag4 = 0;
			}
			else if (crystal3D[i][N] == Se){
				if ((crystal3D[i][X] - crystal3D[j][X] == latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == latConst / 4))
					flag1 = 0;

				if ((crystal3D[i][X] - crystal3D[j][X] == -latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == -latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == latConst / 4))
					flag2 = 0;

				if ((crystal3D[i][X] - crystal3D[j][X] == -latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == -latConst / 4))
					flag3 = 0;

				if ((crystal3D[i][X] - crystal3D[j][X] == latConst / 4) && (crystal3D[i][Y] - crystal3D[j][Y] == -latConst / 4) && (crystal3D[i][Z] - crystal3D[j][Z] == -latConst / 4))
					flag4 = 0;
			}
			else
			{
				flag1 = 0;
				flag2 = 0;
				flag3 = 0;
				flag4 = 0;
			}
		}
		if (crystal3D[i][N] == Cd){
			if (flag1){
				Hvec[N] = H;
				Hvec[X] = crystal3D[i][X] + latConst / 8;
				Hvec[Y] = crystal3D[i][Y] + latConst / 8;
				Hvec[Z] = crystal3D[i][Z] + latConst / 8;
				crystal3D.push_back(Hvec);
			}
			if (flag2){
				Hvec[N] = H;
				Hvec[X] = crystal3D[i][X] - latConst / 8;
				Hvec[Y] = crystal3D[i][Y] - latConst / 8;
				Hvec[Z] = crystal3D[i][Z] + latConst / 8;
				crystal3D.push_back(Hvec);
			}
			if (flag3){
				Hvec[N] = H;
				Hvec[X] = crystal3D[i][X] - latConst / 8;
				Hvec[Y] = crystal3D[i][Y] + latConst / 8;
				Hvec[Z] = crystal3D[i][Z] - latConst / 8;
				crystal3D.push_back(Hvec);
			}
			if (flag4){
				Hvec[N] = H;
				Hvec[X] = crystal3D[i][X] + latConst / 8;
				Hvec[Y] = crystal3D[i][Y] - latConst / 8;
				Hvec[Z] = crystal3D[i][Z] - latConst / 8;
				crystal3D.push_back(Hvec);
			}
		}
		else if (crystal3D[i][N] == Se){
			if (flag1){
				Hvec[N] = H;
				Hvec[X] = crystal3D[i][X] - latConst / 8;
				Hvec[Y] = crystal3D[i][Y] - latConst / 8;
				Hvec[Z] = crystal3D[i][Z] - latConst / 8;
				crystal3D.push_back(Hvec);
			}
			if (flag2){
				Hvec[N] = H;
				Hvec[X] = crystal3D[i][X] + latConst / 8;
				Hvec[Y] = crystal3D[i][Y] + latConst / 8;
				Hvec[Z] = crystal3D[i][Z] - latConst / 8;
				crystal3D.push_back(Hvec);
			}
			if (flag3){
				Hvec[N] = H;
				Hvec[X] = crystal3D[i][X] + latConst / 8;
				Hvec[Y] = crystal3D[i][Y] - latConst / 8;
				Hvec[Z] = crystal3D[i][Z] + latConst / 8;
				crystal3D.push_back(Hvec);
			}
			if (flag4){
				Hvec[N] = H;
				Hvec[X] = crystal3D[i][X] - latConst / 8;
				Hvec[Y] = crystal3D[i][Y] + latConst / 8;
				Hvec[Z] = crystal3D[i][Z] + latConst / 8;
				crystal3D.push_back(Hvec);
			}
		}

		/*counter = crystal3D.size();*/


	}


	string mopFilename;
	string csvFilename;
	string qchemInFilename;
	string groFilename;


	string CdString = static_cast<ostringstream*>(&(ostringstream() << CdCnt))->str();
	string SeString = static_cast<ostringstream*>(&(ostringstream() << SeCnt))->str();

	mopFilename = "QD_CdSe_Cd" + CdString + "Se" + SeString + ".mop";
	csvFilename = "QD_CdSe_Cd" + CdString + "Se" + SeString + ".csv";
	qchemInFilename = "QD_CdSe_Cd" + CdString + "Se" + SeString + ".in";
	groFilename = "conf.gro";

	ofstream mopFile(mopFilename.c_str());
	ofstream csvFile(csvFilename.c_str());
	ofstream qchemInFile(qchemInFilename.c_str());
	ofstream groFile(groFilename.c_str());

	mopFile << "PM7\n";
	mopFile << "Quantum Dot CdSe\n";
	mopFile << "Cartesian Coord\n";

	qchemInFile << "$comment\n";
	qchemInFile << "QD Cd" << CdString << "Se" << SeString << "\n";
	qchemInFile << "$end\n";
	qchemInFile << "$molecule\n";
	qchemInFile << "0 1\n";

	groFile << "QD CdSe" <<endl;
	groFile << "    " << CdCnt + SeCnt << endl;

	vector <string> atomName;
	atomName.push_back("Cd");
	atomName.push_back("Se");
	atomName.push_back("H");
	
	double latConst2;
	latConst2 = 0.608 / 8;

	counter = crystal3D.size();
	groFile.precision(3);

	if (mopFile.is_open())
	{
		for (i = 0; i < counter; i++)
		{
			if (crystal3D[i][N] != Null){
				csvFile << crystal3D[i][N] << "," << crystal3D[i][X] * latConst2 << "," << crystal3D[i][Y] * latConst2 << "," << crystal3D[i][Z] * latConst2 << "\n";
				switch (crystal3D[i][N]){
				case 0:
					qchemInFile << "Cd" << " " << crystal3D[i][X] * latConst2 << " " << crystal3D[i][Y] * latConst2 << " " << crystal3D[i][Z] * latConst2 << "\n";;
					break;
				case 1:
					qchemInFile << "Se" << " " << crystal3D[i][X] * latConst2 << " " << crystal3D[i][Y] * latConst2 << " " << crystal3D[i][Z] * latConst2 << "\n";;;
					break;
				case 2:
					qchemInFile << "H" << " " << crystal3D[i][X] * latConst2 << " " << crystal3D[i][Y] * latConst2 << " " << crystal3D[i][Z] * latConst2 << "\n";;;
					break;
				}
			}
 	 	if (crystal3D[i][N] == H) continue;
		groFile.width(5);
		groFile <<  i + 1;
		groFile.width(5);
		groFile << atomName[crystal3D[i][N]] + "B";
		groFile.width(5);
		groFile  <<  atomName[crystal3D[i][N]];
		groFile.width(5);
		groFile << i + 1;
		groFile.width(8);
		groFile << fixed << crystal3D[i][X] * latConst2 + 10;
		groFile.width(8);
		groFile << fixed << crystal3D[i][Y] * latConst2 + 10;
		groFile.width(8);
		groFile << fixed << crystal3D[i][Z] * latConst2 + 10 << endl; 
		}

		float box = 4.00000;
		groFile << "   " << box << "   " << box << "   " << box;

		qchemInFile << "$end\n";
		qchemInFile << "$rem\n";
		qchemInFile << "basis SBKJC\n";
		qchemInFile << "ecp SBKJC\n";
		qchemInFile << "exchange pbe0\n";
		qchemInFile << "max_scf_cycles 200\n";
		qchemInFile << "mem_static 1000\n";
		qchemInFile << "mem_total 16000\n";
		qchemInFile << "$end\n";

		mopFile.close();
		csvFile.close();
		qchemInFile.close();
	}

	return 0;
}
