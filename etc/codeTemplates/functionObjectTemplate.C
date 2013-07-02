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

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(TYPENAME, 0);


// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const objectRegistry& TYPENAME::obr() const
{
    return obr_;
}


const fvMesh& TYPENAME::mesh() const
{
    return static_cast<fvMesh const &>(obr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

TYPENAME::TYPENAME
(
    const word& name,
    const objectRegistry& obr,
    const dictionary& dict,
    const bool
)
:
    functionObject(name),
    obr_(obr)
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

    return true;
}


void TYPENAME::execute()
{
    Info << typeName << "::execute" << endl;
}


bool TYPENAME::end()
{
    Info << typeName << "::end" << endl;

    return true;
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

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
