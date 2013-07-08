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

#include "adjustTimeStep.H"
#include "Time.H"
#include "fvCFD.H"
#include "unitConversion.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(adjustTimeStep, 0);
addToRunTimeSelectionTable(functionObject, adjustTimeStep, dictionary); 


// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

adjustTimeStep::adjustTimeStep
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

adjustTimeStep::~adjustTimeStep()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool adjustTimeStep::read(const dictionary& dict)
{
    Info << typeName << "::read" << endl;

    // TODO: check if execution is necessary here, since execute follows the read, 
    //       done in the constructor. 
    // return execute(false); 
    return true;
}


bool adjustTimeStep::execute(const bool forceWrite)
{
    Info << typeName << "::execute" << endl;
    return true;
}

bool adjustTimeStep::start()
{
    Info << typeName << "::start" << endl;

    return true;
}


bool adjustTimeStep::end()
{
    Info << typeName << "::end" << endl;

    return execute(false);
}


bool adjustTimeStep::timeSet()
{
    Info << typeName << "::timeSet" << endl;

    return true;
}


void adjustTimeStep::write()
{
    Info << typeName << "::write" << endl;
}

void adjustTimeStep::updateMesh(const mapPolyMesh& map)
{
    Info << typeName << "::updateMesh" << endl;
}

void adjustTimeStep::movePoints(const polyMesh& mesh)
{
    Info << typeName << "::movePoints" << endl;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
