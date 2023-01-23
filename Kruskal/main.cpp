#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "Array.h"
using namespace std;



void UnionFind(double** edges, double** mst, double size) {
	int** parent = new int*[size];
	for (int i = 0; i < size; i++) {
		parent[i] = new int;
		*parent[i] = i;
	}
	int a, b, aRoot, bRoot;
	int j = 0;

	for (int i = 0; i < size - 1; i) {
		bool flag = false;
		a = edges[j][0];
		b = edges[j][1];
		

		while (!flag) {
			if (*parent[a] != a) {
				a = *parent[a];
			}
			else {
				aRoot = *parent[a];
				flag = true;
			}
		}

		while (flag) {
			if (*parent[b] != b) {
				b = *parent[b];
			}
			else {
				bRoot = *parent[b];
				flag = false;
			}
		}

		//cout << aRoot << " " << bRoot << endl << endl;

		if (aRoot != bRoot) {
			mst[i] = edges[j];
			parent[bRoot] = parent[aRoot];

			/*for (int u = 0; u < size; u++) {
				cout << *parent[u] << endl;
			}
			cout << endl;*/

			i++;
		}
		j++;
	}

	/*for (int i = 0; i < size; i++) {
		cout << *parent[i] << endl;
	}*/
}

void Find() {

}

void Union() {

}


void bucketSort(double** a, int size) {
	int n = floor(sqrt(size));
	double w = 1.0 / n;
	Array* buckets = new Array[n];
	for (int i = 0; i < size; i++) {
		int bucketIndex = floor(a[i][2] / w);
		buckets[bucketIndex].add(a[i]);
	}
	for (int i = 0; i < n; i++) {
		buckets[i].sort();

	}
	Array* result = new Array;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < buckets[i].numberOfRecords; j++) {
			result->add(buckets[i].ar[j]);
		}
	}
	//result->print();
	for (int i = 0; i < size; i++) {
		a[i] = result->ar[i];
	}
}

int main() {
	string text;
	double **vertices;
	double **edges;
	double **mst;
	fstream file;

	file.open("g3.txt");

	getline(file, text);
	istringstream iss(text);
	int w;
	iss >> w;
		
	vertices = new double* [w];
	for (int i = 0; i < w; i++) {
		vertices[i] = new double[2];
	}
	for (int i = 0; i < w; i++) {
		getline(file, text);
		istringstream iss(text);
		double a, b;
		iss >> a >> b;

		vertices[i][0] = a;
		vertices[i][1] = b;
	}

	getline(file, text);
	istringstream isk(text);
	int k;
	isk >> k;

	edges = new double* [k];
	for (int i = 0; i < k; i++) {
		edges[i] = new double[3];
	}
	for (int i = 0; i < k; i++) {
		getline(file, text);
		istringstream iss(text);
		double c;
		int a, b;

		iss >> a >> b >> c;

		edges[i][0] = a;
		edges[i][1] = b;
		edges[i][2] = c;
	}

	mst = new double* [w - 1];
	for (int i = 0; i < w - 1; i++) {
		mst[i] = new double[3];
	}

	file.close();
	
	bucketSort(edges, k);

	/*for (int i = 0; i < k; i++) {
		cout << i << " " << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << endl;
	}
	cout << endl;*/
	
	UnionFind(edges, mst, w);

	for (int i = 0; i < w-1; i++) {
		cout << i << " " << mst[i][0] << " " << mst[i][1] << " " << mst[i][2] << endl;
	}
	cout << endl;

}