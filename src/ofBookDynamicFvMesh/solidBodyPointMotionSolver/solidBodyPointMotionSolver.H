/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
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
    Foam::solidBodyPointMotionSolver

Description
    Solid-body motion of the mesh specified by a run-time selectable
    motion function.

SourceFiles
    solidBodyPointMotionSolver.C

Authors
    Tomislav Maric tomislav<<dot>>maric<<a>>gmx<<dot>>com

\*---------------------------------------------------------------------------*/

#ifndef solidBodyPointMotionSolver_H
#define solidBodyPointMotionSolver_H

#include "dictionary.H"
#include "pointIOField.H"
#include "solidBodyMotionFunction.H"
#include "tmp.H"
#include "pointField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                   Class solidBodyPointMotionSolver Declaration
\*---------------------------------------------------------------------------*/

class solidBodyPointMotionSolver
{
    // Private data

        //- Dictionary of motion control parameters
        const dictionary dynamicMeshCoeffs_;

        //- The motion control function
        autoPtr<solidBodyMotionFunction> SBMFPtr_;

    // Private Member Functions

        //- Disallow default bitwise copy construct
        solidBodyPointMotionSolver(const solidBodyPointMotionSolver&);

        //- Disallow default bitwise assignment
        void operator=(const solidBodyPointMotionSolver&);


public:

    //- Runtime type information
    TypeName("solidBodyPointMotionSolver");


    // Constructors

        //- Construct from IOobject
        solidBodyPointMotionSolver(const IOobject& io);


    //- Destructor
    virtual ~solidBodyPointMotionSolver();


    // Member Functions

        //- Update the mesh for both mesh motion and topology change
        virtual tmp<pointField> movePoints(const pointField& points) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
