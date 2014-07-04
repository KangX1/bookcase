/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "wettedCellsFunctionObject.H"
#include "addToRunTimeSelectionTable.H"
#include "error.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(wettedCellsFunctionObject, 0);
addToRunTimeSelectionTable(functionObject, wettedCellsFunctionObject, dictionary); 


// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

wettedCellsFunctionObject::wettedCellsFunctionObject
(
    const word& name,
    const Time& time,
    const dictionary& dict
)
:
    functionObject(name),
    time_(time),
    mesh_(time.lookupObject<fvMesh>(polyMesh::defaultRegion)), 
    alpha1_
    (
        mesh_.lookupObject<volScalarField>
        (
            dict.lookup("volFractionField") 
        )
    ),
    wettedCellsPtr_
    ( 
        new volScalarField 
        (
            IOobject
            (
                "wettedCells", 
                time.timeName(), 
                time, 
                IOobject::NO_READ, 
                IOobject::AUTO_WRITE
            ), 
            mesh_,  
            dimensionedScalar
            (
                "zero", 
                dimless,
                0.0
            )
        )
    ),
    wettedTolerance_(readScalar(dict.lookup("wettedTolerance"))),
    wettedDomainPercent_(0)
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

wettedCellsFunctionObject::~wettedCellsFunctionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool wettedCellsFunctionObject::read(const dictionary& dict)
{
    notImplemented("wettedCellsFunctionObject::read(const dictionary&)"); 
    return execute(false); 
}


bool wettedCellsFunctionObject::execute(const bool forceWrite)
{
    calcWettedCells(); 
    calcWettedDomainPercent(); 
    report(); 

    if (forceWrite)
    {
        wettedCellsPtr_->write(); 
    }

    return true;
}

void wettedCellsFunctionObject::calcWettedCells()
{
    volScalarField& wettedCells_ = wettedCellsPtr_(); 

    forAll (alpha1_, I)
    {
        if (isWetted(alpha1_[I]))
        {
            wettedCells_[I] = 1; 
        }
    }
}

void wettedCellsFunctionObject::calcWettedDomainPercent()
{
    scalar wettedCellsSum = 0;  

    const volScalarField& wettedCells = wettedCellsPtr_(); 

    forAll (wettedCells, I)
    {
        if (wettedCells[I] == 1)
        {
            wettedCellsSum += 1; 
        }
    }

    wettedDomainPercent_ = wettedCellsSum / alpha1_.size() * 100; 
}

void wettedCellsFunctionObject::report()
{
    Info << "Wetted " << wettedDomainPercent_ 
        << " % of the domain." << endl; 
}

bool wettedCellsFunctionObject::start()
{
    execute(true); 
    return true;
}


bool wettedCellsFunctionObject::end()
{
    return execute(false);
}

void wettedCellsFunctionObject::updateMesh(const mapPolyMesh& map)
{
    execute(false); 
}

void wettedCellsFunctionObject::movePoints(const polyMesh& mesh)
{
    execute(false);  
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
