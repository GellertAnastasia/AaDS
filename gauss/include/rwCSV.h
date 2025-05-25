#ifndef RWCSV_H
#define RWCSV_H
#include <iostream>
#include <string>
#include <fstream>
#include <Eigen/Dense>
#include "../libs/lazycsv.hpp"

Eigen::MatrixXd readCSV(const std::string& file);
void writeCSV(const Eigen::VectorXd& x);

#endif
