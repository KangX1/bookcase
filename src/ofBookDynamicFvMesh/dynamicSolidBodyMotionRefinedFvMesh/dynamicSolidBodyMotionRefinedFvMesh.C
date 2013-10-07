/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2012 OpenFOAM Foundation
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

#include "dynamicSolidBodyMotionRefinedFvMesh.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"
#include "fvcSurfaceIntegrate.H"
#include "surfaceMesh.H"
#include "fvsPatchField.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(dynamicSolidBodyMotionRefinedFvMesh, 0);
    addToRunTimeSelectionTable(dynamicFvMesh, dynamicSolidBodyMotionRefinedFvMesh, IOobject);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::dynamicSolidBodyMotionRefinedFvMesh::dynamicSolidBodyMotionRefinedFvMesh(const IOobject& io)
:
    dynamicRefineFvMesh(io), 
    pointMotionSolver_(io)
{
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::dynamicSolidBodyMotionRefinedFvMesh::~dynamicSolidBodyMotionRefinedFvMesh()
{}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * /

bool Foam::dynamicSolidBodyMotionRefinedFvMesh::update()
{
    static bool hasWarned = false; 

    dynamicRefineFvMesh::update(); 

    const pointField& meshPoints = points(); 
    movePoints(pointMotionSolver_.movePoints(meshPoints)); 

    if (foundObject<volVectorField>("U"))
    {
        const_cast<volVectorField&>(lookupObject<volVectorField>("U"))
            .correctBoundaryConditions();
    }
    else if (!hasWarned)
    {
        WarningIn("solidBodyPointMotionSolver::update()")
            << "Did not find volVectorField U."
            << " Not updating U boundary conditions." << endl;
    }

    // FIXME: this checks the mesh courant number against the Courant number, and 
    // adjusts the time step accordingly. 
    //adjustMeshCourantTimeStep(); 

    return true; 
}

Foam::scalar Foam::dynamicSolidBodyMotionRefinedFvMesh::getMaxMeshCourantNumber(
    const fvMesh& mesh, 
    const surfaceScalarField& phi
)
{
    Time& runTime = const_cast<Time&>(mesh.time()); 

    #include "CourantNo.H"
    #include "meshCourantNo.H"

    return max(CoNum, meshCoNum); 
}


void Foam::dynamicSolidBodyMotionRefinedFvMesh::adjustMeshCourantTimeStep()
{
    const fvMesh& mesh = *this; 
    Time& runTime = const_cast<Time&>(mesh.time()); 
    const surfaceScalarField& phi = lookupObject<surfaceScalarField>("phi"); 

    #include "readTimeControls.H"

    scalar CoNum = getMaxMeshCourantNumber(mesh, phi);  

    while (CoNum >= maxCo)
    {
        #include "setDeltaT.H"
        CoNum = getMaxMeshCourantNumber(mesh,phi); 

        Info << "maxCo = " << maxCo << endl; 
        Info << "Corrected CoNum = " << CoNum << endl;
        Info << "Corrected deltaT = " << runTime.deltaT() << endl;
    }
}

void Foam::dynamicSolidBodyMotionRefinedFvMesh::removeOvershoots(volScalarField& alpha1)
{
    forAll(alpha1, I)
    {
        if (alpha1[I] > 1)
        {
            alpha1[I] = 1; 
        }
    }
}

// ************************************************************************* //
