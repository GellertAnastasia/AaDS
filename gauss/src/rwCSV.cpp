#include "rwCSV.h"


Eigen::MatrixXd readCSV(const std::string& file)
{
    std::vector<std::vector<double>> rcsv;
    {
        lazycsv::parser parser{file};
        for (const auto row : parser)
        {
            std::vector<double> r;
            for (const auto cell : row)
            {
                r.push_back(std::stod(std::string(cell.raw())));
            }
            rcsv.push_back(r);
        }
    }

    int rows = rcsv.size();
    int cols = rcsv[0].size();
    Eigen::MatrixXd A(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A(i, j) = rcsv[i][j];
        }
    }
    return A;
}

void writeCSV(const Eigen::VectorXd& x)
{
    std::ofstream file("solution.csv");

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << "solution.csv" << std::endl;
        return;
    }

    for (int i = 0; i < x.size(); i++)
    {
        file << x(i);
        if (i != x.size() - 1)
        {
            file << ",";
        }
    }

    file.close();
    std::cout << "Data written to " << "solution.csv" << std::endl;
}
