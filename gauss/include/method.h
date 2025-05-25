#ifndef METHOD_H
#define METHOD_H
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "../libs/lazycsv.hpp"

Eigen::VectorXd gaussianMethod(Eigen::MatrixXd& A);

#endif
