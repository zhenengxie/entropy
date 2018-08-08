#include "nabo/nabo.h"
#include <iostream>
#include <unsupported/Eigen/SpecialFunctions>
#include <cmath>
#include <random>
#include <algorithm>

using namespace Nabo;
using namespace Eigen;

double sample(double dummy) {
  static std::random_device rd{};
  static std::mt19937 gen{rd()};
  static std::normal_distribution<> dist{0, 1};
  return dist(gen);
}

ArrayXd kl_entropy(MatrixXd M, int k, double epsilon = 0)
{
  const int d = M.rows();
  const int n = M.cols();
  
  // create a kd-tree for M, note that M must stay valid during the lifetime of the kd-tree
  NNSearchD* nns = NNSearchD::createKDTreeLinearHeap(M);

  // look for the 5 nearest neighbour of a the single-point query
  MatrixXi indices(k, n);
  MatrixXd dists2(k, n);
  nns->knn(M, indices, dists2, k, epsilon);

  // cleanup kd-tree
  delete nns;

  ArrayXd estimate;
  estimate = dists2.array().log().rowwise().sum();
  estimate = estimate * d;
  estimate = estimate / (2 * n);
  estimate = estimate - ArrayXd::LinSpaced(k, 1, k).digamma();
  estimate = estimate + 0.5 * d * log(M_PI) - lgamma(1 + 0.5 * d) + log(n - 1);

  return estimate;
}

int main()
{
  const int d = 1; // dimensions
  const int n = 100000; // number of data points
  const int k = 10;

  // Generate data from uniform with d independent components
  MatrixXd M = MatrixXd::Random(d, n);

  ArrayXd estimate = kl_entropy(M, k);

  std::cout << estimate << std::endl;
}
