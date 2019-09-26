//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

/**
 * Generates the necessary kernels for the Grand Potential Function for any number
 * of order parameters and chemical potentials. Can do so with two sets of order
 * parameters that use different material properties. Also able to use anisotropic
 * diffusivities for the chemical potential variables.
 *
 * KERNELS GENERATED BY THIS ACTION
 * chemical_potentials
 *  -SusceptibilityTimeDerivative
 *  -MatDiffusion (or MatAnisonDiffusion if D is a tensor)
 *  -CoupledSwitchingTimeDerivative (one for each gr and op)
 * grains
 *  -TimeDerivative
 *  -ACInterface
 *  -ACSwitching
 *  -ACGrGrMulti
 * additional_order_parameters
 *  -TimeDerivative
 *  -ACInterface
 *  -ACSwitching
 *  -ACGrGrMulti
 **/

#ifndef GRANDPOTENTIALKERNELACTION_H
#define GRANDPOTENTIALKERNELACTION_H

#include "Action.h"

class GrandPotentialKernelAction : public Action
{
public:
  GrandPotentialKernelAction(const InputParameters & parameters);

  virtual void act();
};

template <>
InputParameters validParams<GrandPotentialKernelAction>();

#endif // GRANDPOTENTIALKERNELACTION_H
