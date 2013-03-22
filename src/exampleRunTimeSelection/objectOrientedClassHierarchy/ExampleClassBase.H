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

Class
    Foam::ExampleClassBase

Description

SourceFiles
    ExampleClassBaseI.H
    ExampleClassBase.C
    ExampleClassBaseIO.C

\*---------------------------------------------------------------------------*/

#ifndef ExampleClassBase_H
#define ExampleClassBase_H

#include "label.H"
#include "dictionary.H"
#include "runTimeSelectionTables.H"
#include "Pstream.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace BookExamples
{

/*---------------------------------------------------------------------------*\
                         Class ExampleClassBase Declaration
\*---------------------------------------------------------------------------*/

class ExampleClassBase
{

    dictionary baseDict_; 

    void initData(const dictionary& baseDict); 

    string parameter_; 

public:

    TypeName ("ExampleClassBase"); 

    declareRunTimeSelectionTable (
        autoPtr,  // Select the type of a smart pointer 
        ExampleClassBase,  // ExampleClassBase ame
        Word,  // Construct from a Word : arbitrary name 
        (
           const word& name 
        ),
        (name) // Constructor argument name list
    );

    declareRunTimeSelectionTable (
        autoPtr,  // Select the type of a smart pointer 
        ExampleClassBase,  // ExampleClassBase name
        Dictionary,  // Construct from dictionary : arbitrary name 
        (
           const dictionary& dictName 
        ),
        (dictName) // Constructor argument list
   );

   ExampleClassBase (const word& name); 
   ExampleClassBase (const dictionary& baseDict); 

   //- Factory method for the label constructor. It doesn't select, 
   //  it produces a new object. 
   static autoPtr<ExampleClassBase> New(const dictionary& baseDict);
   static autoPtr<ExampleClassBase> New(const word& name);
   
   static autoPtr<ExampleClassBase> New(); 

   const dictionary& baseDict() const
   {
       return baseDict_;
   }; 

   string parameter() const
   {
       return parameter_;
   }

   //- Destructor
   virtual ~ExampleClassBase();
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace BookExamples 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
