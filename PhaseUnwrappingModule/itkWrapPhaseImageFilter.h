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
#ifndef __itkWrapPhaseImageFilter_h
#define __itkWrapPhaseImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "itkWrapPhaseFunctor.h"

namespace itk
{

/** \class WrapPhaseImageFilter
 *
 * \brief Wraps the input image into the range -pi to pi.
 *
 * Applies the following operation, pixelwise across the image: atan2(sin(x), cos(x)).
 *
 */
template< class TInputImage, class TOutputImage = TInputImage >
class WrapPhaseImageFilter:
  public
  UnaryFunctorImageFilter< TInputImage,
                           TOutputImage,
                           Functor::WrapPhaseFunctor< typename TInputImage::PixelType,
                                                      typename TOutputImage::PixelType > >
{
public:
  /** Standard class typedefs. */
  typedef WrapPhaseImageFilter       Self;
  typedef UnaryFunctorImageFilter< TInputImage,
                                   TOutputImage,
                                   Functor::WrapPhaseFunctor< typename TInputImage::PixelType,
                                                              typename TOutputImage::PixelType > > Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(WrapPhaseImageFilter,
               UnaryFunctorImageFilter);

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

protected:
  WrapPhaseImageFilter() {}
  virtual ~WrapPhaseImageFilter() {}

private:
  WrapPhaseImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);   //purposely not implemented
};
} // end namespace itk

#endif
