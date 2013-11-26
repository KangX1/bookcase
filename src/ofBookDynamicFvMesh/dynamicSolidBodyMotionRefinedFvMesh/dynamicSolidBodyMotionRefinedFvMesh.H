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
    Foam::dynamicSolidBodyMotionRefinedFvMesh

Description
    Dynamic mesh class for combined mesh motion and hexahedral refinement.
    

SourceFiles
    dynamicSolidBodyMotionRefinedFvMesh.C
    dynamicSolidBodyMotionRefinedFvMeshNew.C

Authors
    Tomislav Maric
    maric<<at>>csi<<dot>>tu<<minus>>darmstadt<<dot>>de
    tomislav<<dot>>maric<<at>>gmx<<dot>>com

\*---------------------------------------------------------------------------*/

#ifndef dynamicSolidBodyMotionRefinedFvMesh_H
#define dynamicSolidBodyMotionRefinedFvMesh_H

#include "dynamicRefineFvMesh.H"
#include "solidBodyMotionFunction.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class dynamicSolidBodyMotionRefinedFvMesh Declaration
\*---------------------------------------------------------------------------*/

class dynamicSolidBodyMotionRefinedFvMesh
:
    public dynamicRefineFvMesh
{
    //- Dictionary of solid body motion control parameters
    const dictionary motionCoeffs_;

    //- The motion control function
    autoPtr<solidBodyMotionFunction> SBMFPtr_;

    //- The reference points which are transformed
    pointIOField undisplacedPoints_;

public:

    //- Runtime type information
    TypeName("dynamicSolidBodyMotionRefinedFvMesh");

    // Constructors

        //- Construct from objectRegistry, and read/write options
        explicit dynamicSolidBodyMotionRefinedFvMesh(const IOobject& io);


    //- Destructor
    virtual ~dynamicSolidBodyMotionRefinedFvMesh();


    // Member Functions
    
        //- Compute the maximal Courant number, including mesh motion.
        scalar getMaxMeshCourantNumber(const fvMesh& mesh, const surfaceScalarField& phi);

        //- Adjust the time step based on the mesh courant number. 
        virtual void adjustMeshCourantTimeStep(); 

        //- Update the mesh for both mesh motion and topology change
        virtual bool update();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
