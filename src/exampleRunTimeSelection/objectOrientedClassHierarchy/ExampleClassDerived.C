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

\*---------------------------------------------------------------------------*/

#include "ExampleClassDerived.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam 
{
namespace BookExamples
{

    defineTypeNameAndDebug(ExampleClassDerived, 0); 

    addToRunTimeSelectionTable(ExampleClassBase, ExampleClassDerived, dictionary);

    ExampleClassDerived::ExampleClassDerived(const dictionary& baseDict)
        :
            ExampleClassBase(baseDict)
    {
        // Read the type of the validation model from the dictionary.
        const word baseType(baseDict.lookup("baseModel"));

        Pout << "ExampleClassDerived(const dictionary& baseDict)" << endl;

        cout << "Type: " << baseType << endl;
    }


    ExampleClassDerived::ExampleClassDerived() 
    {
        // Read the type of the validation model from the dictionary.
        const word baseType(baseDict().lookup("baseModel"));
        Pout << "ExampleClassDerived(const dictionary& baseDict)" << endl;
        cout << "Type: " << baseType << endl;
    }

    ExampleClassDerived::~ExampleClassDerived()
    {
        Pout << "~ExampleClassDerived()" << endl;
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace BookExamples 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //
