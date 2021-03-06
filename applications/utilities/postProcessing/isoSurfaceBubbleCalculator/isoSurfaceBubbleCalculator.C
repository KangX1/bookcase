/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author 
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

Application
    calcBubbleVelocity

Description
    Post processing application for computing the velocity and area of a 
    rising bubble using an iso-surface.

Authors
    Tomislav Maric tomislav@sourceflux.de 
    Jens Hoepken jens@sourceflux.de
    Kyle Mooney kyle.g.mooney@gmail.com

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "timeSelector.H"
#include "isoBubble.H"

using namespace bookExamples;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
    argList::addOption
    (
        "field",
        "name of the field to be averaged"
    );

    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    word fieldName = "";

    if (!args.optionFound("field"))
    {
        fieldName = "alpha1";  
    }
    else
    {
        fieldName = args.optionRead<word>("field");
    }

    volScalarField isoField 
    (
        IOobject 
        (
            fieldName, 
            runTime.timeName(), 
            mesh, 
            IOobject::MUST_READ, 
            IOobject::NO_WRITE
        ),
        mesh
    );

    isoBubble bubble 
    (
        IOobject
        (
            "bubble", 
            "bubble", 
            runTime, 
            IOobject::NO_READ, 
            IOobject::AUTO_WRITE
        ), 
        isoField 
    ); 

    Foam::instantList timeDirs = Foam::timeSelector::select0(runTime, args);

    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);

        Info<< "Time = " << runTime.timeName() << endl;

        mesh.readUpdate();

        isoField = volScalarField
        (
            IOobject 
            (
                fieldName, 
                runTime.timeName(), 
                mesh, 
                IOobject::MUST_READ, 
                IOobject::NO_WRITE
            ),
            mesh
        );

        bubble.reconstruct(isoField); 

        Info << "Bubble area = " << bubble.area() << endl;
        Info << "Bubble centre = " << bubble.centre() << endl;

        bubble.write(); 
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nEnd\n" << endl;
    return 0;
}


// ************************************************************************* //
