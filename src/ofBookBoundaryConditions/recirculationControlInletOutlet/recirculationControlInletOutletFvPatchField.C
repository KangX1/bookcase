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

#include "recirculationControlInletOutletFvPatchField.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF
)
:
    inletOutletFvPatchField<Type>(p, iF), 
    recirculationRate_(0),
    controlledField_()
{
}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf,
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    inletOutletFvPatchField<Type>(ptf, p, iF, mapper), 
    recirculationRate_(0),
    controlledField_()
{}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const dictionary& dict
)
:
    inletOutletFvPatchField<Type>(p, iF, dict), 
    recirculationRate_(), 
    controlledField_()
{
}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf
)
:
    inletOutletFvPatchField<Type>(ptf),
    recirculationRate_(ptf.recirculationRate_),
    controlledField_(ptf.controlledField_)
{}


template<class Type>
Foam::recirculationControlInletOutletFvPatchField<Type>::recirculationControlInletOutletFvPatchField
(
    const recirculationControlInletOutletFvPatchField<Type>& ptf,
    const DimensionedField<Type, volMesh>& iF
)
:
    inletOutletFvPatchField<Type>(ptf, iF),
    recirculationRate_(ptf.recirculationRate_),
    controlledField_(ptf.controlledField_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::updateCoeffs()
{
    // Adjust the values before doing the control operation. 
    inletOutletFvPatchField<Type>::updateCoeffs();

    //if (this->updated())
    //{
        //return;
    //}

    //const Field<scalar>& phip =
        //this->patch().template lookupPatchField<surfaceScalarField, scalar>
        //(
            //phiName_
        //);

    // Compute the percentage of the inflow volumetric flux (recirculation rate).   

    // If defined, access the inlet boundary, and reduce the velocity by the
    // recirculation rate.  

}


template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::write(Ostream& os) const
{
    inletOutletFvPatchField<Type>::write(os); 
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void Foam::recirculationControlInletOutletFvPatchField<Type>::operator=
(
    const fvPatchField<Type>& ptf
)
{
    inletOutletFvPatchField<Type>::operator=(ptf); 
}


// ************************************************************************* //
