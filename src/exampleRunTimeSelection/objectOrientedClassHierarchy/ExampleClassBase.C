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

#include "ExampleClassBase.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam 
{
namespace BookExamples
{
    defineTypeNameAndDebug(ExampleClassBase, 0);

    defineRunTimeSelectionTable(ExampleClassBase, Dictionary);
    defineRunTimeSelectionTable(ExampleClassBase, Word);
    
    addToRunTimeSelectionTable(ExampleClassBase, ExampleClassBase, Dictionary);

    void ExampleClassBase::initData(const dictionary& baseDict) 
    {
        Pout << "ExampleExampleClassBase::initData(const dictionary&)" << endl;
        Pout << "Dictionary parameter initialization." << endl;

        // Set the parameter based on a dictionary entry.
        parameter_ = baseDict.lookupOrDefault<string> (
            "dictParameter", 
            "Constructed with a dictionary"
        );
    }

    ExampleClassBase::ExampleClassBase(const word& name)
        :
            baseDict_(), 
            parameter_("Set using the name.")
    {
        Pout<< "ExampleClassBase::ExampleClassBase(const word&)" << endl;
        Pout << "Default parameter initialization." << endl;
    }

    ExampleClassBase::ExampleClassBase(const dictionary& baseDict)
        :
            baseDict_(baseDict)
    {
        initData(baseDict); 
    }

    ExampleClassBase::~ExampleClassBase()
    {
        Pout << "~ExampleClassBase()" << endl;
    }

    autoPtr<ExampleClassBase> ExampleClassBase::New (
        const word& name 
    )
    {

        Info<< "Selecting validation model " << name << endl;
        // Find the constructor pointer for the model in the constructor table.
        WordConstructorTable::iterator cstrIter =
            WordConstructorTablePtr_->find(name);

        // If the constructor pointer is not found in the table.
        if (cstrIter == WordConstructorTablePtr_->end())
        {
            FatalErrorIn (
                "ExampleClassBase::New(const dictionary&)"
            )   << "Unknown ExampleClassBase type "
                << name << nl << nl
                << "Valid ExampleClassBases are : " << endl
                << WordConstructorTablePtr_->sortedToc()
                << exit(FatalError);
        }

        // Construct the model and return the autoPtr to the object. 
        return autoPtr<ExampleClassBase>
            (cstrIter()(name));
    }

    autoPtr<ExampleClassBase> ExampleClassBase::New (
        const dictionary& baseDict
    )
    {
        const word name = baseDict.lookupOrDefault<word> (
                "className", 
                "ExampleClassBase"
        ); 

        Info<< "Selecting validation model " << name << endl;
        // Find the constructor pointer for the model in the constructor table.
        DictionaryConstructorTable::iterator cstrIter =
            DictionaryConstructorTablePtr_->find(name);

        // If the constructor pointer is not found in the table.
        if (cstrIter == DictionaryConstructorTablePtr_->end())
        {
            FatalErrorIn (
                "ExampleClassBase::New(const dictionary&)"
            )   << "Unknown ExampleClassBase type "
                << name << nl << nl
                << "Valid ExampleClassBases are : " << endl
                << DictionaryConstructorTablePtr_->sortedToc()
                << exit(FatalError);
        }

        // Construct the model and return the autoPtr to the object. 
        return autoPtr<ExampleClassBase>
            (cstrIter()(baseDict));
    }



    autoPtr<ExampleClassBase> ExampleClassBase::New ()
    {
        dictionary baseDict ("constant/baseDict"); 

        return ExampleClassBase::New(baseDict); 
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace BookExamples 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
