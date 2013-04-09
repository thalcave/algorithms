#ifndef GENVECTOR_HPP
#define GENVECTOR_HPP

#include <vector>

typedef std::vector<unsigned> IntVector;

IntVector
generateVector(unsigned& search);

void
printVector(IntVector const&);

#endif

