/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkWrappedPhaseDifferencesBaseImageFilter_h
#define __itkWrappedPhaseDifferencesBaseImageFilter_h
 

#include "itkObjectFactory.h"
#include "itkCyclicShiftImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkComposeImageFilter.h"
#include "itkCovariantVector.h"

// Custom
#include "itkPhaseImageToImageFilter.h"
#include "itkWrapPhaseImageFilter.h"

namespace itk
{
/** \class WrappedPhaseDifferencesBaseImageFilter
 * \brief Base class for images dealing with wrapped phase derivatives.
 *
 * Provides useful methods for dealing with wrapped phase differences.  The
 * DirectionalDerivative(unsigned int i) method returns wrapped phase differences
 * in the specified image dimension.  ComposeVector() produces a vector image
 * of wrapped phase differences, where the ith component is produced by calling
 * DirectionalDerivative() in the ith direction.
 *
 */
template< typename TInputImage, typename TOutputImage = TInputImage >
class WrappedPhaseDifferencesBaseImageFilter:
public PhaseImageToImageFilter< TInputImage, TOutputImage >
{
public:

  /** Standard class typedefs. */
  typedef WrappedPhaseDifferencesBaseImageFilter                Self;
  typedef PhaseImageToImageFilter< TInputImage, TOutputImage >  Superclass;
  typedef SmartPointer< Self >                                  Pointer;
  typedef SmartPointer< const Self >                            ConstPointer;
  
  #ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( SameDimensionCheck,
                   ( Concept::SameDimension< TInputImage::ImageDimension, TOutputImage::ImageDimension > ) );
  
  itkConceptMacro( InputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TInputImage::PixelType > ) );
                   
  itkConceptMacro( OutputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TOutputImage::PixelType > ) );
  // End concept checking
  #endif
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(WrappedPhaseDifferencesBaseImageFilter, PhaseImageToImageFilter);
  
  typedef CovariantVector< typename TInputImage::PixelType, TInputImage::ImageDimension > TVector;
  typedef Image< TVector, TInputImage::ImageDimension >          TVectorImage;
  typedef typename TVectorImage::Pointer TVectorPointer;
 
protected:

  WrappedPhaseDifferencesBaseImageFilter();
  ~WrappedPhaseDifferencesBaseImageFilter(){}
	
  // Declare the component filter types:
  typedef CyclicShiftImageFilter< TInputImage >           ShiftType;
  typedef SubtractImageFilter< TInputImage, TInputImage > SubtractType;
  typedef WrapPhaseImageFilter< TInputImage, TInputImage >             WrapType;
  typedef ImageRegionIterator< TInputImage >              ItType;
  
  typedef ComposeImageFilter< TInputImage, TVectorImage > ComposeType;
 
  typename TInputImage::Pointer DirectionalDerivative(unsigned int i);
  TVectorPointer ComposeVector();
 
private:

  WrappedPhaseDifferencesBaseImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented

};

} //namespace ITK

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkWrappedPhaseDifferencesBaseImageFilter.txx"
#endif
 
#endif
