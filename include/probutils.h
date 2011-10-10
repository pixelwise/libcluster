#ifndef PROBUTILS_H
#define PROBUTILS_H

#include <stdexcept>
#include <Eigen/Dense>
#include <vector>

//
// Useful Typedefs
//

typedef Eigen::Array<bool, Eigen::Dynamic, 1> ArrayXb; //!< Boolean Array


//
// Namespaces
//

/*! \brief Namespace for various linear algebra tools useful for dealing with
 *         Gaussians and log-probability expressions.
 *
 * \author Daniel Steinberg
 *         Australian Centre for Field Robotics
 *         The University of Sydney
 *
 * \date   15/02/2011
 */
namespace probutils
{

/*! \brief Calculate the column means of a matrix.
 *
 *  \param X an NxD matrix.
 *  \returns a 1xD row vector of the means of each column of X.
 */
Eigen::RowVectorXd mean (const Eigen::MatrixXd& X);


/*! \brief Calculate the column means of a vector of matrices (one mean for
 *         all data in the matrices).
 *
 *  \param X a vector of N_jxD matrices for j = 1:J.
 *  \returns a 1xD row vector of the means of each column of X.
 *  \throws std::invalid_argument if X has inconsistent D between elements.
 */
Eigen::RowVectorXd mean (const std::vector<Eigen::MatrixXd>& X);


/*! \brief Calculate the column standard deviations of a matrix, uses N - 1.
 *
 *  \param X an NxD matrix.
 *  \returns a 1xD row vector of the standard deviations of each column of X.
 */
Eigen::RowVectorXd stdev (const Eigen::MatrixXd& X);


/*! \brief Calculate the covariance of a matrix.
 *
 *    If X is an NxD matrix, then this calculates:
 *
 *    Cov(X) = (X-E[X])' * (X-E[X]) / (N-1)
 *
 *  \param X is a NxD matrix to calculate the covariance of.
 *  \returns a DxD covariance matrix.
 *  \throws std::invalid_argument if X is 1xD or less (has one or less
 *          observations).
 */
Eigen::MatrixXd cov (const Eigen::MatrixXd& X);


/*! \brief Calculate the covariance of a vector of matrices (one mean for
 *         all data in the matrices).
 *
 *    This calculates:
 *
 *    Cov(X) = Sum_j (X_j-E[X])' * (X_j-E[X]) / [-1 + Sum_j N_j]
 *
 *  \param X is a a vector of N_jxD matrices for j = 1:J.
 *  \returns a DxD covariance matrix.
 *  \throws std::invalid_argument if any X_j has one or less observations.
 *  \throws std::invalid_argument if X has inconsistent D between elements.
 */
Eigen::MatrixXd cov (const std::vector<Eigen::MatrixXd>& X);


/*! \brief Calculate the Mahalanobis distance, (x-mu)' * A^-1 * (x-mu), N
 *         times.
 *
 *  \param X an NxD matrix of samples/obseravtions.
 *  \param mu a 1XD vector of means.
 *  \param A a DxD marix of weights, A must be invertable.
 *  \returns an Nx1 matrix of distances evaluated for each row of X.
 *  \throws std::invalid_argument If X, mu and A do not have compatible
 *          dimensionality, or if A is not PSD.
 */
Eigen::VectorXd mahaldist (
    const Eigen::MatrixXd& X,
    const Eigen::RowVectorXd& mu,
    const Eigen::MatrixXd& A
    );


/*! \brief Perform a log(sum(exp(X))) in a numerically stable fashion.
 *
 *  \param X is a NxK matrix. We wish to sum along the rows (sum out K).
 *  \returns an Nx1 vector where the log(sum(exp(X))) operation has been
 *           performed along the rows.
 */
Eigen::VectorXd logsumexp (const Eigen::MatrixXd& X);


/*! \brief The eigen power method. Return the principal eigenvalue and
 *         eigenvector.
 *
 *  \param A is the DxD matrix to decompose.
 *  \param eigvec is the Dx1 principal eigenvector (mutable)
 *  \returns the principal eigenvalue.
 *  \throws std::invalid_argument if the matrix A is not square
 *
 */
double eigpower (const Eigen::MatrixXd& A, Eigen::VectorXd& eigvec);


/*! \brief Get the log of the determinant of a PSD matrix.
 *
 *  \param A a DxD positive semi-definite matrix.
 *  \returns log(det(A))
 *  \throws std::invalid_argument if the matrix A is not square or if it is
 *          not positive semidefinite.
 */
double logdet (const Eigen::MatrixXd& A);


/*! \brief Calculate digamma(X) for each element of X.
 *
 *  \param X an NxM matrix
 *  \returns an NxM matrix for which digamma(X) has been calculated for each
 *           element
 */
Eigen::MatrixXd mxdigamma (const Eigen::MatrixXd& X);


/*! \brief Calculate log(gamma(X)) for each element of X.
 *
 *  \param X an NxM matrix
 *  \returns an NxM matrix for which log(gamma(X)) has been calculated for
 *           each element
 */
Eigen::MatrixXd mxlgamma (const Eigen::MatrixXd& X);


/*! \brief Calculate the square c-seperation between two Gaussians, defined:
 *
 *    C^2_k,l = ||mu_k - mu_l||^2 / (D*max(eigval_max,k, eigval_max,l))
 *
 *  \param eigvalk, maximum eigenvalue of the covariance matrix of Gaussian k
 *  \param eigvall, maximum eigenvalue of the covariance matrix of Gaussian l
 *  \param muk, the mean vector of Gaussian k
 *  \param mul, the mean vector of Gaussian l
 *  \returns the square of the c-seperation of the two Gaussians
 *  \throws std::invalid_argument if muk and mul are not the same length.
 */
double cseperation (
    double eigvalk,
    double eigvall,
    const Eigen::RowVectorXd& muk,
    const Eigen::RowVectorXd& mul
    );

}

#endif // PROBUTILS_H
