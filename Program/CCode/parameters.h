struct parameters{
    float L;           // Length of tank
    float diam;        // Diameter of tank
    float Vp;          // Volume of PCM
    float Ap;          // Surface area of PCM
    float rho_p;       // Density of PCM
    float Tmelt;       // Melting temperature of PCM
    float C_ps;        // Specific heat capacity of solid PCM
    float C_pl;        // Specific heat capacity of liquid PCM
    float Hf;          // Heat of fusion for PCM
    float Ac;          // Area of coil
    float Tc;          // Temperature of coil
    float rho_w;       // Density of water
    float C_w;         // Specific heat capacity of water
    float hc;          // Heat transfer coefficient between water and coil
    float hp;          // Heat transfer coefficient between PCM and water
    float Tinit;       // Initial temperature of water and PCM
    float tstep;       // Time step for simulation
    float tfinal;      // Time at which to stop simulation
    float AbsTol;      // Absolute tolerance
    float RelTol;      // Relative tolerance
    float Vt;          // Total volume of tank, including PCM and water
    float Mw;          // Mass of water
    float tau_w;       // ODE parameter for water
    float eta;         // ODE parameter
    float Mp;          // Mass of PCM
    float tau_ps;      // ODE parameter for solid PCM
    float tau_pl;      // ODE parameter for liquid PCM
    float Epmelt_init; // Heat energy in PCM at the instant when melting begins
    float Ep_melt3;    // Heat energy change in PCM from melting start to completion
    float Mw_noPCM;    // Mass of water if no PCM is present
    float tau_w_noPCM; // ODE parameter for water if no PCM is present
};


