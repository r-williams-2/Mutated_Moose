//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef SPLITCHWRESSECOND_H
#define SPLITCHWRESSECOND_H

#include "SplitCHWResBaseSecond.h"

/**
 * SplitCHWRes creates the residual for the chemical
 * potential in the split form of the Cahn-Hilliard
 * equation with a scalar (isotropic) mobility.
 * Primary and secondary versions of this residual
 * were constructed as the original variational
 * derivative is now the difference of the different
 * variational derivatives.
 */
class SplitCHWResSecond : public SplitCHWResBaseSecond<Real>// Public access to functions defined in new SplitCHWResBaseSecond
{
public:
  SplitCHWResSecond(const InputParameters & parameters);
};

template <>
InputParameters validParams<SplitCHWResSecond>();

#endif // SPLITCHWRESSECOND_H
