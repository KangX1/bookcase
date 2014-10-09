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

#include "interpolatedSplineViscosityModel.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"
#include "interpolateSplineXY.H"
#include "mathematicalConstants.H"
#include "Tuple2.H"
#include "IFstream.H"
#include "volFields.H"
#include "fvcGrad.H"
// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(interpolatedSplineViscosityModel, 0);

    addToRunTimeSelectionTable
    (
        viscosityModel,
        interpolatedSplineViscosityModel,
        dictionary
    );
}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

Foam::volScalarField
Foam::viscosityModels::interpolatedSplineViscosityModel::calcNu()
{

    //open and parse the rheometry data file
    loadDataTable();

    //initialize a viscosity field to return later
    volScalarField viscosityField
    (
        IOobject
        (
            "viscosityField",
            U_.time().timeName(),
            U_.db(),
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        U_.mesh(),
        dimensionedScalar("viscosityField", dimensionSet(0,2,-1,0,0,0,0), 0.0),
        zeroGradientFvPatchScalarField::typeName
    );

    //Access the local strain rate using the private function
    const volScalarField& localStrainRate = strainRate();
        
    //Loop through all cells and calulate the effective viscosity 
    //  using the spline interpolation class
    forAll(localStrainRate.internalField(),cellI)
    {
        scalar& localMu = viscosityField.internalField()[cellI];
              
        localMu = interpolateSplineXY
        (
            localStrainRate.internalField()[cellI],
            rheologyTableX_,
            rheologyTableY_
        );  
    }

    return viscosityField;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::interpolatedSplineViscosityModel::interpolatedSplineViscosityModel
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    viscosityModel(name, viscosityProperties, U, phi),
    interpolatedSplineViscosityModelCoeffs_(viscosityProperties.subDict(typeName + "Coeffs")),
    rheologyTableX_(label(1),scalar(0)),
    rheologyTableY_(label(1),scalar(0)),
    dataFileName_(interpolatedSplineViscosityModelCoeffs_.lookup("dataFileName")),
    U_(U),
    nu_
    (
        IOobject
        (
            name,
            U_.time().timeName(),
            U_.db(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        calcNu()
    )
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::interpolatedSplineViscosityModel::read
(
    const dictionary& viscosityProperties
)
{
    viscosityModel::read(viscosityProperties);

    interpolatedSplineViscosityModelCoeffs_ = viscosityProperties.subDict(typeName + "Coeffs");
    interpolatedSplineViscosityModelCoeffs_.lookup("dataFileName") >> dataFileName_;

    return true;
}

void Foam::viscosityModels::interpolatedSplineViscosityModel::loadDataTable()
{

    fileName timeDataFileName
    (
       dataFileName_
    );

    //Lookup the rheometry data in /constant/
    IFstream dataStream("constant/"+timeDataFileName);

    //Verify and parse the table into respective members
    if (dataStream.good())
    {
        List<Tuple2<scalar, scalar> > timeValues
        (
            dataStream
        );

        rheologyTableX_.setSize(timeValues.size());
        rheologyTableY_.setSize(timeValues.size());

        forAll(timeValues, i)
        {
            rheologyTableX_[i] = timeValues[i].first();
            rheologyTableY_[i] = timeValues[i].second();
        }
    }
    else
    {
        FatalErrorIn
        (
            "viscosityModels::splineInterpolated::loadDataTable"
            "(const dictionary&)"
        )   << "Cannot open time data file " << timeDataFileName
           << exit(FatalError);
    }

}
// ************************************************************************* //
