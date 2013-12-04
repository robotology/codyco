/* 
 * Copyright (C) 2013 CoDyCo
 * Author: Andrea Del Prete
 * email:  andrea.delprete@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#ifndef _RECURSIVE_LINEAR_ESTIMATOR
#define _RECURSIVE_LINEAR_ESTIMATOR

#include <Eigen/Core>                               // import most common Eigen types
#include <Eigen/Cholesky>

namespace motorFrictionIdentification
{

/** Class for performing online (i.e. recursive) estimation of parameters
 * according to a linear model of the form:
 * \f[
 * \phi x = y,
 * \f]
 * where\f$ \phi \in R^{m\times n}\f$ is the regressor matrix, \f$ x \in R^n \f$ is 
 * the parameter vector and \f$ y \in R^m \f$ is the output vector. 
 * The parameters \f$ x \f$ are estimated in the least-square sense as:
 * \f[
 * \hat{x} = (\phi^T \phi)^{-1} \phi^T y
 * \f]
 * The estimation is performed online, that is the samples are provided as they become
 * available, and the parameter estimate is updated every time. After \f$ t \f$ input-output
 * samples (\f$ \Phi_t, Y_t\f$) have been fed into the estimator, the parameter estimate is:
 * \f[
 * \hat{x}_t = (\underbrace{\Phi_t^T \Phi_t}_{A_t})^{-1} \underbrace{\Phi_t^T Y_t}_{b_t}
 * \f]
 * To avoid storing all the samples in memory the estimator only need to store \f$ A_t \in R^{n \times n}\f$
 * and \f$ b_t \in R^n\f$, which have constant size. Actually, to improve the numerical accuracy
 * of the estimation, we store the Cholesky decomposition of \f$ A_t \f$, that is a triangular matrix
 * \f$ R_t \in R^{n \times n} \f$ such that \f$ A_t = R_t^T R_t \f$. It uses a rank 1 update rule to
 * incrementally update the Cholesky decomposition.
 */
class RecursiveLinearEstimator
{
protected:
    unsigned int        n;     ///< The dimensionality of the input domain
    //unsigned int        m;   ///< The dimensionality of the output domain (codomain)
    
    Eigen::LDLT<Eigen::MatrixXd>    R;  ///< Cholesky factor of the inverse covariance matrix (i.e. A).
    Eigen::VectorXd     x;              ///< current parameter estimate
    Eigen::VectorXd     b;              ///< current projected output

    //double sigma;           ///< Signal noise (don't know if it could be useful)
    int sampleCount;        ///< Number of samples during last training routine

    /** Checks whether the input is of the desired dimensionality.
     * @param input A sample input.
     * @return True if the dimensionality is correct. */
    inline bool checkDomainSize(const Eigen::VectorXd& input) const { return input.size()==n; }

    /** Checks whether the output is of the desired dimensionality.
     * @param output A sample output.
     * @return True if the dimensionality is correct. */
    //inline bool checkCoDomainSize(const Eigen::VectorXd& output){ return output.size()==m; }

    /** Validates whether the input and output are of the desired dimensionality.
     * @param input A sample input.
     * @param output The corresponding output. */
    //bool checkDomainCoDomainSizes(const Eigen::VectorXd& input, const Eigen::VectorXd& output)
    //{
    //    return checkDomainSize(input) && checkCoDomainSize(output);
    //}

    /** Resize all matrices and vectors based on the current domain and codomain sizes. */
    void resizeAllVariables();

public:

    /** Constructor.
     * @param nParam The number of parameters to estimate.*/
    RecursiveLinearEstimator(unsigned int nParam = 1);

    /** Provide the estimator with an example of the desired linear mapping.
     * @param input A sample input.
     * @param output The corresponding output. */
    void feedSample(const Eigen::VectorXd &input, const double &output);

    /** Update the current estimation of the parameters. */
    void updateParameterEstimation();

    /** Given an input predicts the corresponding output using the current parameter
     * estimate.
     * @param input A sample input.
     * @param output Output vector containing the predicted model output. */
    void predictOutput(const Eigen::VectorXd &input, double &output) const;

    /** Get the current estimate of the parameters x.
     * @param xEst Output vector containing the current estimate of the parameters. */
    void getCurrentParameterEstimate(Eigen::VectorXd &xEst) const;

    /** Returns the size (dimensionality) of the input domain.
     * @return The size of the input domain. */
    unsigned int getDomainSize() const { return this->n; }

    /** Returns the size (dimensionality) of the output domain (codomain).
     * @return The size of the codomain. */
    //unsigned int getCoDomainSize() const { return this->m; }

    /** Mutator for the domain size.
     * @param size The desired domain size. */
    virtual void setDomainSize(unsigned int size) { this->n = size; }

    /** Mutator for the codomain size.
     * @param size The desired codomain size. */
    //virtual void setCoDomainSize(unsigned int size) {this->m = size; }
};

}   // end namespace 

#endif
