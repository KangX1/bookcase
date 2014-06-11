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
    testFieldCellSet

Description
    Tester applictation for the field based cellSet example.

Authors:
    Tomislav Maric tomislav@sourceflux.de
    Jens Hoepken jens@sourceflux.de
    Kyle Mooney kyle.g.mooney@gmail.com

Contributors:


\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include <functional>
#include "fieldCellSet.H"
#include "OFstream.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
    argList::addOption
    (
        "field",
        "Name of the field to be averaged."
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
        )   << "Please use option '-field' to provide the name of the field on which the cell set is based." << endl
            << exit(FatalError);
    }

    const word fieldName = args.optionRead<word>("field");

    volScalarField field
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

    fieldCellSet fcs 
    (
        IOobject
        (
            "fieldCellSet", 
            runTime.timeName(),  
            runTime, 
            IOobject::NO_READ, 
            IOobject::AUTO_WRITE
        ),
        mesh
    ); 

    // Create a set of cells that have the value of the "field" equal to 1, 
    // using C++ STL function objects (C++03 standard). 
    fcs.collectCells(field, std::bind1st(std::equal_to<scalar>(), 1));  

    // Write the cell set. 
    fcs.write(); 

    Info<< "\nEnd\n" << endl;
    return 0;
}


// ************************************************************************* //
