/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author 
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
    Foam::isoBubble

Authors
    Tomislav Maric tomislav@sourceflux.de 
    Jens Hoepken jens@sourceflux.de
    Kyle Mooney kyle.g.mooney@gmail.com

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
    const Time& runTime = time(); 
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

void isoBubble::computeIsoPointField(const volScalarField& isoField)
{
    // Interpolate the track field to the points using volPointInterpolation. 
    volPointInterpolation pointInterpolation (isoField.mesh());
    
    // Reconstruct the bubble using both fields.
    isoPointField_ = pointInterpolation.interpolate(isoField)();
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

isoBubble::isoBubble
(
    const IOobject& io, 
    const volScalarField& isoField, 
    bool isTime , 
    scalar isoValue,
    label timeIndexPad,
    word outputFormat, 
    bool regularize
)
    : 
        regIOobject(io, isTime), 
        isoPointField_(isoField.mesh().nPoints(),0), 
        bubblePtr_(),
        timeIndexPad_(timeIndexPad), 
        outputFormat_(outputFormat)
{
    // Reconstruct immediately using the tracked field.
    reconstruct(isoField, isoValue, regularize);
}

isoBubble::isoBubble(const isoBubble& copy)
    :
        regIOobject(copy), 
        isoPointField_(copy.isoPointField_),
        bubblePtr_(),
        timeIndexPad_(copy.timeIndexPad_), 
        outputFormat_(copy.outputFormat_)
{
    // Make a deep copy: avoid ownership transfer.  
    bubblePtr_ = autoPtr<isoSurface>(new isoSurface (copy.bubblePtr_()));
}

// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * * //

isoBubble::~isoBubble() {}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void isoBubble::setBubbleField(const volScalarField& isoField)
{
    isoPointField_.resize(isoField.mesh().nPoints()); 
}

void isoBubble::reconstruct
(
    const volScalarField& isoField,
    scalar isoValue, 
    bool regularize 
)
{
    computeIsoPointField(isoField); 
    
    bubblePtr_ = autoPtr<isoSurface>
    (
        new isoSurface 
        (
            isoField, 
            isoPointField_, 
            isoValue, 
            regularize
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

    isoPointField_ = rhs.isoPointField_; 
    // Make a deep copy of the bubble surface mesh.
    bubblePtr_ = autoPtr<isoSurface>(new isoSurface(rhs.bubblePtr_()));
    timeIndexPad_ = rhs.timeIndexPad_;
    outputFormat_ = rhs.outputFormat_;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace bookExamples 


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //
