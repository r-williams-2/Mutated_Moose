//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SplitCHWResSecond.h"

/**
 * Primary and secondary versions of this residual
 * were constructed as the original variational
 * derivative is now the difference of the different
 * variational derivatives.
 */

registerMooseObject("PhaseFieldApp", SplitCHWResSecond);

template <>
InputParameters
validParams<SplitCHWResSecond>()
{
  InputParameters params = validParams<SplitCHWResBaseSecond<>>();
  params.addClassDescription("Split formulation Cahn-Hilliard Kernel for the chemical potential "
                             "variable with a scalar (isotropic) mobility");
    
  return params;
}

SplitCHWResSecond::SplitCHWResSecond(const InputParameters & parameters) : SplitCHWResBaseSecond<Real>(parameters) {}