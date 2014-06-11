/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by authors 
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
    testDebugging

Description
    Tester application for learning how to work with GDB debugger. 

    Implements a harmonic average operator in the fvc::namespace, which uses
    (1 / x) and introduces SIGFPE which is then debugged with gdb.

Authors:
    Tomislav Maric tomislav@sourceflux.de
    Jens Hoepken jens@sourceflux.de
    Kyle Mooney kyle.g.mooney@gmail.com

Contributors:

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "timeSelector.H"

namespace Foam 
{
    namespace fvc 
    {
        template<typename Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > 
        harmonicMean 
        (
            const GeometricField<Type, fvPatchField, volMesh>& inputField 
        )
        {
            typedef GeometricField<Type, fvPatchField, volMesh> volumeField; 

            typedef typename volumeField::GeometricBoundaryField volumeBoundaryField;

            const fvMesh& mesh = inputField.mesh();

            tmp< volumeField > resultTmp
            (
                new volumeField 
                (
                    IOobject
                    (
                        "fvc::harmonicMean(" + inputField.name() + ")", 
                        mesh.time().timeName(), 
                        mesh, 
                        IOobject::NO_READ, 
                        IOobject::NO_WRITE
                    ),
                    inputField
                )
            ); 

            volumeField& resultField = resultTmp(); 

            forAll (resultField, I)
            {
                // SIGFPE.
                resultField[I] = (1. / resultField[I]);

                Info << "resultField[I] " << resultField[I] << endl;

                // No SIGFPE.
                //resultField[I] = (1. / (resultField[I] + SMALL));
            }

            labelField total (inputField.size(), 1);

            const labelList& own = mesh.owner(); 
            const labelList& nei = mesh.neighbour(); 

            forAll (own, I)
            {
                // Q: Which is more efficient, caching O, N, or multiple addressing?
                // A: What does profiling with valgrind say?
                label P = own[I];
                label N = nei[I];

                ++total[P];
                ++total[N];

                // SIGFPE
                resultField[P] += (1. / inputField[N]);
                resultField[N] += (1. / inputField[P]);

                // No SIGFPE.
                //resultField[P] += (1. / (inputField[N] + SMALL));
                //resultField[N] += (1. / (inputField[P] + SMALL));

            }

            const volumeBoundaryField& inputFieldBoundary = 
                inputField.boundaryField(); 

            forAll (inputFieldBoundary, patchI)
            {
                if (inputFieldBoundary[patchI].coupled())
                {
                    const Field<Type>& inputFieldNeighbour = 
                        inputFieldBoundary[patchI].patchNeighbourField(); 

                    forAll (inputFieldNeighbour, patchFaceI)
                    {
                        label faceLabel = patchFaceI + 
                            inputFieldBoundary[patchI].patch().start(); 

                            // SIGFPE.
                            resultField[own[faceLabel]] += 
                                (1. / inputFieldNeighbour[patchFaceI]);

                            // No SIGFPE. 
                            //resultField[own[faceLabel]] += 
                                //(1. / (inputFieldNeighbour[patchFaceI] + SMALL));

                            ++total[own[faceLabel]];
                    }
                }
            }

            forAll (resultField, I)
            {
                resultField[I] = 1. / resultField[I];

                // Uncomment do solve SIGFPE bug.
                // resultField[I] = 1. / (resultField[I] + SMALL);

                resultField[I] *= total[I];
            }

            return resultTmp;
        }
    }
}

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



    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    if (!args.optionFound("field"))
    {
        FatalErrorIn
        (
            "main()"
        )   << "Please provide a name of the field: use the 'field' option.." << endl
            << exit(FatalError);
    }

    const word fieldName = args.optionRead<word>("field");

    volScalarField inputField 
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

    Foam::instantList timeDirs = Foam::timeSelector::select0(runTime, args);

    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);

        Info << "------------------------------------" << endl;
        Info<< "Time = " << runTime.timeName() << endl;

        mesh.readUpdate();

        inputField = volScalarField
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

        fvc::harmonicMean(inputField)->write();

        Info << "------------------------------------" << endl;

    }

    Info<< "\nEnd\n" << endl;
    return 0;
}


// ************************************************************************* //
