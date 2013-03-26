/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2012 OpenFOAM Foundation
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

namespace Foam 
{
namespace BookExamples
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Parameter>
ExampleClassTemplateBase<Parameter>::ExampleClassTemplateBase(
    const dictionary& dict)
{
    // The constructor sets the class attributes using dictionary entries.
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Parameter>
autoPtr<ExampleClassTemplateBase<Parameter> >
ExampleClassTemplateBase<Parameter>::New(const dictionary& dict)
{
    // Get the name from the dictionary.
    const word name = dict.lookupOrDefault<word>(
        "exampleClassTemplateBase", 
        "exampleClassOneBase"
    );

    // Get the RTS Table via the global object.  
    typename DictionaryConstructorTable::iterator cstrIter =
        DictionaryConstructorTablePtr_->find(name);
    // If the constructor pointer is not found in the table.
    if (cstrIter == DictionaryConstructorTablePtr_->end())
    {
        FatalErrorIn (
            "ExampleClassTemplateBase::New(const dictionary&)"
        )   << "Unknown ExampleClassTemplateBase type "
            << name << nl << nl
            << "Valid ExampleClassTemplateBases are : " << endl
            << DictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr< ExampleClassTemplateBase<Parameter> > (cstrIter()(dict));
}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace BookExamples 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
