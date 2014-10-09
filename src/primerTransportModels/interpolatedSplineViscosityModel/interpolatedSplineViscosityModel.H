/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original authors 
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::viscosityModels::interpolatedSplineViscosityModel

Description
     A viscosity model which takes in raw rheometry data and 
     uses splines to compute a local effective viscosity based
     on the data table.  

SourceFiles
    interpolatedSplineViscosityModel.C

Authors:
    Kyle Mooney kyle.g.mooney@gmail.com
    Jens Hoepken jens@sourceflux.de
    Tomislav Maric tomislav@sourceflux.de

\*---------------------------------------------------------------------------*/

#ifndef interpolatedSplineViscosityModel_H
#define interpolatedSplineViscosityModel_H

#include "viscosityModel.H"
#include "dimensionedScalar.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{

/*---------------------------------------------------------------------------*\
                           Class interpolatedSplineViscosityModel Declaration
\*---------------------------------------------------------------------------*/

class interpolatedSplineViscosityModel
:
    public viscosityModel
{
    // Private data

        //Dictionary for the viscosity model
        dictionary interpolatedSplineViscosityModelCoeffs_;

        //x and y entries of the rheology data for
        //   use with the spline interpolator
        scalarField rheologyTableX_;
        scalarField rheologyTableY_;

        word dataFileName_;
        volVectorField U_;
        volScalarField nu_;


    // Private Member Functions

        //- Calculate and return the laminar viscosity
        volScalarField calcNu();


        //load the viscosity data table
        void loadDataTable();

public:

    //- Runtime type information
    TypeName("interpolatedSplineViscosityModel");


    // Constructors

        //- Construct from components
        interpolatedSplineViscosityModel
        (
            const word& name,
            const dictionary& viscosityProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    ~interpolatedSplineViscosityModel()
    {}


    // Member Functions

        //- Return the laminar viscosity
        tmp<volScalarField> nu() const
        {
            return nu_;
        }

        tmp<scalarField> nu(const label patchi) const 
        {
            notImplemented("interpolatedSplineViscosityModel::nu(const label) - port to 2.3.x"); 
            return tmp<scalarField>();
        };

        //- Correct the laminar viscosity
        void correct()
        {
            nu_ = calcNu();
        }

        //- Read transportProperties dictionary
        bool read(const dictionary& viscosityProperties);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace viscosityModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
