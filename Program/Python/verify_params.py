import math
import warnings


def verify_valid(params):
    # Check that inputs are valid

    if params.L <= 0:
        raise ValueError('Tank length must be > 0\n')
    elif params.diam <= 0:
        raise ValueError('Tank diameter must be > 0\n')
    elif params.Vp <= 0:
        raise ValueError('PCM volume must be > 0\n')
    elif params.Vp >= params.Vt:
        raise ValueError('PCM volume must be < tank volume\n')
    elif params.Ap <= 0:
        raise ValueError('PCM area must be > 0\n')
    elif params.rho_p <= 0:
        raise ValueError('rho_p must be > 0\n')
    elif params.Tmelt <= 0 or params.Tmelt >= params.Tc:
        raise ValueError('Tmelt must be > 0 and < Tc\n')
    elif params.Tc <= params.Tinit:
        raise ValueError('Tc must be > Tinit\n')
    elif params.Tc >= 100 or params.Tc <= 0:
        raise ValueError('Tc must be > 0 and < 100\n')
    elif params.C_ps <= 0:
        raise ValueError('C_ps must be > 0\n')
    elif params.C_pl <= 0:
        raise ValueError('C_pl must be > 0\n')
    elif params.Hf <= 0:
        raise ValueError('Hf must be > 0\n')
    elif params.Ac <= 0:
        raise ValueError('Ac must be > 0\n')
    elif params.rho_w <= 0:
        raise ValueError('rho_w must be > 0\n')
    elif params.C_w <= 0:
        raise ValueError('C_w must be > 0\n')
    elif params.hc <= 0:
        raise ValueError('hc must be > 0\n')
    elif params.hp <= 0:
        raise ValueError('hp must be > 0\n')
    elif params.Tinit <= 0 or params.Tinit >= 100:
        raise ValueError('Tinit must be > 0 and < 100\n')
    elif params.tfinal <= 0:
        raise ValueError('tfinal must be > 0\n')
    elif params.Tinit >= params.Tmelt:
        raise ValueError('Tinit must be < Tmelt\n')


def verify_recommended(params):
    # Software Constraints

    if params.L < 0.1 or params.L > 50:
        warnings.warn('It is recommended that 0.1 <= L <= 50\n')
    if params.diam / params.L < 0.002 or params.diam / params.L > 200:
        warnings.warn('It is recommended that 0.002 <= D/L <= 200\n')
    if params.Vp < 1e-6 * params.Vt:
        warnings.warn('It is recommended that Vp be >= 0.0001% of Vt\n')
    if params.Vp > params.Ap or params.Ap > (2 / 0.001) * params.Vp:
        warnings.warn('It is recommended that Vp <= Ap <= (2/0.001) * Vp\n')
    if params.rho_p <= 500 or params.rho_p >= 20000:
        warnings.warn('It is recommended that 500 < rho_p < 20000\n')
    if params.C_ps <= 100 or params.C_ps >= 4000:
        warnings.warn('It is recommended that 100 < C_ps < 4000\n')
    if params.C_pl <= 100 or params.C_pl >= 5000:
        warnings.warn('It is recommended that 100 < C_pl < 5000\n')
    # if params.Hf <= ADD WHEN DECIDED:
        # warning.warn()
    if params.Ac > math.pi * (params.diam / 2) ** 2:
        warnings.warn('It is recommended that Ac <= pi * (D/2) ^ 2\n')
    if params.rho_w <= 950 or params.rho_w > 1000:
        warnings.warn('It is recommended that 950 < rho_w <= 1000\n')
    if params.C_w <= 4170 or params.C_w >= 4210:
        warnings.warn('It is recommended that 4170 < C_w < 4210\n')
    if params.hc <= 10 or params.hc >= 10000:
        warnings.warn('It is recommended that 10 < hc < 10000\n')
    if params.hp <= 10 or params.hp >= 10000:
        warnings.warn('It is recommended that 10 < hp < 10000\n')
    if params.tfinal <= 0 or params.tfinal >= 86400:
        warnings.warn('It is recommended that 0 < tfinal < 86400\n')
