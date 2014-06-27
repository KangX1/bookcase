/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Application
    writePatch

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "timeSelector.H"


template<typename VolumetricField>
void averageBoundaryField 
(
    const word& patchName, 
    const IOobject& fieldHeader, 
    const fvMesh& mesh
)
{
    Info << fieldHeader.headerClassName() << endl;
    if (fieldHeader.headerClassName() == VolumetricField::typeName)
    {
        typedef typename VolumetricField::value_type Type; 

        GeometricField<Type, fvPatchField, volMesh> field 
        (
            fieldHeader,
            mesh
        );

        label patchID = mesh.boundaryMesh().findPatchID(patchName);

        const Field<Type>& patchField = field.boundaryField()[patchID];

        Info << patchName 
            << " average : " << Foam::average(patchField) << endl;
    } 
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
    argList::addOption
    (
        "patch",
        "Name of the boundary mesh patch."
    );

    argList::addOption
    (
        "field",
        "Name of the field to be averaged."
    );

    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    if (!args.optionFound("patch"))
    {
        FatalErrorIn
        (
            "main()"
        )   << "Please use option '-patch' to provide the name of the boundary mesh patch." << endl
            << exit(FatalError);
    }

    if (!args.optionFound("field"))
    {
        FatalErrorIn
        (
            "main()"
        )   << "Please use option '-field' to provide the name of the field to be averaged." << endl
            << exit(FatalError);
    }

    const word patchName = args.optionRead<word>("patch");
    const word fieldName = args.optionRead<word>("field");

    IOobject fieldHeader
    (
        fieldName,
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    Foam::instantList timeDirs = Foam::timeSelector::select0(runTime, args);

    forAll(timeDirs, timeI)
    {
        if (fieldHeader.headerOk())
        {
            averageBoundaryField<volScalarField>(patchName, fieldHeader, mesh); 
            averageBoundaryField<volVectorField>(patchName, fieldHeader, mesh); 
            averageBoundaryField<volSphericalTensorField>(patchName, fieldHeader, mesh); 
            averageBoundaryField<volTensorField>(patchName, fieldHeader, mesh); 
        }
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
