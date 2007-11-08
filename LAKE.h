/******************************************************************************
// $Id$
  Modifications:
  2006-Nov-07 Removed LAKE_MODEL option.				TJB
  2007-Aug-16 Made return value of initialize_prcp an int.		JCA
  2007-Aug-21 Added features for EXCESS_ICE option.			JCA
  2007-Oct-24 Changed get_sarea, get_volume, and get_depth to return exit
	      status so that errors can be trapped and communicated up the
	      chain of function calls.					KAC via TJB
  2007-Oct-24 Changed lakeice() to return exit status.			KAC via TJB
  2007-Nov-06 New lake physics parameters.  Modified argument lists for
	      various functions.  Moved get_dist() to vicNl.h.		LCB via TJB
******************************************************************************/

//#ifndef LAKE_SET

#define LAKE_SET
#define TMELT 0.0
#define EMICE 0.97      /* Ice emissivity */
#define EMH2O .98
#define RHOSNOW   250.  /* densities of water and snow */
#define RHOICE   917.   /* ice density*/
#define rhosurf 1.275   /* surface air density */
#define MAX_SURFACE_LAKE   .6  /* max. surface layer thickness for E-B (m) */
#define BETA 0.001       /* Curve shape parameter for lake profile. */
#define FRACMIN  0.10   /* min ice thickness in meters */
#define FRACLIM   0.02  /* lower limit on fractional ice cover */
#define CPW_ICE   4200. /* specific heat of ice */
#define DM 1.38889E-07  /* molecular diffusivity of water */
#define SNOWCRIT   0.05  /* for albedo, in m */
//#define G 9.80616
#define ZWATER 0.0045    // 0.004 - original value
#define ZSNOW 0.005
#define CONDI 2.3        /* thermal conductivity of ice */
#define CONDS 0.31       /* thermal conductivity of snow */ 

// attenuation of short and longwave radiation through ice (1/m)
#define lamisw 1.5 // 1.5 in Patterson & Hamblin
#define lamilw 20  // 20.0 in Patterson & Hamblin
// attenuation of short and longwave radiation through snow (1/m)
#define lamssw 6.0 // 6.0 in Patterson & Hamblin
#define lamslw 20  // 20.0 in Patterson & Hamblin
// attenuation of short and longwave radiation through water (1/m)
#define lamwsw .3  // San Fran Bay data: 0.31 - 29.9 1/m (visible)
#define lamwlw .2 // Hostetler and Bartlein assume 0.85 1/m (total)
#define  a1 0.7        /* Percent of radiation in visible band. */
#define  a2 0.3        /* Percent of radiation in infrared band. */
#define QWTAU 86400./2.   /* D. Pollard sub-ice time constant. */
#define RADIUS 6371.228 /* Earth radius in km. */

//#endif // LAKE_SET

/*** Subroutine prototypes ***/

double adjflux(double, double, double ,double, double, double, double,
	       double, double, double, double *, double *);
void alblake(double, double, double *, double *, float *, float *, double, double, 
	     int, int *, double, double, char *);
void alloc_atmos(int, atmos_data_struct **);
double calc_density(double);
void colavg (double *, double *, double *, float, double *, int, double, double);
float dragcoeff(float, double, double);
void eddy (int, double, double * , double *, double *, double, int, double, double);
void energycalc(double *, double *, int, double, double,double *, double *, double *);
void iceform (double *,double *,double ,double,double *,int, int, double, double, double *, double *, double *, double *, double *, double);
void icerad(double,double ,double,double *, double *,double *);
int ice_depth(lake_con_struct, double, double, double *);
int initialize_lake(lake_var_struct *, lake_con_struct, snow_data_struct *, double);
int lakeice(double *, double, double, double, double, int, 
	    double, double, double *, double, double, int, dmy_struct, double *, double *, double, double);
int lakemain(atmos_data_struct *, lake_con_struct, double, double, soil_con_struct *, veg_con_struct *,
#if EXCESS_ICE
	     int, double,
#endif
	     int, dist_prcp_struct *, 
	     int, int, double, global_param_struct *, dmy_struct *, 
	     int, int);
void latsens(double,double, double, double, double, double, double, double,
	     double *, double *, double);
float lkdrag(float, double, double, double, double);
lake_con_struct read_lakeparam(FILE *, soil_con_struct, veg_con_struct *);
void rhoinit(double *, double);
int solve_lake(double, double, double, double, double, double, double, double, 
		double, double, lake_var_struct *, lake_con_struct, 
		soil_con_struct, int, int, energy_bal_struct *, 
		snow_data_struct *, double, dmy_struct, double);
double specheat (double);
void temp_area(double, double, double, double *, double *, double *, double *, int, double *, int, double, double, double*, double *, double *);
void tracer_mixer(double *, int *, int, double*, int, double, double, double *);
void tridia(int, double *, double *, double *, double *, double *);
int water_balance (lake_var_struct *, lake_con_struct, int, dist_prcp_struct *, int, int, int, double, soil_con_struct, 
#if EXCESS_ICE
		    int, double,
#endif		    
		    double, double, double, double, double);
double func_lake_energy_balance(double, va_list);
double solve_surf_energy_bal(double Tsurf, ...);
int ice_melt(double, double, double *, double, snow_data_struct *, lake_var_struct *, int, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double *, double *, double *, double *, double *, double *, double *, double *, double *, double);
double CalcIcePackEnergyBalance(double Tsurf, ...);
double func_lake_energy_bal(double , va_list);
double IceEnergyBalance(double, va_list);
double ErrorPrintIcePackEnergyBalance(double, va_list);
double ErrorIcePackEnergyBalance(double Tsurf, ...);
int  water_energy_balance(int, double*, double*, int, int, double, double, double, double, double, double, double, double, double, double, double, double, double, double *, double *, double *, double*, double *, double *, double *, double, double *, double *, double *, double *, double *, double);
int water_under_ice(int, double,  double, double *, double *, double, int, double, double, double, double *, double *, double *, double *, int, double, double, double, double *);
void write_lake_var(lake_var_struct, int);
int get_sarea(lake_con_struct, double, double *);
int get_volume(lake_con_struct, double, double *);
int get_depth(lake_con_struct, double, double *);
int wetland_energy(int, atmos_data_struct *, dist_prcp_struct *, dmy_struct *,
		   global_param_struct *, soil_con_struct  *, 
#if EXCESS_ICE
		   int,
#endif
		   int, int, double, lake_con_struct, veg_con_struct *);
void update_prcp(dist_prcp_struct *, energy_bal_struct *,  snow_data_struct *, double, lake_var_struct *, lake_con_struct, int, int, soil_con_struct);
int initialize_prcp(dist_prcp_struct *, energy_bal_struct *,  snow_data_struct *, int, int, 
		    soil_con_struct, lake_var_struct *, int, lake_con_struct, double *, double *);
