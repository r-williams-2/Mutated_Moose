//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SplitCHCRes.h"

template <>
InputParameters
validParams<SplitCHCRes>()
{
  InputParameters params = validParams<SplitCHBase>();
  params.addClassDescription("Split formulation Cahn-Hilliard Kernel");
  params.addRequiredCoupledVar("w", "chem potential"); // Syntax for coupled variable for split CH (i.e. the variational derivative)
  params.addRequiredCoupledVar("c_j", "coupled concentrations"); // Syntax for coupled concentration to allow the calculation of the coupled gradients.
  //params.addRequiredCoupledVar("w", "Chemical potential");
  params.addRequiredParam<MaterialPropertyName>("kappa_name", "The kappa used with the kernel");
  // params.addParam<MaterialPropertyName>("mols_in_sys", "The total number of mols in the system"); // Get the material property named mols_in_sys.
  return params;
}

SplitCHCRes::SplitCHCRes(const InputParameters & parameters)
  : SplitCHBase(parameters),
    _kappa(getMaterialProperty<Real>("kappa_name")),
    // _no_mols(getMaterialProperty<Real>("mols_in_sys")), // Get 
    _w_var(coupled("w")), // Syntax for coupled variable for split CH (i.e. the variational derivative)
    _w(coupledValue("w")), // Syntax for coupled variable for split CH (i.e. the variational derivative)
    _c_j_var(coupled("c_j")), // Syntax for coupled concentration to allow the calculation of the coupled gradients.
    _c_j(coupledValue("c_j")), // Syntax for coupled concentration to allow the calculation of the coupled gradients.
    _grad_coupled(coupledGradient("c_j")) // Syntax for gradient of coupled concentrations.
    //_w_var(coupled("w")),
    //_w(coupledValue("w"))
{
}

/*Real
SplitCHCRes::computeDFDC(PFFunctionType type)
{
  switch (type)
  {
  case Residual:
    return _u[_qp]*_u[_qp]*_u[_qp] - _u[_qp]; // return Residual value

  case Jacobian:
    return (3.0*_u[_qp]*_u[_qp] - 1.0)*_phi[_j][_qp]; //return Jacobian value

  }

  mooseError("Invalid type passed in");
}*/

Real
SplitCHCRes::computeQpResidual()
{
  Real residual =
      SplitCHBase::computeQpResidual(); //(f_prime_zero+e_prime)*_test[_i][_qp] from SplitCHBase. This is the partial derivative term.

  residual += -_w[_qp] * _test[_i][_qp]; // This is the coupled variable term.
  residual += 0.5 * _kappa[_qp] * _grad_u[_qp] * _grad_test[_i][_qp]; // This is the coupled gradients term for (1/n)*k*grad(c_i)*grad(test), where c_i is the primary concentration.
  //_grad_args.resize(_c_j.size());
  // for (unsigned int j = 0; j < _c_j.size(); j++)
  // {
  //   //MooseVariable * cvar = _c_j[j];
  //   //_grad_args[j] = &(cvar->gradSln());
  //   residual += (1.0 / _no_mols[_qp]) * _kappa[_qp] * coupledGradient("_c_j", j)[_qp] * _grad_test[_i][_qp];
  // }
  residual += 0.5 * _kappa[_qp] * _grad_coupled[_qp] * _grad_test[_i][_qp]; // This is the coupled gradients term for (1/n)*k*grad(c_j)*grad(test), where c_j is the secondary concentration.
  // Since kappa is the same, constant value in both cases, it is like a matrix of constants. If we neglected the second term, it would be like only constants on the leading diagonal.
  // If we were to have an arbitrary number of phases, there would need to be a sum over all 

  //residual += -_w[_qp] * _test[_i][_qp];
  //residual += _kappa[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];

  return residual;
}

Real
SplitCHCRes::computeQpJacobian()
{
  Real jacobian = SplitCHBase::computeQpJacobian(); //(df_prime_zero_dc+de_prime_dc)*_test[_i][_qp];
                                                    // from SplitCHBase

  jacobian += 0.5 * _kappa[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
  //jacobian += _kappa[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];

  return jacobian;
}

Real
SplitCHCRes::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _w_var)
  {
    return -_phi[_j][_qp] * _test[_i][_qp];
  }
  else if (jvar == _c_j_var)
  {
    return 0.5 * _kappa[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
    // for(int i = 0; i < v.size(); i++){ // Code for arbitrary number of concentrations.
	  //   printf("%d", v[i]);
    // }
  }
  else
  {
    return 0.0;
  }

  //return 0.0;
}
