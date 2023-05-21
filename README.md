[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-light-mode-only)

# Airfoil Lift Modelling & Analysis using Signaloid's Cloud Platform
In this project, I have created models of lift of an airfoil using equations of fluid dynamics and analyzed it by inserting uncertainties in various variables using Signaloid's cloud platform and probability distribution methodologies.

![image](https://github.com/murtazahussain-1/Airfoil-Lift-Generation-Model/assets/118768714/79308d0d-4ace-4917-8218-50e5d44d76cc)

# Introduction
There are three main methods in fluid dynamics, by which we can analyze the lift of an airfoil.

* Using the Bernoulli's equation [^1]
* Using the Panel Method (Lift Equation) [^2] [^3]
* Using Navier Stokes Equations [^4]

To keep things simple, I will be avoiding Navier Stokes Equations, because using them can be a complicated process. Instead, I will be following the first two methods to model the lift. Not only they are simple to understand, but they also cater in a decent amount of variables.

## Model using Bernoulli's equation
In the heart of Bernoulli's Equation, the lift of an airfoil depends on the difference between the pressure below the airfoil (P1) and pressure above the airfoil (P2).

| Relationship between P1 & P2 | Lift |
| ----------------- | ------------------------------------------------------------------ |
| P1 > P2 | Lift would be upwards |
| P1 = P2 | No lift |
| P1 < P2 | Lift would be downwards |

### Equation
![image](https://github.com/murtazahussain-1/Airfoil-Lift-Generation-Model/assets/118768714/3aa53adb-193e-4ef0-9db7-8c85f4ae2db7)

#### Inputs
| Symbol | Meaning | Value Range |
| ------ | ------- |------- |
| ρ | Air Density | 0.0316 - 1.2256 kg/m^3 |
| g | Acceleration due to gravity | 9.80665 m/s^2 (Constant) |
| v1 | Velocity Below the Airfoil | 0 - 265 m/s |
| v2 | Velocity on upper surface Airfoil | 0 - 330 m/s |
| h2 - h1 | Thickness of the airfoil | 0.84 - 1.8 m |
| A | Area of airfoil | 51.18 - 817 m^2|
| m | Mass of an airplane | 85000 - 220100 kg |

• `ρ`: For air density, I used an online calculator [^5]. I kept the Temperature of air constant at 15 Celsius, humidity at 40%, atmospheric pressure at 29.9200 psi. I only changed the altitude from 0 ft to 42,000 ft, which is the maximum height a commercial airplane is allowed. Of course, in reality, all these parameters change with altitude, but to keep things simple, I made the air Density only dependent on the altitude

• `g`:  Acceleration due to gravity[^6] is around 9.80665 m/s^2. Although, it slightly varies with altitude from the center of the Earth, but the change is so small that it can be kept constant

• `v1` and `v2`: For commercial airplanes speeds can reach upto 737 mph or ~330 m/s. v1 is kept slightly smaller in order to accomodate the mass of the airplane [^7]

• `h2 - h1`: After looking at various online resources. The thickness of an airfoil can range from 0.84 to 1.8 meters

• `A`: Area of the airfoil of most commercial aircrafts range from 51.18 meters to 817 meters [^8]

• `m`: After looking through muliple online resources. Mass of an airplane[^9] can range from 85000 - 220100 kg. Although, private jets can have a mass even lower than 85,000 kg

#### Outputs
| Symbol | Meaning |
| ------ | ------- |
| P1 - P2 | Difference of pressure between both surfaces of an airfoil (N / m^2) |
| F_lift | Lift Force on an airfoil (N) |
| F_lift_adjusted | Lift force accounting both the airfoils and the mass of the airplane (N) |

#### Simplifying the equation to get the airlift:
```             
           ρ ⋅ pow(v2, 2)                    ρ ⋅ pow(v1, 2)
P1 - P2 =  ______________  + (ρ ⋅ g ⋅ h2) -  ______________ -  (ρ ⋅ g ⋅ h1)
                 2                                2      
```
```             
P1 - P2 =    (ρ/2)⋅{pow(v2, 2) - pow(v1, 2)}  +  (ρ⋅g)⋅(h2 - h1)  
```
At this point we have calculated the pressure difference between upper and lower surfaces of the airfoil. This should give us some idea about the lift on the airfoil. However, this is the pressure difference. To get the actual lift, which is the force on the airfoil, we need to multiply both sides by the Area (A) of the Airfoil

We know that:
```
P = F / A

So,

F_lift = A ⋅ (P1 - P2)
```

```
A ⋅ (P1 - P2) = A ⋅ { (ρ/2)⋅{pow(v2, 2) - pow(v1, 2)} + (ρ⋅g)⋅(h2-h1) }  
```

```
F_lift = A ⋅ { (ρ/2)⋅{pow(v2, 2) - pow(v1, 2)} + (ρ⋅g)⋅(h2-h1) }  
```

# References
[^1]: https://en.wikipedia.org/wiki/Bernoulli%27s_principle
[^2]: https://open.oregonstate.education/intermediate-fluid-mechanics/chapter/the-panel-method-an-introduction/
[^3]: https://www.grc.nasa.gov/www/k-12/rocket/lifteq.html
[^4]: https://www.grc.nasa.gov/www/k-12/airplane/nseqs.html
[^5]: https://www.engineersedge.com/calculators/air-density.htm 
[^6]: https://en.wikipedia.org/wiki/Gravitational_acceleration
[^7]: https://www.flyingmag.com/guides/how-fast-do-commerical-planes-fly/
[^8]: https://en.wikipedia.org/wiki/Thickness-to-chord_ratio
[^9]: https://euflightcompensation.com/how-much-does-a-plane-weigh/
