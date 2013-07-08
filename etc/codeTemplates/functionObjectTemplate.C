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

#include "TYPENAME.H"
#include "Time.H"
#include "fvCFD.H"
#include "unitConversion.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(TYPENAME, 0);
addToRunTimeSelectionTable(functionObject, TYPENAME, dictionary); 


// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

TYPENAME::TYPENAME
(
    const word& name,
    const Time& time,
    const dictionary& dict
)
:
    functionObject(name),
    time_(time)
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

TYPENAME::~TYPENAME()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool TYPENAME::read(const dictionary& dict)
{
    Info << typeName << "::read" << endl;

    // TODO: check if execution is necessary here, since execute follows the read, 
    //       done in the constructor. 
    // return execute(false); 
    return true;
}


bool TYPENAME::execute(const bool forceWrite)
{
    Info << typeName << "::execute" << endl;
    return true;
}

bool TYPENAME::start()
{
    Info << typeName << "::start" << endl;

    return true;
}


bool TYPENAME::end()
{
    Info << typeName << "::end" << endl;

    return execute(false);
}


bool TYPENAME::timeSet()
{
    Info << typeName << "::timeSet" << endl;

    return true;
}


void TYPENAME::write()
{
    Info << typeName << "::write" << endl;
}

void TYPENAME::updateMesh(const mapPolyMesh& map)
{
    Info << typeName << "::updateMesh" << endl;
}

void TYPENAME::movePoints(const polyMesh& mesh)
{
    Info << typeName << "::movePoints" << endl;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
