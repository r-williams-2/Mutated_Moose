//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "SplitCHBase.h"

// Forward Declarations
class SplitCHCRes;

template <>
InputParameters validParams<SplitCHCRes>();

/// The couple, SplitCHCRes and SplitCHWRes, splits the CH equation by replacing chemical potential with 'w'.
class SplitCHCRes : public SplitCHBase
{
public:
  SplitCHCRes(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialProperty<Real> & _kappa;
  // const MaterialProperty<Real> & _no_mols; // Material property named _no_mols
  unsigned int _w_var; // Syntax for coupled variable.
  const VariableValue & _w; // Syntax for coupled variable.
  unsigned int _c_j_var; // Syntax for coupled variable. Needed for gradient of this variable.
  const VariableValue & _c_j; // Syntax for coupled variable. Needed for gradient of this variable.
  //std::vector<const VariableGradient *> _grad_coupled;
  const VariableGradient & _grad_coupled; // Gradient of the coupled variable.
};

