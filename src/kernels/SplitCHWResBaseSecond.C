//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SplitCHWResBaseSecond.h"

template <>
InputParameters
validParams<SplitCHWResBaseSecond<>>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(
      "Split formulation Cahn-Hilliard Kernel for the chemical potential variable");
  params.addParam<MaterialPropertyName>("mob_name", "mobtemp", "The mobility used with the kernel");
  params.addCoupledVar("args", "Vector of arguments of the mobility");
  params.addRequiredCoupledVar ("c_i", "Concentration of species for diffusion coefficient."); // First coupled concentration for this term of the residual. This is with the provision of M(c_i).
  params.addRequiredCoupledVar ("c_j", "Concentration of species for diffusion potential."); // Second coupled concentration for this term of the residual. Premultiplies the gradient of the variational derivative.
  return params;
}
