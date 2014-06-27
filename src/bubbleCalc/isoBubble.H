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
    Bubble described using an iso-surface mesh. 

SourceFiles
    isoBubble.C

Authors
    Tomislav Maric, tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#ifndef isoBubble_H
#define isoBubble_H

#include "regIOobject.H"
#include "autoPtr.H"
#include "volFieldsFwd.H"
#include "scalarField.H"
#include "pointFields.H"
#include "isoSurface.H"
#include "fileName.H"

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

    // Tracked iso-field.
    volScalarField const * isoFieldPtr_;  
    
    // Computed point iso-field.
    scalarField isoPointField_; 

    // Bubble geometry described with an iso-surface mesh.
    autoPtr<isoSurface> bubblePtr_; 

    // iso value
    scalar isoValue_; 

    // Number of zeros that are prepended to the timeIndex() for output .vtk files. 
    label timeIndexPad_; 

    // Output format.
    word outputFormat_; 

    // Turn on regularization of the isoSurface.
    bool regularize_;  

    virtual void computeIsoPointField(); 

    fileName paddWithZeros(const fileName& input) const;

    void resetPtrData()
    {
        isoFieldPtr_ = 0; 
    }

public:

    // Constructors

        //- Construct from components
        isoBubble 
        (
            const IOobject& io, 
            const volScalarField& bubbleField, 
            bool isTime = false,
            scalar isoValue = 0.5,
            label timeIndexPad = 10, 
            word outputFormat = "vtk", 
            bool regularize = true
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
        bool write (fileName file) const;

        bool write() const;
        
        bool writeData(Ostream& os) const; 

        // Access
        
        const volScalarField& isoField() const 
        {
            return *isoFieldPtr_;
        }

        scalar area() const;

        vector centre() const;

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
