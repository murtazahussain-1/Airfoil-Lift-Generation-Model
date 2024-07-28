#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <uxhw.h>

/**
 *  Title: Airfoil Lift Modelling & Analysis using Signaloid's Cloud Platform
 *
 *  Overview: In this project, a model of lift force applied on an airfoil is made
 *            using Lift Equation
 *
 *  Equations:
 *  F_lift = 0.5 * Cl * ρ * pow(v, 2) * A
 *  
 *  ===== Inputs =====
 *  | Symbol  | Meaning                       | Value Range             |
 *  | ρ       | Air Density                   | 0.0316 - 1.2256 kg/m^3  |
 *  | g       | Acceleration due to gravity   | 9.80665 m/s^2 (Constant)|
 *  | v       | Velocity                      | 0 - 330 m/s             |
 *  | Cl      | Lift coefficient              | 1.2 - 3.3               | 
 *  | A       | Area of airfoil               | 51.18 - 817 m^2         |
 *  | m       | Mass of an airplane           | 85000 - 220100 kg       |
 *
 *  ===== Outputs =====
 *  | Symbol           | Meaning                                    |
 *  | F_lift           | Lift Force on an airfoil (N)               |
 *  | F_lift_adjusted  | Lift force accounting both the airfoils and the mass of the airplane (N) |
 *
 */

static const double g = 9.80665;

static void load_values(double *rho, double *v, double *Cl, double *A, double *m)
{
    double empirical_dist_Cl[] = {
        1.2, 1.8, 1.4, 2.0, 1.6, 2.5, 1.5, 1.9, 1.7, 2.1, 1.9, 3.3,
        1.4, 1.8, 1.6, 2.2, 1.6, 2.6, 1.2, 1.8, 1.6, 2.2, 1.8, 3.2,
        1.2, 1.8, 1.4, 2.0, 1.6, 2.2, 1.2, 1.8, 1.4, 2.0, 1.6, 2.6
    };

    double empirical_dist_area[] = {
        51.18, 54.54, 77.3, 91.04, 92.97, 92.97, 93.5, 112.3, 122.4, 124.6,
        157.9, 185.25, 219, 260, 271.9, 283.3, 283.4, 338.9, 363.1, 367.7,
        427.8, 437.3, 511, 525, 543, 817
    };

    // Air density should follow the gaussian distribution
    *rho = UxHwDoubleGaussDist(0.597, 0.199);
    printf("rho (kg/m³) = %lf\n", *rho);

    // v should slightly be higher, in order to accommodate the mass of the airplane
    *v  = UxHwDoubleGaussDist(165, 55);
    printf("v (m/s) = %lf\n", *v);

    // Using empirical distribution for lift coefficient
    *Cl = UxHwDoubleDistFromSamples(empirical_dist_Cl, sizeof(empirical_dist_Cl)/sizeof(double));
    printf("Cl = %lf\n", *Cl);

    // Using empirical distribution for area of the airfoil
    *A = UxHwDoubleDistFromSamples(empirical_dist_area, sizeof(empirical_dist_area)/sizeof(double));
    printf("A (m^2) = %lf\n", *A);

    // Mass of an airplane can vary drastically, hence using uniform distribution
    *m = UxHwDoubleUniformDist(85000, 220100);
    printf("m (kg) = %lf\n", *m);
}

int main(void)
{
    printf("Model using Lift equation (Plane Method)\n");

    double rho, v, Cl, A, m;

    // Loading values into our input variables
    load_values(&rho, &v, &Cl, &A, &m);

    // Lift force on a single airfoil
    double F_lift = 0.5 * Cl * rho * pow(v, 2) * A;
    printf("F_lift (N) = %lf\n", F_lift);

    // Lift force accounting both the airfoils and the mass of the airplane
    double F_lift_adjusted = (2 * F_lift) - (m * g);

    if (F_lift_adjusted > 0)
    {
        printf("Elevation level is increasing\n");
    }
    else if (F_lift_adjusted < 0)
    {
        printf("Elevation level is decreasing\n");
    }
    else // In case if F_lift_adjusted == 0
    {
        printf("Airplane is not changing elevation level\n");
    }

    printf("F_lift subtracting the weight of the airplane (N) = %lf\n", F_lift_adjusted);

    return 0;
}
