#include <flann/flann.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <iomanip>
using namespace std;
using namespace boost;

int main(int argc, char** argv) {
	const int numResult = 2;
	const int numInput = 100;
	const int numQuery = 2;
	const int dimension = 2;
	const int maxValue = 255;
	const int minValue = 0;

	mt19937 gen(static_cast<unsigned long>(time(0)));
	uniform_smallint<> dst(minValue,maxValue);
	variate_generator<mt19937&, uniform_smallint<> > rand(gen, dst);

	//Calculate the width of values
	ostringstream ss;
	ss << (numInput - 1);
	string s = ss.str();
	int lnWidth = s.length(); // for line number
	ostringstream sss;
	sss << maxValue;
	s = sss.str();
	int valWidth = s.length(); // for each values
	ostringstream ssss;
	ssss << numQuery;
	s = ssss.str();
	int qWidth = s.length(); // for query number

	cout << "Target Data:" << endl;
	int targetData[(numInput * dimension)];
	for (int i = 0; i < numInput; ++i) {
		cout.width(qWidth);
		cout.fill(' ');
		cout << ' ';
		cout << "#";
		cout.width(lnWidth);
		cout.fill('0');
		cout << i << "\t";
		for (int j = 0; j < dimension; ++j) {
			targetData[i * dimension + j] = rand();
			cout.width(valWidth);
			cout.fill(' ');
			cout << targetData[i * dimension + j] << "\t";
		}
		cout << endl;
	}
	flann::Matrix<int> dataset(targetData, numInput, dimension);
	int queryData[dimension];
	cout << endl << "Query:" << endl;
	for (int i = 0; i < numQuery; i++) {
		cout << "Q";
		cout.width(qWidth);
		cout.fill('0');
		cout << i;
		cout.width(lnWidth + 1);
		cout.fill(' ');
		cout << " " << "\t";
		for (int j = 0; j < dimension; j++) {
			queryData[(i * dimension) + j] = rand();
			cout.width(valWidth);
			cout.fill(' ');
			cout << queryData[(i * dimension) + j] << "\t";
		}
		cout << endl;
	}
	flann::Matrix<int> query(queryData, numQuery, dimension);
	flann::Matrix<int> indices(new int[query.rows * numResult], query.rows,
			numResult);
	flann::Matrix<float> dists(new float[query.rows * numResult], query.rows,
			numResult);
	// construct an randomized kd-tree index using 4 kd-trees
	flann::Index<flann::L2<int> > index(dataset, flann::KDTreeIndexParams(8));
	index.buildIndex();
	// do a knn search, using 128 checks
	index.knnSearch(query, indices, dists, numResult, flann::SearchParams(128));
	cout << endl;
	for (int q = 0; q < numQuery; q++) {
		for (int r = 0; r < numResult; r++) {
			cout << "Q";
			cout.width(qWidth);
			cout.fill('0');
			cout << q;
			cout << "#";
			cout.width(lnWidth);
			cout.fill('0');
			cout << indices[q][r] << "\t";
			for (int j = 0; j < dimension; ++j) {
				cout.width(valWidth);
				cout.fill(' ');
				cout << dataset[indices[q][r]][j] << "\t";
			}
			cout << "dist:" << dists[q][r] << endl;
		}
	}
	//delete[] dataset.ptr();
	//delete[] query.ptr();
	delete[] indices.ptr();
	delete[] dists.ptr();
	return 0;
}
