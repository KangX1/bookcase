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

Application
    myRunTimeSelectableClass

Description
    Run Time Selection (RTS) testing application for the example classes 
    of the exampleRunTimeSelection library that show how RTS is enabled for 
    an object oriented as well as generic class hierarchy. 

Authors
    Tomislav Maric tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "ExampleClassBase.H"
#include "ExampleClassDerived.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

using namespace BookExamples;

int main(int argc, char *argv[])
{
    // Add the option to the argument list for the name of the class to be 
    // selected using the RTS mechanism.
    argList::addOption
    (
        "className",
        "name of the run-time selected class"
    );

    #include "setRootCase.H"
    #include "createTime.H"

    autoPtr<ExampleClassBase> baseClassPtr; 

    // Global argument list object is named "args"
    // If the option is found in the argument map. 
    if (args.optionFound("className"))
    {
        // Get the className string. 
        const word className = args.option("className");
        // Define the pointer using the Word constructor.
        baseClassPtr = ExampleClassBase::New(className);
    }
    else 
    {
        IOdictionary baseDict (
            IOobject ( 
                "runTimeSelectionExampleDict", 
                "constant", 
                runTime, 
                IOobject::MUST_READ_IF_MODIFIED,
                IOobject::AUTO_WRITE
            )
        ); 

        // Define the pointer using the Dictionary constructor.
        baseClassPtr = ExampleClassBase::New(baseDict);
    }

    // Use the class pointer.
    Info << "Class parameter: " << baseClassPtr->parameter() << endl;

    return 0;
}


// ************************************************************************* //
