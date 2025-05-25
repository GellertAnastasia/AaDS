#include "method.h"

Eigen::VectorXd gaussianMethod(Eigen::MatrixXd& A)
{
    int n = A.rows();
    int m = A.cols();
    for (int i = 0; i < n; i++)
    {
        int maxRow = i;
        double maxVal = std::abs(A(i, i));
        for (int k = i + 1; k < n; k++)
        {
            if (std::abs(A(k, i)) > maxVal)
            {
                maxVal = std::abs(A(k, i));
                maxRow = k;
            }
        }
        
        if (maxRow != i)
        {
            A.row(i).swap(A.row(maxRow));
        }
        if (std::abs(A(i, i)) < 1e-10)
        {
            std::cerr << "Matrix is singular\n";
            return Eigen::VectorXd::Zero(n);
        }
        const double y = 1.0 / A(i,i);
        A.row(i) *= y;
        A(i,i) = 1.0;

        for (int k = i + 1; k < n; k++)
        {
            const double y = A(k,i);
            A.row(k) -= A.row(i) * y;
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        bool allZero = true;
        for (int j = 0; j < m - 1; j++)
        {
            if (std::abs(A(i, j)) > 1e-10)
            {
                allZero = false;
                break;
            }
        }
        if (allZero && std::abs(A(i, m - 1)) > 1e-10)
        {
            std::cerr << "Matrix is inconsistent\n";
            return Eigen::VectorXd::Zero(n);
        }
    }

    Eigen::VectorXd x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        x(i) = A(i, m - 1);
        if (i < n - 1) {
            x(i) -= A.row(i).segment(i+1, n-i-1).dot(x.segment(i+1, n-i-1));
        }
    }

    return x;
}
