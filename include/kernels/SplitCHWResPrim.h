//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef SPLITCHWRESPRIM_H
#define SPLITCHWRESPRIM_H

#include "SplitCHWResBasePrim.h"

/**
 * SplitCHWRes creates the residual for the chemical
 * potential in the split form of the Cahn-Hilliard
 * equation with a scalar (isotropic) mobility.
 */
class SplitCHWResPrim : public SplitCHWResBasePrim<Real>//, SplitCHWResBaseSecond<Real>
{
public:
  SplitCHWResPrim(const InputParameters & parameters);
};

template <>
InputParameters validParams<SplitCHWResPrim>();

#endif // SPLITCHWRESPRIM_H
