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
    wettedCells_
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
    )
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
    notImplemented("wettedCellsFunctionObject::execute(const bool)"); 
    return true;
}

bool wettedCellsFunctionObject::start()
{
    notImplemented("wettedCellsFunctionObject::start()"); 
    return true;
}


bool wettedCellsFunctionObject::end()
{
    notImplemented("wettedCellsFunctionObject::end()"); 
    return execute(false);
}


bool wettedCellsFunctionObject::timeSet()
{
    notImplemented("wettedCellsFunctionObject::timeSet()"); 
    return true;
}

void wettedCellsFunctionObject::updateMesh(const mapPolyMesh& map)
{
    notImplemented("wettedCellsFunctionObject::updateMesh(const mapPolyMesh&)"); 
}

void wettedCellsFunctionObject::movePoints(const polyMesh& mesh)
{
    notImplemented("wettedCellsFunctionObject::movePoints(const polyMesh&)"); 
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
