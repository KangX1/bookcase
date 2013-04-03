/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 OpenFOAM Foundation
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
    runTimeSelectionMinimalExample

Description
    This is an test application with a minimal example of the Run Time Selection
    (RTS) mechanism added into a object oriented class hierarchy. 
    The RTS mechanism in this example doesn't use dictionary entries, it relies
    on user specified type names through the console I/O. 

    Note: this tester app can be executed anywhere 

Authors
    Tomislav Maric tomislav.maric@gmx.com

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

class AlgorithmBase
{
    public: 

        // Declare the static variable typeName of the class AlgorithmBase.
        TypeName ("base");

        // Empty constructor. 
        AlgorithmBase () {};

        // Word constructor.
        AlgorithmBase (const word& algorithmName) {};

        // Destructor: needs to be declared virtual since 
        virtual ~AlgorithmBase() {};

        // Macro for declaring stuff required for RTS 
        declareRunTimeSelectionTable
        (
            autoPtr, 
            AlgorithmBase, 
            Word, 
            (
                const word& algorithmName
            ),
            (algorithmName)
        )

        // Factory Method (selector)
        static autoPtr<AlgorithmBase> New (const word& algorithmName)
        {

            // Find the Factory Method pointer in the RTS Table 
            // (HashTable<word, autoPtr<AlgorithmBase>(*)(word))
            WordConstructorTable::iterator cstrIter =
                WordConstructorTablePtr_->find(algorithmName);

            // If the Factory Method was not found. 
            if (cstrIter == WordConstructorTablePtr_->end())
            {
                FatalErrorIn
                (
                    "AlgorithmBase::New(const word&)"
                )   << "Unknown AlgorithmBase type "
                    << algorithmName << nl << nl
                    << "Valid AlgorithmBase types are :" << endl
                    << WordConstructorTablePtr_->sortedToc()
                    << exit(FatalError);
            }

            // Call the "constructor" and return the autoPtr<AlgorithmBase>
            return cstrIter()(algorithmName);

        }

        // Make the class callable (function object) 
        virtual void operator()() 
        {
            // Overridable default implementation
            Info << "AlgorithmBase::operator()()" << endl;
        }
};

defineTypeNameAndDebug(AlgorithmBase, 0);
defineRunTimeSelectionTable(AlgorithmBase, Word);
addToRunTimeSelectionTable(AlgorithmBase, AlgorithmBase, Word);

class AlgorithmNew
:
    public AlgorithmBase
{
    public: 

        // Declare the static variable typeName of the class AlgorithmNew.
        TypeName ("new");

        // Empty constructor. 
        AlgorithmNew () {};

        // Word constructor.
        AlgorithmNew (const word& algorithmName) {};

        // Make the class callable (function object) 
        virtual void operator()()
        {
            Info << "AlgorithmNew::operator()()" << endl;
        }
};

defineTypeNameAndDebug(AlgorithmNew, 0);
addToRunTimeSelectionTable(AlgorithmBase, AlgorithmNew , Word);

class AlgorithmAdditional
:
    public AlgorithmNew 
{
    public: 

        // Declare the static variable typeName of the class AlgorithmAdditional.
        TypeName ("additional");

        // Empty constructor. 
        AlgorithmAdditional () {};

        // Word constructor.
        AlgorithmAdditional (const word& algorithmName) {};

        // Make the class callable (function object) 
        virtual void operator()()
        {
            // Call base operator explicitly.
            AlgorithmNew::operator()();
            // Perform additional operations.
            Info << "AlgorithmAdditional::operator()()" << endl;
        }
};

defineTypeNameAndDebug(AlgorithmAdditional, 0);
addToRunTimeSelectionTable(AlgorithmBase, AlgorithmAdditional , Word);

int main(int argc, char *argv[])
{

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    argList::addOption
    (
        "algorithmName",
        "name of the run-time selected algorithm"
    );

    argList args(argc, argv);

    if (args.optionFound("algorithmName"))
    {
        autoPtr<AlgorithmBase> algorithmPtr; 

        // Get the className string. 
        const word algorithmName = args.option("algorithmName");
        // Define the pointer using the Word constructor.
        algorithmPtr = AlgorithmBase::New(algorithmName);

        // Get the reference to the algorithm.
        AlgorithmBase& algorithm = algorithmPtr(); 

        // Call the algorithm.
        algorithm(); 

    }
    else
    {
        FatalErrorIn
        (
            "main()"
        )   << "Please use with the 'algorithmName' option." << endl
            << exit(FatalError);
    }

    Info<< "\nEnd\n" << endl;
    return 0;
}


// ************************************************************************* //
