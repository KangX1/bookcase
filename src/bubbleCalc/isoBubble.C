/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 OpenFOAM Foundation
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

#include "isoBubble.H"
#include "error.H"

namespace Foam {

namespace bookExamples {

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

isoBubble::isoBubble
(
    const IOobject& io, 
    const volScalarField& bubbleField, 
    bool isTime 
)
    : 
        regIOobject(io, isTime), 
        bubbleFieldPtr_(&bubbleField)
{}

isoBubble::isoBubble(const isoBubble& copy)
    :
        regIOobject(copy), 
        bubbleFieldPtr_(copy.bubbleFieldPtr_)
{}

// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * * //

isoBubble::~isoBubble()
{
    bubbleFieldPtr_ = 0; 
}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void isoBubble::setBubbleField(const volScalarField& bubbleField)
{
    bubbleFieldPtr_ = &bubbleField; 
}

void isoBubble::reconstruct()
{
    // Generate the point field from the tracked volume field. 
    
    // Reconstruct the bubble using both fields.
    
}

bool isoBubble::write() const
{
    Info << "isoBubble::write" << endl;

    return true;
}

bool isoBubble::writeData(Ostream& os) const
{
    os << "Write bubble in the .vtk format" << endl;

    Info << "isoBubble::writeData" << endl;

    return true;
}

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void isoBubble::operator=(const isoBubble& rhs)
{
    // Check for assignment to self
    if (this == &rhs)
    {
        FatalErrorIn("isoBubble::operator=(const isoBubble&)")
            << "Attempted assignment to self"
            << abort(FatalError);
    }

    bubbleFieldPtr_ = rhs.bubbleFieldPtr_; 
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace bookExamples 


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //
