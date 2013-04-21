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

Class
    Foam::isoBubble

Description
    Bubble described by an iso-surface mesh. 

SourceFiles
    isoBubble.C

Authors
    Tomislav Maric, tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#ifndef isoBubble_H
#define isoBubble_H

#include "regIOobject.H"
#include "volFieldsFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace bookExamples
{

/*---------------------------------------------------------------------------*\
                         Class isoBubble Declaration
\*---------------------------------------------------------------------------*/

class isoBubble
    :
        public regIOobject
{
    volScalarField const * bubbleFieldPtr_;  

public:

    // Constructors

        //- Construct from components
        isoBubble 
        (
            const IOobject& io, 
            const volScalarField& bubbleField, 
            bool isTime = false
        );

        //- Construct as copy
        isoBubble(const isoBubble&);

    // Destructor
    
        virtual ~isoBubble(); 

    // Member Functions
    
        // Edit
        
        void setBubbleField(const volScalarField& bubbleField); 

        void reconstruct(); 

        // Write
        bool write() const;
        
        bool writeData(Ostream& os) const; 


    // Member Operators

        void operator=(const isoBubble&);

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace bookExamples 


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
