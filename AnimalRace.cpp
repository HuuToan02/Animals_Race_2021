#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define SUTU_TIMESTART 9
#define THO_TIMESTART 8
#define RUA_TIMESTART 7
#define SUTU_QDCHAY 210
#define THO_QDCHAY 210
#define RUA_QDCHAY 135
struct ConVat {
	string MaSo;
	int TocDo, TrangBi;
};
void NhapConVat(ifstream &in, ConVat& a) {
	in >> a.MaSo >> a.TocDo >> a.TrangBi;
}
void XuatConVat(ofstream &out, ConVat& a) {
	out << a.MaSo << "  " << a.TocDo << "  " << a.TrangBi << endl;
}
void NhapDanhSachConVat(ifstream& in, vector<ConVat> &DanhSach) {
	int n; in >> n;
	for (int i = 0; i < n; i++) {
		ConVat a;
		NhapConVat(in, a);
		DanhSach.push_back(a);
	}
}
int Vantocthucsu(ConVat a) {
	if (a.TrangBi == 0) return a.TocDo;
	else {
		if (a.MaSo[0] == 'L') return a.TocDo * 2;
		if (a.MaSo[0] == 'R') return a.TocDo += 30;
		if (a.MaSo[0] == 'T') return a.TocDo * 5;
	}
}
double tinhThoiGian(ConVat a) {
	int vantoc = Vantocthucsu(a);
	if (a.MaSo[0] == 'L') {
		return (double)SUTU_QDCHAY / vantoc + SUTU_TIMESTART;
	}
	if (a.MaSo[0] == 'R') {
		return (double)THO_QDCHAY / vantoc + THO_TIMESTART;
	}
	if (a.MaSo[0] == 'T') {
		return (double)RUA_QDCHAY / vantoc + RUA_TIMESTART;
	}
}
void SapXepDanhSach(vector<ConVat>& DanhSach) {
	int n = DanhSach.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (tinhThoiGian(DanhSach[i]) > tinhThoiGian(DanhSach[j])) {
				ConVat b;
				b = DanhSach[i];
				DanhSach[i] = DanhSach[j];
				DanhSach[j] = b;
			}
		}
	}
}
int main() {
	ifstream in("INPUT.txt");
	vector<ConVat> DanhSach;
	NhapDanhSachConVat(in, DanhSach);
	SapXepDanhSach(DanhSach);
	in.close();
	ofstream out("OUTPUT.txt");
	out << " " << endl;
	int n = DanhSach.size();
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (tinhThoiGian(DanhSach[i]) <= 12) {
			out << i + 1 << ". ";
			XuatConVat(out, DanhSach[i]);
			count++;
		}
	}
	out.seekp(0, SEEK_SET);
	out << count << endl;
	system("pause");
}
