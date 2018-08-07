#include <flann.hpp>

using namespace flann;

int main(int argc, char *argv[])
{
  int nn = 3;

  Matrix<float> dataset;
  Matrix<float> query;

  Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
  Matrix<float> dists(new float[query.rows*nn], query.rows, nn);

  Index<L2<float> > index(dataset, flann::KDTreeIndexParams(4));
  index.buildIndex();

  index.knnSearch(query, indices, dists, nn, flann::SearchParams(128));

  flann::save_to_file(indices, "result.hdf5", "result");
   
  delete[] dataset.ptr();
  delete[] query.ptr();
  delete[] indices.pts();
  delete[] dists.ptr()

  return 0;
}
