#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <typeinfo>

#include <Eigen/Dense>
#include "libs/lazycsv.hpp"

int main() {
    std::vector<std::vector<double>> rcsv{};
    {
        lazycsv::parser parser{ "AB.csv" };
        for (const auto row : parser)
        {
            std::vector<double> r{};
            for (const auto cell : row)
            {
                r.push_back(std::stod(std::string(cell.raw())));
            }
            rcsv.push_back(r);
        }
    }

    // Создаем матрицы с использованием Eigen
    Eigen::Matrix<double, -1, -1, Eigen::RowMajor> A(rcsv.size(), rcsv.begin()->size());

    int ir = 0;
    for(auto r : rcsv)
    {
        int ic = 0;
        std::cout << "row:";
        for(double e: r) {
            A(ir, ic++) = e;
        }
        ir++;
        std::cout << std::endl;
    }

    Eigen::MatrixXd B(3, 2); // ColMajor по-умолчанию будет скорее
    // https://eigen.tuxfamily.org/dox/group__TopicStorageOrders.html
    B << 7, 8,
         9, 10,
         11, 12;

    // Умножение матриц с использованием Eigen
    Eigen::MatrixXd C = A * B;

    std::cout << "Матрица A:\n" << A << "\n\n";
    std::cout << "Матрица B:\n" << B << "\n\n";
    std::cout << "Результат умножения (C = A * B):\n" << C << "\n";

    // Редактирование на месте
    double c = 2.0;
    A.row(0) += c * A.row(1);
    A.coeffRef(1, 1) -= B.coeff(1, 1);
    std::cout << "Новая матрица A:\n" << A << "\n\n";

    return 0;
}
