#
# Modified CH according to Cogswell and Carter (2011).
#

[Mesh]
  type = GeneratedMesh
  dim = 2
  elem_type = QUAD4
  nx = 5#100
  ny = 5#100
  nz = 0
  xmin = 0
  xmax = 25.0e-9
  ymin = 0
  ymax = 25.0e-9
  zmin = 0
  zmax = 0
  uniform_refine = 2
  # type = GeneratedMesh
  # dim = 1
  # elem_type = EDGE2#QUAD4
  # nx = 1000
  # ny = 0
  # nz = 0
  # xmin = 0
  # xmax = 100
  # ymin = 0
  # ymax = 0
  # zmin = 0
  # zmax = 0
  # uniform_refine = 2
[]

[Variables]
  #[./T]   # Temperature
  #  order = FIRST
  #  family = LAGRANGE
  #[../]
  [./c1]   # Mole fraction of species 1 (unitless)
    order = FIRST
    family = LAGRANGE
    # scaling = 1e-12
  [../]
  [./c2]   # Mole fraction of species 2 (unitless)
    order = FIRST
    family = LAGRANGE
    # scaling = 1e-12
  [../]
  [./mu1]   # Variational derivative for diffusion of species 1. Maybe in eV/mol
    order = FIRST
    family = LAGRANGE
    # scaling = 1.0e32
  [../]
  [./mu2]   # Variational derivative for diffusion of species 1. Maybe in eV/mol
    order = FIRST
    family = LAGRANGE
    # scaling = 1.0e32
  [../]
[]

[AuxVariables]
  [./c3]
    order = FIRST
    family = MONOMIAL
  [../]
  [./T]
    order = FIRST
    family = MONOMIAL
  [../]
  [./ctot]
    order = FIRST
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./c3]
    type = ParsedAux
    args = 'c1 c2'
    execute_on = timestep_end
    variable = c3
    function = '1-c1-c2'
  [../]
  [./ctot]
    type = ParsedAux
    args = 'c1 c2 c3'
    execute_on = timestep_end
    variable = ctot
    function = 'c1+c2+c3'
  [../]
[]

#NEEDS CHANGED
[ICs]
  [./c1IC]   # 46.774 mol% with variations
    # type = RandomIC
    # min = 0.45
    # max = 0.50
    # seed = 25
    # variable = c1
    # type = BoundingBoxIC
    # x1 = 5.0
    # x2 = 20.0
    # y1 = 11.0
    # y2 = 14.0
    # variable = c1
    # inside = 0.6
    # outside = 0.3
    # type = RampIC
    # variable = c1
    # value_left = 0.6
    # value_right = 0.3
    type = MultiBoundingBoxIC
    # corners = '11.0 11.0 0   5.0 11.0 0   14.0 11.0 0   0.0 14.0 0   0.0 0.0 0   0.0 11.0 0   20.0 11.0 0'
    # opposite_corners = '14.0 14.0 0   11.0 14.0 0   20.0 14.0 0   25.0 25.0 0   25.0 11.0 0   5.0 14.0 0   25.0 14.0 0'
    # inside = '0.6   0.3   0.3   0.3   0.3   0.3   0.3'
    corners = '11.0e-9 11.0e-9 0   5.0e-9 11.0e-9 0   14.0e-9 11.0e-9 0   0.0e-9 14.0e-9 0   0.0 0.0 0   0.0 11.0e-9 0   20.0e-9 11.0e-9 0'
    opposite_corners = '14.0e-9 14.0e-9 0   11.0e-9 14.0e-9 0   20.0e-9 14.0e-9 0   25.0e-9 25.0e-9 0   25.0e-9 11.0e-9 0   5.0e-9 14.0e-9 0   25.0e-9 14.0e-9 0'
    inside = '0.6   0.3   0.3   0.3   0.3   0.3   0.3'
    #outside = 0.1
    variable = c1

  [../]
  [./c2IC]   # 25.0 mol% with variations
    # type = RandomIC
    # min = 0.22
    # max = 0.28
    # seed = 30
    # variable = c2
    # type = BoundingBoxIC
    # x1 = 11.0
    # x2 = 14.0
    # y1 = 11.0
    # y2 = 14.0
    # variable = c2
    # inside = 0.3
    # outside = 0.6
    # type = RampIC
    # variable = c2
    # value_left = 0.3
    # value_right = 0.2
    # type = SmoothCircleIC
    # variable = c2
    # invalue = 0.3
    # radius = 1.5
    # outvalue = 0.6
    # x1 = 12.5
    # y1 = 12.5
    type = MultiBoundingBoxIC
    # corners = '11.0 11.0 0   5.0 11.0 0   14.0 11.0 0   0.0 14.0 0   0.0 0.0 0   0.0 11.0 0   20.0 11.0 0'
    # opposite_corners = '14.0 14.0 0   11.0 14.0 0   20.0 14.0 0   25.0 25.0 0   25.0 11.0 0   5.0 14.0 0   25.0 14.0 0'
    # inside = '0.3   0.6   0.6   0.3   0.3   0.3   0.3'
    corners = '11.0e-9 11.0e-9 0   5.0e-9 11.0e-9 0   14.0e-9 11.0e-9 0   0.0 14.0e-9 0   0.0 0.0 0   0.0 11.0e-9 0   20.0e-9 11.0e-9 0'
    opposite_corners = '14.0e-9 14.0e-9 0   11.0e-9 14.0e-9 0   20.0e-9 14.0e-9 0   25.0e-9 25.0e-9 0   25.0e-9 11.0e-9 0   5.0e-9 14.0e-9 0   25.0e-9 14.0e-9 0'
    inside = '0.3   0.6   0.6   0.3   0.3   0.3   0.3'
    #outside = 0.1
    variable = c2
  [../]
  [./TIC]   # Temperature IC
    type = ConstantIC
    variable = T
    value = 1000.0
  [../]
[]

[BCs]
  # periodic BC as is usually done on phase-field models
  [./Periodic]
    [./cx_bcs]
      auto_direction = 'x y'
    [../]
  [../]
[]

[Kernels]
  [./c1_dot]
    variable = mu1
    v = c1
    type = CoupledTimeDerivative
  [../]
  [./coupled_res_c1_Prim]
    variable = mu1
    type = SplitCHWRes#Prim
    mob_name = M
    c_i = c1
    c_j = c2
    mu_j = mu2
  [../]
  # [./coupled_res_c1_Second]
  #   variable = mu1
  #   type = SplitCHWResSecond
  #   mob_name = M
  #   c_i = c1
  #   c_j = c2
  #   mu_j = mu2
  # [../]
  [./coupled_parsed_c1]
    variable = c1
    type = SplitCHParsed
    f_name = f_loc
    kappa_name = kappa_c
    mols_in_sys = sys_mols
    w = mu1
    c_j = c2
  [../]
  [./c2_dot]
    variable = mu2
    v = c2
    type = CoupledTimeDerivative
  [../]
  [./coupled_res_c2_Prim]
    variable = mu2
    type = SplitCHWRes#Prim
    mob_name = M
    c_i = c2
    c_j = c1
    mu_j = mu1
  [../]
  # [./coupled_res_c2_Second]
  #   variable = mu2
  #   type = SplitCHWResSecond
  #   mob_name = M
  #   c_i = c2
  #   c_j = c1
  #   mu_j = mu1
  # [../]
  [./coupled_parsed_c2]
    variable = c2
    type = SplitCHParsed
    f_name = f_loc
    kappa_name = kappa_c
    mols_in_sys = sys_mols
    c_j = c1
    w = mu2
  [../]
[]

#NEEDS CHANGED
[Materials]
  # d is a scaling factor that makes it easier for the solution to converge
  # without changing the results. It is defined in each of the materials and
  # must have the same value in each one.
  [./constants]
    # Define constant values kappa_c and M. Eventually M will be replaced with
    # an equation rather than a constant.
    type = GenericFunctionMaterial
    prop_names = 'kappa_c M sys_mols'
    # REALISTIC PROPS
    prop_values = ' 6.6512e-8
                    (1.0e-8)*0.5/(8314.0*1000.0)
                    (1.0e-9)*(25.0e-9)*(25.0e-9)/(1.0e-5)'
    # prop_values = ' 6.6512e-8*1e-30
    #                 ((1.0e-8)*((1.0e+9)^2)*0.5/(6.242e+18*8314.0*1000.0))/1e-30
    #                 (1.0)*(25.0)*(25.0)/(1.0e+22)'
    # prop_values = '6.6512e-9
    #                (1.0*10.0^-8)*0.5/(8314.0*1000.0)
    #                1.0'
    # prop_values = '6.512e-2
    #                (1.0*10.0^-2)*0.5/(8314.0*1000.0)
    #                1.0'
    # prop_values = '6.6512*10^(-17.0)
    #                10.0^(10.0)*0.46774/(8314.0*1000.0)
    #                25.0*25.0/(10.0^(22.0))'#x1*x2*(c1/Vm1+c2/Vm2+(1-c1-c2)/vm3)'
                   # kappa_c*eV_J*nm_m^2*d
                   # M*nm_m^2/eV_J/d
    # prop_values = '6.512e-2
    #                (1.0*10.0^-2)*0.5/(8314.0*1000.0)
    #                1.0'
  [../]
  [./local_energy]
    # Defines the function for the local free energy density as given in the
    # problem, then converts units and adds scaling factor.
    type = DerivativeParsedMaterial
    f_name = f_loc
    args = 'c1   c2   T'#   c3
    # WORKING
    # constant_names = 'n   Omega12   Omega13   Omega23   R'
    # constant_expressions = '1.0   -10.0   -10.0   -10   8.314'
    # function = '(1/n)*(Omega12*c1*c2 + Omega13*c1*c3 + Omega23*c2*c3 + R*T*(c1*log(c1) + c2*log(c2) + c3*log(c3)))'
    # constant_expressions = '25.0*25.0/(10.0^22.0)   -10.0*8314.0   -10.0*8314.0   -10.0*8314.0   8314.0'
    # function = '(1/n)*(Omega12*c1*c2 + Omega13*c1*c3 + Omega23*c2*c3 + R*T*(c1*log(c1) + c2*log(c2) + c3*log(c3)))'
    # WORKING
    # constant_expressions = '1.0   -10.0*8314.0   -10.0*8314.0   -10.0*8314.0   8314.0'
    # function = '(1/n)*(Omega12*c1*c2 + Omega13*c1*c3 + Omega23*c2*c3 + R*T*(c1*log(c1) + c2*log(c2) + c3*log(c3)))'
    # NOT WORKING, UNNORMALISED
    constant_names = 'Nmols   Omega12   Omega13   Omega23   R'
    constant_expressions = '(1.0e-9)*(25.0e-9)*(25.0e-9)/(1.0e-5)   -10.0*8314.0   -10.0*8314.0   -10.0*8314.0   8314.0'
    function = '(1.0/Nmols)*(Omega12*c1*c2 + Omega13*c1*(1.0-c1-c2) + Omega23*c2*(1.0-c1-c2) + R*T*(c1*log(c1) + c2*log(c2) + (1.0-c1-c2)*log(1.0-c1-c2)))'
    # constant_names = 'Nmols   Omega12   Omega13   Omega23   R'
    # constant_expressions = '(1.0)*(25.0)*(25.0)/(1.0e+22)   -10.0*8314.0   -10.0*8314.0   -10.0*8314.0   8314.0'
    # function = '((1e-30)*(6.242e+18)/Nmols)*(Omega12*c1*c2 + Omega13*c1*(1.0-c1-c2) + Omega23*c2*(1.0-c1-c2) + R*(c1*log(c1) + c2*log(c2) + (1.0-c1-c2)*log(1.0-c1-c2)))'
    # OTHER PROPS
    # constant_names = 'n   Omega12   Omega13   Omega23   R'
    # constant_expressions = '1.0   -10.0*8314.0   -10.0*8314.0   -10.0*8314.0   8314.0'
    # function = '(1/n)*(Omega12*c1*c2 + Omega13*c1*c3 + Omega23*c2*c3 + R*T*(c1*log(c1) + c2*log(c2) + c3*log(c3)))'

    derivative_order = 2
  [../]
[]

[Postprocessors]
  [./step_size]             # Size of the time step
    type = TimestepSize
  [../]
  [./iterations]            # Number of iterations needed to converge timestep
    type = NumNonlinearIterations
  [../]
  [./nodes]                 # Number of nodes in mesh
    type = NumNodes
  [../]
  [./evaluations]           # Cumulative residual calculations for simulation
    type = NumResidualEvaluations
  [../]
  [./active_time]           # Time computer spent on simulation
    type = PerformanceData
    event =  ALIVE#ACTIVE
  [../]
[]

# # [Preconditioning]
# #   # [./coupled]
# #   #   type = SMP
# #   #   full = true
# #   # [../]
# #   # [./FDP]
# #   #   type = FDP
# #   #   full = true
# #   # [../]
# # []

# [Executioner]
#   type = Transient
#   solve_type = NEWTON#PJFNK
#   l_max_its = 100
#   l_tol = 1e-6
#   nl_max_its = 50
#   nl_rel_tol = 1e-8
#   # nl_abs_tol = 1e-9
#   # line_search = none
#   end_time = 600.0#7200   # seconds
#   petsc_options = '-ksp_converged_reason -ksp_monitor_true_residual -snes_converged_reason -snes_linesearch_monitor' #-snes_check_jacobian -pc_svd_monitor -snes_check_jacobian_view -snes_view -log_view    -snes_fd - -snes_error_if_not_converged -ksp_error_if_not_converged'
#   petsc_options_iname = '-snes_linesearch_type -pc_type'#-pc_factor_mat_solver_package
#   petsc_options_value = 'basic lu'#svd lu mumps
#   # petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_ksp_type
#   #                        -sub_pc_type -pc_asm_overlap'
#   # petsc_options_value = 'asm      31                  preonly
#   #                        ilu          1'
#   [./TimeStepper]
#     type = IterationAdaptiveDT
#     dt = 0.1
#     cutback_factor = 0.7
#     growth_factor = 1.5
#     optimal_iterations = 15
#   [../]
#   [./Adaptivity]
#     coarsen_fraction = 0.1
#     refine_fraction = 0.7
#     max_h_level = 2
#   [../]
# []

# [Debug]
#   show_var_residual_norms = true
# []

# [Outputs]
#   exodus = true
#   console = true
#   # csv = true
#   [./console]
#     type = Console
#     max_rows = 10
#   [../]
# []

[Preconditioning]
  [./coupled]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  solve_type = NEWTON#PJFNK
  l_max_its = 30
  l_tol = 1e-6
  nl_max_its = 50
  # nl_abs_tol = 1e-9
  nl_rel_tol = 1e-3
  end_time = 600.0   # seconds.
  automatic_scaling = true
  # petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_ksp_type
  #                        -sub_pc_type -pc_asm_overlap'
  # petsc_options_value = 'asm      31                  preonly
  #                        ilu          1'
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 0.1
    cutback_factor = 0.7
    growth_factor = 1.5
    optimal_iterations = 15
  [../]
  [./Adaptivity]
    coarsen_fraction = 0.1
    refine_fraction = 0.7
    max_h_level = 2
  [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  exodus = true
  console = true
  #csv = true
  [./console]
    type = Console
    max_rows = 10
  [../]
[]