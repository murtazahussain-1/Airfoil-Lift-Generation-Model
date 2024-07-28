#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <uxhw.h>

/**
 *  Title: Airfoil Lift Modelling & Analysis using Signaloid's Cloud Platform
 *
 *  Overview: In this project, a model of lift force applied on an airfoil is made
 *            using Bernoulli's Equation
 *
 *  Equations: 
 *  (P1 - P2) = { (ρ/2)⋅{pow(v2, 2) - pow(v1, 2)} + (ρ⋅g)⋅(h2-h1) }  
 *  F_lift = A ⋅ { (ρ/2)⋅{pow(v2, 2) - pow(v1, 2)} + (ρ⋅g)⋅(h2-h1) }
 *
 *  ===== Inputs =====
 *  Symbol      Meaning                         Value Range
 *  ρ           Air Density                     0.0316 - 1.2256 kg/m^3
 *  g           Acceleration due to gravity     9.80665 m/s^2 (Constant)
 *  v1          Velocity Below the Airfoil      0 - 265 m/s
 *  v2          Velocity on upper surface Airfoil   0 - 330 m/s
 *  h2 - h1     Thickness of the airfoil        0.84 - 1.8 m
 *  A           Area of airfoil                 51.18 - 817 m^2
 *  m           Mass of an airplane             85000 - 220100 kg
 *
 *  ===== Outputs =====
 *  Symbol          Meaning
 *  P1 - P2         Difference of pressure between both surfaces of an airfoil (N / m^2)
 *  F_lift          Lift Force on an airfoil (N)
 *  F_lift_adjusted Lift force accounting both the airfoils and the mass of the airplane (N)
 *
 */

static const double g = 9.80665;

static void load_values(double *rho, double *v1, double *v2, double *h2_h1_airfoil_thickness, double *A, double *m)
{
    double empirical_dist_area[] = {
        51.18, 54.54, 77.3, 91.04, 92.97, 92.97, 93.5, 112.3, 122.4, 124.6,
        157.9, 185.25, 219, 260, 271.9, 283.3, 283.4, 338.9, 363.1, 367.7,
        427.8, 437.3, 511, 525, 543, 817
    };

    // Air density should follow the gaussian distribution
    *rho = UxHwDoubleGaussDist(0.597, 0.199);
    printf("rho (kg/m³) = %lf\n", *rho);

    // v1 and v2 usually center around the mean value hence using Gaussian
    *v1  = UxHwDoubleGaussDist(132.5, 44.16666);
    printf("v1 (m/s) = %lf\n", *v1);

    // v2 should slightly be higher, in order to accommodate the mass of the airplane
    *v2  = UxHwDoubleGaussDist(165, 55);
    printf("v2 (m/s) = %lf\n", *v2);

    // Airfoil thickness can vary drastically, hence using uniform distribution
    *h2_h1_airfoil_thickness = UxHwDoubleUniformDist(0.84, 1.8);
    printf("h2-h1 (m) = %lf\n", *h2_h1_airfoil_thickness);

    // Using empirical distribution for area of the airfoil
    *A = UxHwDoubleDistFromSamples(empirical_dist_area, sizeof(empirical_dist_area)/sizeof(double));
    printf("A (m^2) = %lf\n", *A);

    // Mass of an airplane can vary drastically, hence using uniform distribution
    *m = UxHwDoubleUniformDist(85000, 220100);
    printf("m (kg) = %lf\n", *m);
}

int main(void)
{
    printf("Model using Bernoulli's principle\n");

    double rho, v1, v2, h2_h1_airfoil_thickness, A, m;

    // Loading values into our input variables
    load_values(&rho, &v1, &v2, &h2_h1_airfoil_thickness, &A, &m);

    // Pressure difference between both the surfaces of a single airfoil
    double P1_P2_difference = ((rho / 2) * (pow(v2, 2) - pow(v1, 2)) + (rho * g) * (h2_h1_airfoil_thickness));
    printf("P1 - P2 (N/m^2) = %lf\n", P1_P2_difference);
    
    // Lift force on a single airfoil
    double F_lift = A * P1_P2_difference;
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
