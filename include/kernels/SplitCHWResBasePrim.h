//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef SPLITCHWRESBASEPRIM_H
#define SPLITCHWRESBASEPRIM_H

#include "Kernel.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

// Forward declarations
template <typename T = void>
class SplitCHWResBasePrim;

template <>
InputParameters validParams<SplitCHWResBasePrim<>>();
/**
 * SplitCHWresBase implements the residual for the chemical
 * potential in the split form of the Cahn-Hilliard
 * equation in a general way that can be templated to a scalar or
 * tensor mobility.
 * This is the first of the two terms.
 */
template <typename T>
class SplitCHWResBasePrim : public DerivativeMaterialInterface<JvarMapKernelInterface<Kernel>>
{
public:
  SplitCHWResBasePrim(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialPropertyName _mob_name;
  const MaterialProperty<T> & _mob;

  unsigned int _c_i_var; // Syntax for defining the coupled concentration that this kernel applies to
  const VariableValue & _c_i; // Syntax for defining the coupled concentration that this kernel applies to

  std::vector<const MaterialProperty<T> *> _dmobdarg;
};

template <typename T>
SplitCHWResBasePrim<T>::SplitCHWResBasePrim(const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapKernelInterface<Kernel>>(parameters),
  //: SplitCHBase(parameters),
    _mob_name(getParam<MaterialPropertyName>("mob_name")),
    _mob(getMaterialProperty<T>("mob_name")),
    _c_i_var(coupled("c_i")), // Syntax for defining the coupled concentration that this kernel applies to
    _c_i(coupledValue("c_i")) // Syntax for defining the coupled concentration that this kernel applies to
{
  // Get number of coupled variables
  unsigned int nvar = _coupled_moose_vars.size();

  // reserve space for derivatives
  _dmobdarg.resize(nvar);

  // Iterate over all coupled variables
  for (unsigned int i = 0; i < nvar; ++i)
    _dmobdarg[i] = &getMaterialPropertyDerivative<T>(_mob_name, _coupled_moose_vars[i]->name());
}

template <typename T>
Real
SplitCHWResBasePrim<T>::computeQpResidual()
{
  return _mob[_qp] * (1.0 - _c_i[_qp]) * _grad_u[_qp] * _grad_test[_i][_qp]; // Form of the residual for M(1-c_i)*grad(mu_i)*grad(test). grad(mu_i) is the gradient of the variational derivative of F wrt c_1
}

template <typename T>
Real
SplitCHWResBasePrim<T>::computeQpJacobian()
{
  return _mob[_qp] * (1.0 - _c_i[_qp]) * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}

template <typename T>
Real
SplitCHWResBasePrim<T>::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _c_i_var)
  {
    return - _mob[_qp] * _phi[_j][_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
  }
  else
  {
    // get the coupled variable jvar is referring to
    const unsigned int cvar = mapJvarToCvar(jvar);

    return (*_dmobdarg[cvar])[_qp] * _phi[_j][_qp] * (1.0 - _c_i[_qp]) * _grad_u[_qp] * _grad_test[_i][_qp];
  }
}

#endif // SPLITCHWRESBASEPRIM_H