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

Authors
    Tomislav Maric
    maric<<at>>csi<<dot>>tu<<minus>>darmstadt<<dot>>de
    tomislav<<dot>>maric<<at>>gmx<<dot>>com

\*---------------------------------------------------------------------------*/

#include "dynamicSolidBodyMotionRefinedFvMesh.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"
#include "fvcSurfaceIntegrate.H"
#include "surfaceMesh.H"
#include "fvsPatchField.H"

//#include "pimpleControl.H"
//#include "fixedValueFvPatchFields.H"
//#include "adjustPhi.H"
//#include "fvcMeshPhi.H"
//#include "fvScalarMatrix.H"

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

    Info << "INFO phi size before refinement : " 
        << lookupObject<surfaceScalarField>("phi").size() << endl;
    Info << "INFO alpha1 size before refinement : " 
        << lookupObject<volScalarField>("alpha1").size() << endl;
    
    dynamicRefineFvMesh::update(); 

    Info << "INFO phi size after refinement : " 
        << lookupObject<surfaceScalarField>("phi").size() << endl;
    Info << "INFO phi average after refinement : " 
        << average(lookupObject<surfaceScalarField>("phi")) << endl;
    Info << "INFO alpha1 size after refinement : " 
        << lookupObject<volScalarField>("alpha1").size() << endl;

    Info << "INFO max alpha1 after refinement: " << max(lookupObject<volScalarField>("alpha1")) << endl;

    //static bool hasWarned = false; 

    //const pointField& meshPoints = points(); 
    //fvMesh::movePoints(pointMotionSolver_.movePoints(meshPoints)); 

    //if (foundObject<volVectorField>("U"))
    //{
        //const_cast<volVectorField&>(lookupObject<volVectorField>("U"))
            //.correctBoundaryConditions();
    //}
    //else if (!hasWarned)
    //{
        //WarningIn("solidBodyPointMotionSolver::update()")
            //<< "Did not find volVectorField U."
            //<< " Not updating U boundary conditions." << endl;
    //}


    //Info << "INFO max alpha1 after motion : " << max(lookupObject<volScalarField>("alpha1")) << endl;
    //Info << "INFO phi average after motion: " 
        //<< average(lookupObject<surfaceScalarField>("phi")) << endl;


    //adjustMeshCourantTimeStep(); 

    // TODO: remove, debugging
    //const_cast<Time&>(lookupObject<volVectorField>("U").time()).writeNow(); 

    // FIXME: this checks the mesh courant number against the Courant number, and 
    // adjusts the time step accordingly. 

    return true; 
}

// FIXME: remove this member function
//void Foam::dynamicSolidBodyMotionRefinedFvMesh::correctPhi() 
//{
    //const volScalarField& p_rgh = lookupObject<volScalarField>("p_rgh");
    //const volScalarField& rho = lookupObject<volScalarField>("rho");
    //const volVectorField& U = lookupObject<volVectorField>("U");

    //surfaceScalarField& phi = const_cast<surfaceScalarField&>(
        //lookupObject<surfaceScalarField>("phi")
    //);

    //wordList pcorrTypes
    //(
        //p_rgh.boundaryField().size(),
        //zeroGradientFvPatchScalarField::typeName
    //);

    //forAll (p_rgh.boundaryField(), i)
    //{
        //if (p_rgh.boundaryField()[i].fixesValue())
        //{
            //pcorrTypes[i] = fixedValueFvPatchScalarField::typeName;
        //}
    //}

    //const Time& runTime = rho.time(); 
    //fvMesh& mesh = *this; 

    //volScalarField pcorr
    //(
        //IOobject
        //(
            //"pcorr",
            //runTime.timeName(),
            //mesh,
            //IOobject::NO_READ,
            //IOobject::NO_WRITE
        //),
        //mesh,
        //dimensionedScalar("pcorr", p_rgh.dimensions(), 0.0),
        //pcorrTypes
    //);

    //dimensionedScalar rAUf("(1|A(U))", dimTime/rho.dimensions(), 1.0);

    //adjustPhi(phi, U, pcorr);

    //fvc::makeAbsolute(phi, U);

    //pimpleControl pimple(mesh); 

    //while (pimple.correctNonOrthogonal())
    //{
        //fvScalarMatrix pcorrEqn
        //(
            //fvm::laplacian(rAUf, pcorr) == fvc::div(phi)
        //);

        //pcorrEqn.setReference(pRefCell, pRefValue);
        //pcorrEqn.solve();

        //if (pimple.finalNonOrthogonalIter())
        //{
            //phi -= pcorrEqn.flux();
            //phiAbs = phi;
            //fvc::makeRelative(phi, U);
        //}
    //}

    //phi.oldTime() = phi;
//}


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

// FIXME: remove this member function
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
