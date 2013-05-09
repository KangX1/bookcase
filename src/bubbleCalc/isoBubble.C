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

\*---------------------------------------------------------------------------*/

#include "isoBubble.H"
#include "error.H"
#include "volPointInterpolation.H"
#include <iomanip>
#include <sstream>

namespace Foam {

namespace bookExamples {

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //
    
fileName isoBubble::paddWithZeros(const fileName& input) const
{
    word extension = input.ext(); 

    if (extension.empty())
    {
        extension = outputFormat_; 
    }

    // Get the time index. 
    const Time& runTime = isoFieldPtr_->time(); 
    // Get the time index. 
    label timeIndex = runTime.timeIndex(); 

    // Remove extension.
    fileName output = input.lessExt();  

    // Padd the string using stringstream and iomanip.
    std::stringstream ss;
    ss << output << "-" << std::setw(timeIndexPad_) << std::setfill('0') 
        << timeIndex << "." << extension;

    return ss.str(); 
}

void isoBubble::computeIsoPointField()
{
    // Interpolate the track field to the points using volPointInterpolation. 
    volPointInterpolation pointInterpolation (isoFieldPtr_->mesh());
    
    // Reconstruct the bubble using both fields.
    isoPointField_ = pointInterpolation.interpolate(*isoFieldPtr_)();
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

isoBubble::isoBubble
(
    const IOobject& io, 
    const volScalarField& bubbleField, 
    bool isTime , 
    scalar isoValue,
    label timeIndexPad,
    word outputFormat, 
    bool regularize
)
    : 
        regIOobject(io, isTime), 
        isoFieldPtr_(&bubbleField),
        isoPointField_(bubbleField.mesh().nPoints(),0), 
        bubblePtr_(),
        isoValue_(isoValue),
        timeIndexPad_(timeIndexPad), 
        outputFormat_(outputFormat), 
        regularize_(regularize)
{
    // Reconstruct immediately using the tracked field.
    reconstruct();
}

isoBubble::isoBubble(const isoBubble& copy)
    :
        regIOobject(copy), 
        isoFieldPtr_(copy.isoFieldPtr_),
        isoPointField_(copy.isoPointField_),
        bubblePtr_(),
        isoValue_(copy.isoValue_),
        timeIndexPad_(copy.timeIndexPad_), 
        outputFormat_(copy.outputFormat_), 
        regularize_(copy.regularize_)
{
    // Make a deep copy: avoid ownership transfer.  
    bubblePtr_ = autoPtr<isoSurface>(new isoSurface (copy.bubblePtr_()));
}

// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * * //

isoBubble::~isoBubble()
{
    resetPtrData(); 
}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void isoBubble::setBubbleField(const volScalarField& bubbleField)
{
    isoFieldPtr_ = &bubbleField; 
    isoPointField_.resize(bubbleField.mesh().nPoints()); 
}

void isoBubble::reconstruct()
{
    computeIsoPointField(); 
    
    // Create the isoSurface geometry 
    bubblePtr_ = autoPtr<isoSurface>
    (
        new isoSurface 
        (
            *isoFieldPtr_, 
            isoPointField_, 
            isoValue_, 
            regularize_ 
        )
    );
}

bool isoBubble::write(fileName file) const
{
    fileName fullPath = file.lessExt(); 
    mkDir(fullPath); 

    fullPath = fullPath + "/" + paddWithZeros(file); 

    bubblePtr_->write(fullPath); 

    return true;
}

bool isoBubble::write() const
{
    // Create the path to the instance directory.
    mkDir(path());

    fileName outFileName = paddWithZeros(objectPath());

    if (OFstream::debug)
    {
        Info<< "regIOobject::write() : "
            << "writing file " << outFileName << endl; 
    }

    bubblePtr_->write(outFileName);

    return true;
}

bool isoBubble::writeData(Ostream& os) const
{
    os << bubblePtr_(); 
    return true;
}

scalar isoBubble::area() const
{
    scalar area = 0;

    const pointField& points = bubblePtr_->points(); 
    const List<labelledTri>& faces = bubblePtr_->localFaces(); 

    forAll (faces, I)
    {
        area += mag(faces[I].normal(points));
    }

    return area;
}

vector isoBubble::centre() const
{
    const pointField& points = bubblePtr_->points(); 

    vector bubbleCentre (0,0,0);

    forAll(points, I)
    {
        bubbleCentre += points[I];
    }

    return bubbleCentre / bubblePtr_->nPoints();
}

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void isoBubble::operator=(const isoBubble& rhs)
{
    // Check for assignment to self
    if (this == &rhs)
    {
        FatalErrorIn("isoBubble::operator=(const isoBubble&)")
            << "Attempted assignment to self"
            << abort(FatalError);
    }

    // Deallocate the memory used for the isoSurface.
    resetPtrData();

    isoFieldPtr_ = rhs.isoFieldPtr_; 
    isoPointField_ = rhs.isoPointField_; 
    bubblePtr_ = autoPtr<isoSurface>(new isoSurface(rhs.bubblePtr_()));
    isoValue_ = rhs.isoValue_;
    timeIndexPad_ = rhs.timeIndexPad_;
    outputFormat_ = rhs.outputFormat_;
    regularize_ = rhs.regularize_;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace bookExamples 


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //