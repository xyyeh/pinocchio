//
// Copyright (c) 2018 CNRS
//

#include "pinocchio/bindings/python/algorithm/algorithms.hpp"
#include "pinocchio/algorithm/regressor.hpp"

namespace pinocchio
{
  namespace python
  {

    Eigen::MatrixXd bodyRegressor_proxy(const Motion & v, const Motion & a)
    {
      return bodyRegressor(v,a);
    }

    Eigen::MatrixXd jointBodyRegressor_proxy(const Model & model, Data & data, const JointIndex jointId)
    {
      return jointBodyRegressor(model,data,jointId);
    }

    void exposeRegressor()
    {
      using namespace Eigen;

      bp::def("computeStaticRegressor",
              &regressor::computeStaticRegressor<double,0,JointCollectionDefaultTpl,VectorXd>,
              bp::args("Model","Data",
                       "Configuration q (size Model::nq)"),
              "Compute the static regressor that links the inertia parameters of the system to its center of mass position,\n"
              "put the result in Data and return it.",
              bp::return_value_policy<bp::return_by_value>());

      bp::def("bodyRegressor",
              &bodyRegressor_proxy,
              bp::args("velocity","acceleration"),
              "Computes the regressor for the dynamic parameters of a single rigid body.\n"
              "The result is such that "
              "Ia + v x Iv = bodyRegressor(v,a) * I.toDynamicParameters()");

      bp::def("jointBodyRegressor",
              &jointBodyRegressor_proxy,
              bp::args("Model","Data",
                       "jointId (int)"),
              "Compute the regressor for the dynamic parameters of a rigid body attached to a given joint.\n"
              "This algorithm assumes RNEA has been run to compute the acceleration and gravitational effects.");
    }
    
  } // namespace python
} // namespace pinocchio
