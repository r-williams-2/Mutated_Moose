//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SplitCHParsed.h"

registerMooseObject("PhaseFieldApp", SplitCHParsed);

template <>
InputParameters
validParams<SplitCHParsed>()
{
  InputParameters params = validParams<SplitCHCRes>();
  params.addClassDescription(
      "Split formulation Cahn-Hilliard Kernel that uses a DerivativeMaterial Free Energy");
  //params.addRequiredCoupledVar("w", "chem poten");
  //params.addRequiredCoupledVar("c_j", "coupled concentrations");
  params.addRequiredParam<MaterialPropertyName>(
      "f_name", "Base name of the free energy function F defined in a DerivativeParsedMaterial");
  params.addCoupledVar("args", "Vector of additional arguments to F");
  return params;
}

SplitCHParsed::SplitCHParsed(const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapKernelInterface<SplitCHCRes>>(parameters),
    _nvar(_coupled_moose_vars.size()),
    _dFdc(getMaterialPropertyDerivative<Real>("f_name", _var.name())),
    _d2Fdc2(getMaterialPropertyDerivative<Real>("f_name", _var.name(), _var.name()))//,
    //_w_var(coupled("w")),
    //_w(coupledValue("w")),
    //_c_j_var(coupled("c_j")),
    //_c_j(coupledValue("c_j"))
{
  // reserve space for derivatives
  _d2Fdcdarg.resize(_nvar);

  // Iterate over all coupled variables
  for (unsigned int i = 0; i < _nvar; ++i)
    _d2Fdcdarg[i] =
        &getMaterialPropertyDerivative<Real>("f_name", _var.name(), _coupled_moose_vars[i]->name());
}

void
SplitCHParsed::initialSetup()
{
  /**
   * We are only interested if the necessary non-linear variables are coupled,
   * as those are thge ones used in constructing the Jacobian. The AuxVariables
   * do not have Jacobian entries.
   */
  validateNonlinearCoupling<Real>("f_name", _var.name());
  validateDerivativeMaterialPropertyBase<Real>("f_name");
}

Real
SplitCHParsed::computeDFDC(PFFunctionType type)
{
  switch (type)
  {
    case Residual:
      return _dFdc[_qp];

    case Jacobian:
      return _d2Fdc2[_qp] * _phi[_j][_qp];
  }

  mooseError("Internal error");
}

Real
SplitCHParsed::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _w_var)
  {
    return SplitCHCRes::computeQpOffDiagJacobian(jvar);
  }
  else if (jvar == _c_j_var)
  {
    const unsigned int cvar = mapJvarToCvar(jvar);

    return SplitCHCRes::computeQpOffDiagJacobian(jvar) + (*_d2Fdcdarg[cvar])[_qp] * _phi[_j][_qp] * _test[_i][_qp];
  }
  else
  {
    // get the coupled variable jvar is referring to
    const unsigned int cvar = mapJvarToCvar(jvar);

    return (*_d2Fdcdarg[cvar])[_qp] * _phi[_j][_qp] * _test[_i][_qp];
  }
}
