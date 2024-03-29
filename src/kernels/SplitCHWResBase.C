//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SplitCHWResBase.h"

template <>
InputParameters
validParams<SplitCHWResBase<>>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(
      "Split formulation Cahn-Hilliard Kernel for the chemical potential variable");
  params.addParam<MaterialPropertyName>("mob_name", "mobtemp", "The mobility used with the kernel");
  params.addCoupledVar("args", "Vector of arguments of the mobility");
  params.addRequiredCoupledVar ("c_i", "Concentration of species passed in."); // Coupled concentration for this term of the residual
  params.addRequiredCoupledVar ("c_j", "Concentration of species for diffusion potential."); // Second coupled concentration for this term of the residual. Premultiplies the gradient of the variational derivative.
  params.addRequiredCoupledVar ("mu_j", "Coupled variational derivative."); // Coupled variational derivative for this term of the residual.
  //params.addCoupledVar(
  //    "w", "Coupled chemical potential (if not specified kernel variable will be used)");
  return params;
}
